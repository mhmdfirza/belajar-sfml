#include <../../engine/engine.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace Core {

    Engine::Engine(unsigned int width, unsigned int height, std::string_view title)
        : m_window(sf::VideoMode({width, height}), sf::String::fromUtf8(title.begin(), title.end()), sf::Style::Default)
        , m_isRunning(true)
    {
        // Limit rendering frame rate to monitor refresh or cap (VSync off for explicit loop test)
        m_window.setVerticalSyncEnabled(true);
    }

    void Engine::run() {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (m_isRunning && m_window.isOpen()) {
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;

            // Spiral of Death protection: prevent massive lag spikes from causing endless updates
            if (timeSinceLastUpdate > sf::seconds(0.25f)) {
                timeSinceLastUpdate = sf::seconds(0.25f);
            }

            // Consume time in fixed chunks
            while (timeSinceLastUpdate >= m_timePerFrame) {
                timeSinceLastUpdate -= m_timePerFrame;
                processEvents();
                update(m_timePerFrame);
            }

            render();
        }
    }

    void Engine::processEvents() {
        // SFML 3.x event polling API returning std::optional<sf::Event>
        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_isRunning = false;
                m_window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    m_isRunning = false;
                    m_window.close();
                }
            }
        }
    }

    void Engine::update(sf::Time fixedDeltaTime) {
        // Core game logic, state management, and physics updates go here in future milestones
    }

    void Engine::render() {
        // Clear screen with dark background color typical for space shooters
        m_window.clear(sf::Color(10, 10, 25));

        // Drawing of current game states will occur here

        m_window.display();
    }

} // namespace Core
