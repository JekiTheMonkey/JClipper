#include "DoubleKeysBuffer.hpp"


namespace jclip
{
    void DoubleKeysBuffer::update()
    {
        swapBuffers();
        m_keyBuffers[m_curBuffer].update();
    }

    KeysBuffer::KeyStates DoubleKeysBuffer::getCurBuffer() const
    {
        return m_keyBuffers[m_curBuffer].getKeyStates();
    }

    KeysBuffer::KeyStates DoubleKeysBuffer::getPrevBuffer() const
    {
        return m_keyBuffers[m_prevBuffer].getKeyStates();
    }

    void DoubleKeysBuffer::swapBuffers()
    {
        std::swap(m_curBuffer, m_prevBuffer);
    }
} // namespace jclip
