/*
 * Copyright (c) MrZoraman 2021
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "wrappers/opengl/ShaderProgram.hpp"

#include <cstdio>
#include <cstring>
#include <exception>
#include <sstream>

#include <glad/glad.h>

#include "exceptions/OpenGLException.hpp"

const size_t kInfoLogSize = 512;

namespace blyss
{
    ShaderProgram::ShaderProgram()
        : handle_{glCreateProgram()}
    {
        if (handle_ == 0)
        {
            throw OpenGLException("glCreateShader failed to create a shader!");
        }
    }

    ShaderProgram::~ShaderProgram()
    {
        try
        {
            glDeleteProgram(handle_);
        }
        catch (const std::exception& e)
        {
            std::printf("Failed to destroy shader program %d: %s\n", handle_, e.what());
        }
        catch (...)
        {
            std::printf("Unknown error occurred while destroying shader program %d\n", handle_);
        }
    }

    void ShaderProgram::AttachShader(const Shader& shader) const
    {
        glAttachShader(handle_, shader.get_handle());
    }

    void ShaderProgram::Link() const
    {
        char info_log[kInfoLogSize];
        std::memset(&info_log, 0, sizeof(info_log));

        glLinkProgram(handle_);

        int success = 0;
        glGetProgramiv(handle_, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(handle_, kInfoLogSize, nullptr, static_cast<char*>(info_log));
            std::stringstream ss;
            ss << "Failed to link shader program: ";
            ss << static_cast<char*>(info_log);
            throw OpenGLException(ss.str().c_str());
        }
    }

    void ShaderProgram::Use() const
    {
        glUseProgram(handle_);
    }
}
