#pragma once

#include "DoubleKeysBuffer.hpp"
#include "Framerate.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Clipboard.hpp>

#include <fstream>


namespace jclip
{
    class Application : private sf::NonCopyable
    {
    public:
        Application();
        ~Application();

        void init();
        void run();

    private:
        void update();

    private:
        DoubleKeysBuffer m_doubleKeysBuffer;
        Framerate m_framerate;
        std::string m_clipboardString;
        std::fstream m_stream;
    };
} // namespace jclip
