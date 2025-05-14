#include "OpenGLInitializer.hpp"
#include <GLFW/glfw3.h>
#include "sge/SGEexception.hpp"

namespace sge
{
    OpenGLInitializer::OpenGLInitializer()
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
            throw errors::gl_error("Failed to initialize GLAD");
    }
}
