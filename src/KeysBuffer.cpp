#include "KeysBuffer.hpp"

#include <iostream>

namespace jclip
{
    sf::Keyboard::Key convert(KeysBuffer::Keys key)
    {
        switch (key)
        {
            case KeysBuffer::LControl: return sf::Keyboard::LControl;
            case KeysBuffer::LAlt: return sf::Keyboard::LAlt;
            case KeysBuffer::LShift: return sf::Keyboard::LShift;
            case KeysBuffer::LSystem: return sf::Keyboard::LSystem;
            
            case KeysBuffer::RControl: return sf::Keyboard::RControl;
            case KeysBuffer::RAlt: return sf::Keyboard::RAlt;
            case KeysBuffer::RShift: return sf::Keyboard::RShift;
            case KeysBuffer::RSystem: return sf::Keyboard::RSystem;

            case KeysBuffer::C: return sf::Keyboard::C;

            default: return sf::Keyboard::Unknown;
        }
    }

    KeysBuffer::KeysBuffer()
    : m_keys()
    {
        for (auto i = 0ul; i < KeyCount; i++)
        {
            m_keys.emplace_back(convert(static_cast<Keys>(i)));
        }
    }

    void KeysBuffer::update()
    {
        auto i = 0ul;
        for (const auto &keyId : m_keys)
        {
            const auto state = sf::Keyboard::isKeyPressed(keyId);
            m_keyStates.set(i, state);
            i++;
        }
    }

    KeysBuffer::KeyStates KeysBuffer::getKeyStates() const
    {
        return m_keyStates;
    }
} // namespace jclip
