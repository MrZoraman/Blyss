#include <glad/glad.h>

#include "Window.hpp"

#include <exception>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <boost/log/trivial.hpp>

#include "exceptions/OpenGLException.hpp"

namespace blyss
{
    Window::Window(int width, int height, const char* title)
        : glfw_window_{width, height, title}
    {
        glfw_window_.MakeContextCurrent();

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Unable to initialize GLAD!");
        }

        glad_set_post_callback(OpenGLException::OpenGLPostCallback);

        glfw_window_.on_window_resize.connect(OnWindowResize);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(glfw_window_.GetRawWinPtr(), true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    Window::~Window()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Window::RunUntilClose()
    {
        while (!glfw_window_.ShouldClose())
        {
            try
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                Frame();
                ImGui::Render();
                glClear(GL_COLOR_BUFFER_BIT);

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
            catch (OpenGLException& e)
            {
                BOOST_LOG_TRIVIAL(error) << "OpenGL Error: " << e.what();
            }

            glfw_window_.SwapBuffers();

            glfwPollEvents();
        }
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Window::Frame()
    {
        ImGui::ShowDemoWindow(nullptr);
    }

    void Window::OnWindowResize(BGlfwWindowW&, int width, int height)
    {
        if (width <= 0 || height <= 0)
        {
            BOOST_LOG_TRIVIAL(warning) << "Window was resized, and the new dimensions are " << width
                << ", " << height << ", which is strange. This resize operation will be ignored.";
            return;
        }

        glViewport(0, 0, width, height);
    }
}
