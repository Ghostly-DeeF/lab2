#include "Buffers.hpp"

#include <glad/glad.h>
#include "sge/SGEexception.hpp"
#include "../Data.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{

    IBuffer::IBuffer(IBuffer &&moved) noexcept
    {
        log::constructor("Move IBuffer");
        m_attributes = std::move(moved.m_attributes);
        m_id = moved.m_id;
        moved.m_id = 0;
    }

    IBuffer &IBuffer::operator=(IBuffer &&moved) noexcept
    {
        log::opertor("IBuffer", "Move");
        if (&moved == this)
            return *this;

        std::swap(m_attributes, moved.m_attributes);
        std::swap(m_id, moved.m_id);

        return *this;
    }

    void IBuffer::bind() const
    {
        log::debug("bind VBO %d", m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }
    
    void IBuffer::unbind() const
    {
        log::debug("unbind VBO %d", m_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Layout IBuffer::getAttributes(size_t it) const
    {
        return m_attributes.at(it);
    }

    unsigned IBuffer::getCountAttributes() const noexcept
    {
        return m_attributes.size();
    }


    VertexBuffer::VertexBuffer(size_t size) : m_size(size)
    {
        log::constructor("VertexBuffer");
        glGenBuffers(1, &m_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW); 
        log::info("VBO id: %d", m_id); 
        unbind();
    }

    void VertexBuffer::push(const IData& data)
    {
        log::debug("Push data to VBO %d", m_id);
        if ((m_dataOffset + data.size()) > m_size)
            throw errors::overflow_error("There is not enough space in the vertex buffer to add a new object", (m_dataOffset + data.size()) - m_size);
        
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, m_dataOffset, data.size(), data.data());

        m_attributes.push_back({data.countElements(), m_dataOffset});

        m_dataOffset += data.size();
        unbind();
    } 

    VertexBuffer::~VertexBuffer()
    {
        log::destructor("VertexBuffer", "%d", m_id);
        glDeleteBuffers(1, &m_id);
    }

}
