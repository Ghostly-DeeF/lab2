#ifndef SGE_GLRENDER_HPP_
#define SGE_GLRENDER_HPP_

#include <cstddef>

typedef void* (* Gladdr)(const char *name);

namespace sge
{

    class GlRender {
    public:
        GlRender(Gladdr gl_address_function);

        void setWindowSize(std::size_t width, std::size_t height);
        void update();

    private:
        void setErrorCallback();
    };

}

#endif
