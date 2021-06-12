#ifndef BLYSS_EXCEPTIONS_GLFWEXCEPTION_H_
#define BLYSS_EXCEPTIONS_GLFWEXCEPTION_H_

#include <exception>

namespace Blyss
{
    class GLFWException final : public std::exception
    {
    public:
        [[noreturn]] static void OnGlfwError(int error_code, const char* description);

    private:
        explicit GLFWException(const char* message);
    };
}

#endif