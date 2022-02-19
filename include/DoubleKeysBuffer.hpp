#include "KeysBuffer.hpp"


namespace jclip
{
    class DoubleKeysBuffer
    {
    public:
        void update();

        KeysBuffer::KeyStates getCurBuffer() const;
        KeysBuffer::KeyStates getPrevBuffer() const;

    private:
        void swapBuffers();

    private:
        size_t m_curBuffer = 0ul;
        size_t m_prevBuffer = 1ul;
        KeysBuffer m_keyBuffers[2ul];
    };
} // namespace jclip
