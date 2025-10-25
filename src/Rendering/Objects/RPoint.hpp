#ifndef SGE_SRC_RENDERING_OBJECT_RPOINT_HPP_
#define SGE_SRC_RENDERING_OBJECT_RPOINT_HPP_

#include "../ShaderProgram.hpp"
#include "sge/2dprimitives.hpp"
#include "../VertexArray.hpp"
#include "../../math/Linear.hpp"

namespace sge::rendering::object
{
    class RPoint {
    public:
        RPoint(sge::geometry::objects2D::Point, const ShaderProgram&);
        RPoint(RPoint &&) = default;
        RPoint(const RPoint &) = delete;
        RPoint &operator=(RPoint &&) = default;
        RPoint &operator=(const RPoint &) = delete;
        ~RPoint() = default;

        void rendering(size_t, size_t);
        sge::geometry::objects2D::Point* getGeometry();

    private:
        sge::geometry::objects2D::Point m_geometry;
        VertexArray m_VAO;
        const ShaderProgram &m_shader;

        math::mat4 m_transform = 1.0f;
        math::vec3 m_oldPos{-1.0f, -1.0f, -1.0f};
        math::vec2 m_oldWindowData{-1.0f, -1.0f};
        
    };    
}
#endif
