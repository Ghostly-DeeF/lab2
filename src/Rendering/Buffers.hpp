#ifndef SGE_RENDERING_BUFFERS_HPP_
#define SGE_RENDERING_BUFFERS_HPP_

#include "../Data.hpp"

namespace sge::rendering
{
    class IBuffer
    {
    public:
        IBuffer() = default;
        virtual void push(const IData&) = 0;
        virtual ~IBuffer() = default;
    };

    class VertexBuffer : public IBuffer
    {
    public:
        explicit VertexBuffer(size_t);
        VertexBuffer(VertexBuffer &&) = default;
        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer &operator=(VertexBuffer &&) = default;
        VertexBuffer &operator=(const VertexBuffer &) = delete;
        ~VertexBuffer() override;

        void push(const IData&) override;

    private:
        unsigned m_id = 0;
        size_t m_size = 0;
        size_t m_dataOffset = 0;
        unsigned char m_numAttrib = 0;

        void bind();
        void unbind();
    };
 
    

}
#endif
