#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>

using size_t = unsigned long int;


namespace jclip
{
    class Framerate : private sf::NonCopyable
    {
    public:
        Framerate();
        Framerate(size_t framerate);

        void update();
        bool doUpdate();

        void setFramerate(size_t framerate);

    private:
        sf::Clock m_clock;
        sf::Time m_timeSinceLastTick = sf::Time::Zero;
        sf::Time m_timePerFrame = sf::Time::Zero;
    };
} // namespace jclip
