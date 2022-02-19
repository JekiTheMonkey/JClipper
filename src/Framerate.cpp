#include "Framerate.hpp"


namespace jclip
{
    Framerate::Framerate()
    {
        setFramerate(0ul);
    }

    Framerate::Framerate(size_t framerate)
    {
        setFramerate(framerate);
    }

    void Framerate::update()
    {
        m_timeSinceLastTick += m_clock.restart();
    }

    bool Framerate::doUpdate()
    {
        if (m_timeSinceLastTick >= m_timePerFrame)
        {
            m_timeSinceLastTick -= m_timePerFrame;
            return true;
        }

        return false;
    }

    void Framerate::setFramerate(size_t framerate)
    {
        m_timePerFrame = sf::seconds(1.f / static_cast<float>(framerate));
    }
} // namespace jclip
