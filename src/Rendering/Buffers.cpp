#include <glad/glad.h>
#include "Buffers.hpp"
#include "sge/SGEexception.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{
    VertexBuffer::VertexBuffer(size_t size) : m_size(size)
    {
        log::constructor("VertexBuffer");
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW); 
        log::debug("VBO id: %d", m_id); 
    }

    void VertexBuffer::push(const IData& data)
    {
        if ((m_dataOffset + data.size()) > m_size)
            throw errors::overflow_error("There is not enough space in the vertex buffer to add a new object", (m_dataOffset + data.size()) - m_size);

        glBufferSubData(GL_ARRAY_BUFFER, m_dataOffset, data.size(), data.data());
        glEnableVertexAttribArray(m_numAttrib);
        glVertexAttribPointer(m_numAttrib, data.countElements(), GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(m_dataOffset));
        m_dataOffset += data.size();
        ++m_numAttrib;

    }
    
    VertexBuffer::~VertexBuffer()
    {
        log::destructor("VertexBuffer");
        glDeleteBuffers(1, &m_id);
    }

}
