#ifndef SGE_SRC_RENDERING_OBJECT_RLINE_HPP_
#define SGE_SRC_RENDERING_OBJECT_RLINE_HPP_

#include "../ShaderProgram.hpp"
#include "sge/2dprimitives.hpp"
#include "../VertexArray.hpp"

namespace sge::rendering::object
{
    class RLine {
    public:
        RLine(sge::geometry::objects2D::Line, const ShaderProgram&);
        RLine(RLine &&) = default;
        RLine(const RLine &) = delete;
        RLine &operator=(RLine &&) = default;
        RLine &operator=(const RLine &) = delete;
        ~RLine() = default;

        void rendering(size_t window_width, size_t window_height);
        sge::geometry::objects2D::Line* getGeometry();

    private:
        sge::geometry::objects2D::Line m_geometry;
        VertexArray m_VAO;
        const ShaderProgram &m_shader;

        sge::geometry::objects2D::Vertex m_oldPos{0, 0, 0};
        math::mat4 m_transform = 1.0f;
    };    
}
#endif
