#ifndef ENGINE_ENGINE_HPP
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <string_view>
#include <memory>

namespace Core {

    /**
     * @brief Core Engine class managing the main window and execution lifecycle.
     * Uses RAII and a Fixed Timestep Game Loop.
     */
    class Engine {
    public:
        Engine(unsigned int width, unsigned int height, std::string_view title);
        ~Engine() = default;

        // Prevent copying to maintain strict ownership of hardware resources
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        // Allow moving if resource ownership needs transfer
        Engine(Engine&&) noexcept = default;
        Engine& operator=(Engine&&) noexcept = default;

        /**
         * @brief Starts and executes the main game loop.
         */
        void run();

    private:
        void processEvents();
        void update(sf::Time fixedDeltaTime);
        void render();

    private:
        sf::RenderWindow m_window;
        bool m_isRunning;

        // Fixed timestep parameters (60 Hz target tick rate)
        static constexpr float TARGET_FPS = 60.0f;
        const sf::Time m_timePerFrame{ sf::seconds(1.0f / TARGET_FPS) };
    };

} // namespace Core

#endif // ENGINE_HPP
