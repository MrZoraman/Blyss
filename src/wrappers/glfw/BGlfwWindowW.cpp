#include "wrappers/glfw/BGlfwWindowW.hpp"

#include <GLFW/glfw3.h>

namespace Blyss
{
    BGlfwWindowW::BGlfwWindowW(int width, int height, const char* title)
        : window_{MakeWindow(width, height, title)}
    {
        glfwSetWindowUserPointer(window_, this);
        glfwSetWindowSizeCallback(window_, GlfwWindowResizeCallback);
    }

    BGlfwWindowW::~BGlfwWindowW()
    {
        if (window_ != nullptr)
        {
            glfwSetWindowUserPointer(window_, nullptr);
            glfwSetWindowSizeCallback(window_, nullptr);
            glfwDestroyWindow(window_);
        }
    }

    void BGlfwWindowW::MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_);
    }

    bool BGlfwWindowW::ShouldClose()
    {
        bool should_close = glfwWindowShouldClose(window_);
        return should_close;
    }

    void BGlfwWindowW::SwapBuffers()
    {
        glfwSwapBuffers(window_);
    }


    GLFWwindow* BGlfwWindowW::MakeWindow(int width, int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        return window;
    }

    void BGlfwWindowW::GetFramebufferSize(int& w, int& h)
    {
        glfwGetFramebufferSize(window_, &w, &h);
    }

    GLFWwindow* BGlfwWindowW::GetRawWinPtr()
    {
        return window_;
    }

    void BGlfwWindowW::GlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto wrapper = static_cast<BGlfwWindowW*>(glfwGetWindowUserPointer(window));
        wrapper->OnWindowResize(width, height);
    }


}