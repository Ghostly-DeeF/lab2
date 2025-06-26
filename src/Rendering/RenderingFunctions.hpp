#ifndef SGE_RENDERING_RENDERINGFUNCTIONS_HPP_
#define SGE_RENDERING_RENDERINGFUNCTIONS_HPP_

#include "sge/2dprimitives.hpp"
#include "VertexArray.hpp"

namespace sge::rendering
{
    VertexArray setup(const objects::Point&);
    void draw(const objects::Point&, const VertexArray & VAO);


}

#endif
