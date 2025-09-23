#ifndef SGE_SRC_RENDERING_OBJECT_RPOINT_HPP_
#define SGE_SRC_RENDERING_OBJECT_RPOINT_HPP_

#include "../ShaderProgram.hpp"
#include "sge/2dprimitives.hpp"
#include "../VertexArray.hpp"

namespace sge::rendering::object
{
    class RPoint {
    public:
        RPoint(sge::objects::Point, const ShaderProgram&);
        RPoint(RPoint &&) = default;
        RPoint(const RPoint &) = delete;
        RPoint &operator=(RPoint &&) = default;
        RPoint &operator=(const RPoint &) = delete;
        ~RPoint() = default;

        void rendering(size_t, size_t) const;
        sge::objects::Point* getGeometry();

    private:
        sge::objects::Point m_geometry;
        VertexArray m_VAO;
        const ShaderProgram &m_shader;
    };    
}
#endif
