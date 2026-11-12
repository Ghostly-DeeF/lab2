#include "GlContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sge::test
{
    namespace
    {
        struct GlState
        {
            bool initialized = false;
            bool attempted = false;
            GLFWwindow* window = nullptr;

            ~GlState()
            {
                if (window != nullptr)
                    glfwDestroyWindow(window);

                if (initialized)
                    glfwTerminate();
            }
        };

        GlState& state()
        {
            static GlState instance;
            return instance;
        }
    }

    bool ensureGlContext()
    {
        GlState& gl = state();

        if (gl.attempted)
            return gl.window != nullptr;

        gl.attempted = true;

        if (!glfwInit())
            return false;

        gl.initialized = true;

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        gl.window = glfwCreateWindow(64, 64, "sge tests", nullptr, nullptr);
        if (gl.window == nullptr)
        {
            glfwTerminate();
            gl.initialized = false;
            return false;
        }

        glfwMakeContextCurrent(gl.window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            glfwDestroyWindow(gl.window);
            gl.window = nullptr;
            glfwTerminate();
            gl.initialized = false;
            return false;
        }

        return true;
    }
}
