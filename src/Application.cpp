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
#elif _WIN32
#include <errhandlingapi.h>
#include <fileapi.h>
#include <winerror.h>
#include <sys/stat.h>
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
        const auto filepath = homeDir + std::string("/.jclipper.txt");
#elif _WIN32
        const auto homeDir = std::string(getenv("USERPROFILE"));
        const auto roamingDir = std::string("\\AppData\\Roaming");
        const auto jclipperDir = std::string("\\JClipper");
        const auto jclipperDirPath = homeDir + roamingDir + jclipperDir;

        struct stat buffer;
        if (stat(jclipperDirPath.c_str(), &buffer))
            CreateDirectory(jclipperDirPath.c_str(), NULL);

        const auto filepath = jclipperDirPath + std::string("\\.jclipper.txt");
#else
#error Unsupported platform
#endif

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
        const auto comb1 = KeysBuffer::KeyStates("100000001");
        const auto comb2 = KeysBuffer::KeyStates("000010001");

        if (cur == comb1 || cur == comb2)
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
