#ifndef SGE_RENDERING_VERTEXARRAY_HPP_
#define SGE_RENDERING_VERTEXARRAY_HPP_


namespace sge::rendering
{
    struct Layout;
    class IBuffer;
}

#include <vector>
#include <memory>

namespace sge::rendering
{
    class VertexArray
    {
    public:
        VertexArray();
        VertexArray(VertexArray &&) noexcept;
        VertexArray(const VertexArray &) = delete;
        VertexArray &operator=(VertexArray &&) noexcept;
        VertexArray &operator=(VertexArray &) = delete;
        ~VertexArray();
 
        void push(std::unique_ptr<IBuffer> buffer);
        void setAttributes(Layout layout, unsigned id) const;

        void bind() const;
        void unbind() const;
        unsigned id() const;

    private:
        unsigned m_id = 0;
        std::vector<std::unique_ptr<IBuffer>> m_buffers;

        
    };
}

#endif
