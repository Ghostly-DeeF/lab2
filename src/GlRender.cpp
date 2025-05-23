#include "GlRender.hpp"
#include <glad/glad.h>
#include "sge/SGEexception.hpp"
#include "sge/Logger.hpp"

namespace sge
{
    GlRender::GlRender(Gladdr gl_address_function)
    {
        if (!gladLoadGLLoader(gl_address_function))
            throw errors::gl_error(GL_DEBUG_SEVERITY_HIGH, 0, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SOURCE_OTHER, "Failed to initialize GLAD");
    
        GLint flags; 
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT))
            log::warn("OpenGL exceptions are not initialized");

        setErrorCallback();
        glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
    }

    void GlRender::setWindowSize(size_t width, size_t height)
    {
        glViewport(0, 0, width, height);
    }

    void GlRender::update()
    {
        glClearColor(.0f, .0f, .0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GlRender::setErrorCallback()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(
            [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
            {
                switch (severity)
                {
                    case GL_DEBUG_SEVERITY_HIGH:
                        throw errors::gl_error(severity, id, type, source, message); 
                        break;
                    case GL_DEBUG_SEVERITY_MEDIUM:
                        throw errors::gl_error(severity, id, type, source, message);
                        break;
                    case GL_DEBUG_SEVERITY_LOW:
                        throw errors::gl_error(severity, id, type, source, message);
                        break;
                    case GL_DEBUG_SEVERITY_NOTIFICATION:
                        log::info("NOTIFICATION:\nID: %s\nType: %s\nSource: %s\nMessage: %s", id, type, source, message);
                        break;
                    default:
                        log::warn("GL unknown error");
                        break;
                }
            }
        , nullptr);
    }
}
