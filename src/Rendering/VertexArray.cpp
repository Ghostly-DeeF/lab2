#include <glad/glad.h>
#include "VertexArray.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{

    VertexArray::VertexArray()
    {
        log::constructor("VertexArray");
        glGenVertexArrays(1, &m_id);
        log::info("VAO id: %d", m_id);
    }

    VertexArray &VertexArray::operator=(VertexArray &&moved) noexcept
    {
        log::lifeTime log("Move", "VertexArray");
        log::info("Move %d to %d", m_id, moved.m_id);
        if (&moved == this)
            return *this;

        std::swap(m_id, moved.m_id);
        std::swap(m_buffers, moved.m_buffers);
        
        return *this;
    }

    void VertexArray::bind() const
    {
        log::debug("bind VAO %d", m_id);
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind() const
    {
        log::debug("unbind VAO %d", m_id);
        glBindVertexArray(0);
    }

    void VertexArray::push(std::unique_ptr<IBuffer> buffer)
    {
        log::lifeTime log("VERTEXARRAY", "Push buffer");
        buffer->bind();
        for(int i = 0; i < 2; ++i)
            setAttributes(buffer->getAttributes(i), i);
        buffer->unbind();

        m_buffers.push_back(std::move(buffer));
    }

    void VertexArray::setAttributes(IBuffer::Layout layout, unsigned id) const
    {
        log::debug("SetAttrib");
        bind();
        
        glEnableVertexAttribArray(id);
        glVertexAttribPointer(id, layout.count_elements, GL_FLOAT, GL_FALSE, layout.count_elements * sizeof(float), reinterpret_cast<void*>(layout.offset));

        unbind();
    }

    VertexArray::~VertexArray()
    {
        log::destructor("VertexArray", "%d", m_id);
        glDeleteVertexArrays(1, &m_id);
    }

}
