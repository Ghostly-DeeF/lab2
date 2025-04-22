#ifndef SGE_OPENGLINITIALIZER_HPP_
#define SGE_OPENGLINITIALIZER_HPP_

#include<glad/glad.h>

namespace sge
{
    class OpenGLInitializer {
    public:
        OpenGLInitializer();
        OpenGLInitializer(OpenGLInitializer &&) = default;
        OpenGLInitializer(const OpenGLInitializer &) = default;
        OpenGLInitializer &operator=(OpenGLInitializer &&) = default;
        OpenGLInitializer &operator=(const OpenGLInitializer &) = default;
        ~OpenGLInitializer() = default;

    private:
        
    };
}

#endif
