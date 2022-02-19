#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <bitset>
#include <vector>


namespace jclip
{
    class KeysBuffer
    {
    public:
        enum Keys
        {
            LControl,
            LShift,
            LAlt,
            LSystem,

            RControl,
            RShift,
            RAlt,
            RSystem,

            C,

            KeyCount
        };

        using KeyStates = std::bitset<static_cast<size_t>(KeyCount)>;
        using KeysContainer = std::vector<sf::Keyboard::Key>;

    public:
        KeysBuffer();

        void update();

        KeyStates getKeyStates() const;

    private:
        KeysContainer m_keys;
        KeyStates m_keyStates;
    };
} // namespace jclip
