#include <glad/glad.h>
#include "Buffers.hpp"
#include "sge/SGEexception.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{

    void IBuffer::bind()
    {
        log::debug("bind VBO %d", m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }
    
    void IBuffer::unbind()
    {
        log::debug("unbind VBO %d", m_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IBuffer::Layout IBuffer::getAttributes(size_t it)
    {
        return m_attributes.at(it);
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
        //glEnableVertexAttribArray(m_numAttrib);
        //glVertexAttribPointer(m_numAttrib, data.countElements(), GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(m_dataOffset));

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
