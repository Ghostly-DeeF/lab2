#ifndef SGE_RENDERING_RENDERINGFUNCTIONS_HPP_
#define SGE_RENDERING_RENDERINGFUNCTIONS_HPP_

#include "sge/2dprimitives.hpp"

namespace sge::rendering
{
    unsigned int setup(const objects::Point&);
    void draw(const objects::Point&, unsigned int);


}

#endif
