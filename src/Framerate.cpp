#include "Framerate.hpp"

#include <chrono>
#include <thread>


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

        const auto remainingTime = m_timePerFrame - m_timeSinceLastTick;
        if (remainingTime > sf::Time::Zero)
        {
            const auto duration = std::chrono::duration<float, std::milli>(remainingTime.asMilliseconds());
            std::this_thread::sleep_for(duration);
        }
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
