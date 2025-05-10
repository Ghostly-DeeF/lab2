#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge::objects
{
    
    ElementData<Vertex, 1> Point::getVerteces() const
    {
        log::debug("vertex: %f", vertex.x);
        return ElementData<Vertex, 1>({vertex}, static_cast<int>(ItemType::VERTEX));
    }

    ElementData<glm::vec4, 1> Point::getColor() const
    {
        log::debug("vertex: %f", vertex.x);
        return ElementData<glm::vec4, 1>({color}, static_cast<int>(ItemType::RGBA));
    }
}
