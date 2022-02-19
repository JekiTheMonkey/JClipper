#include "Application.hpp"

#include <algorithm>
#include <codecvt>
#include <ctime>
#include <cstring>
#include <locale>
#include <iostream>

#ifdef linux
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif


namespace jclip
{
    Application::Application()
    : m_framerate(60ul)
    {
    }

    Application::~Application()
    {
        m_stream.close();
    }

    void Application::init()
    {
#ifdef linux
        const auto *pw = getpwuid(getuid());
        const auto homeDir = std::string(pw->pw_dir);
#elif _WIN32
        const auto homeDir = std::string("%HOMEPATH%\\");
#endif
        const auto filepath = homeDir + std::string("/.jclipper.txt");

        m_stream.open(filepath, m_stream.app | m_stream.out);
        if (!m_stream.is_open())
            throw std::runtime_error("Application::init() - Failed to open \"" + filepath + "\"");
    }

    void Application::run()
    {
        while (true)
        {
            m_framerate.update();

            while (m_framerate.doUpdate())
            {
                update();
            }
        }
    }

    void Application::update()
    {
        m_doubleKeysBuffer.update();

        const auto cur = m_doubleKeysBuffer.getCurBuffer();
        const auto prev = m_doubleKeysBuffer.getPrevBuffer();

        if (auto found = std::find(copyBitsets.begin(), copyBitsets.end(), cur); 
            found != copyBitsets.end())
        {
            if (cur != prev)
            {
                using Converter = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;

                auto buffer = sf::Clipboard::getString();
                auto str = Converter().to_bytes(buffer.toWideString());

                if (str != m_clipboardString)
                {
                    const auto time = std::time(nullptr);
                    auto timeStr = std::string(std::ctime(&time));
                    // Remove trailing \n
                    timeStr.resize(timeStr.size() - 1ul);

                    m_stream << "[" << timeStr << "] - " << str << std::endl;
                    std::swap(str, m_clipboardString);
                }
            }
        }
    }
} // namespace jclip
