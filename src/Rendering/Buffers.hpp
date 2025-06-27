#ifndef SGE_RENDERING_BUFFERS_HPP_
#define SGE_RENDERING_BUFFERS_HPP_

#include "../Data.hpp"
#include <vector>

namespace sge::rendering
{
    class IBuffer
    {
    public:
        IBuffer() = default;
        IBuffer(IBuffer &&) = default;
        IBuffer(const IBuffer &) = delete;
        IBuffer &operator=(IBuffer &&) = default;
        IBuffer &operator=(const IBuffer &) = delete;

        virtual void push(const IData&) = 0;
        virtual ~IBuffer() = default;

        struct Layout
        {
            unsigned char count_elements = 0;
            size_t offset = 0;
        };

        void bind() const;
        void unbind() const;

        Layout getAttributes(size_t it) const;
        
    protected:
        std::vector<Layout> m_attributes;
        unsigned m_id = 0;
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
        //Layout getAttributes(size_t it);
 

    private: 
        size_t m_size = 0;
        size_t m_dataOffset = 0;

    };
 
    

}
#endif
