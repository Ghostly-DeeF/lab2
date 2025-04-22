#include "OpenGLInitializer.hpp"
#include <GLFW/glfw3.h>

namespace sge
{
    OpenGLInitializer::OpenGLInitializer()
    {
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }
}
