#ifndef SGE_RENDERING_VERTEXARRAY_HPP_
#define SGE_RENDERING_VERTEXARRAY_HPP_

#include "Buffers.hpp"

#include <vector>
#include <memory>

namespace sge::rendering
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
 
        void push(std::unique_ptr<IBuffer> buffer);
        void setAttributes(IBuffer::Layout layout, unsigned id);

    private:
        unsigned m_id = 0;
        std::vector<std::unique_ptr<IBuffer>> m_buffers;

        void bind();
        void unbind();
    };
}

#endif
