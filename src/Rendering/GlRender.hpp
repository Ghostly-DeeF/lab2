#ifndef SGE_GLRENDER_HPP_
#define SGE_GLRENDER_HPP_

#include <cstddef>

typedef void* (* Gladdr)(const char *name);

namespace sge::rendering
{

    class GlRender {
    public:
        GlRender(Gladdr gl_address_function);

        void setWindowSize(size_t width, size_t height);
        void update();

    private:
        void setErrorCallback();
    };

}

#endif
