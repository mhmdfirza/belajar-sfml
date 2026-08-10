#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#ifndef ENGINE_STATE_HPP
#define ENGINE_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace Core {

    class StateManager; // Forward declaration

    /**
     * @brief Abstract base class for all game states.
     */
    class State {
    public:
        State(StateManager& stateManager, sf::RenderWindow& window)
            : m_stateManager(stateManager), m_window(window) {}

        virtual ~State() = default;

        State(const State&) = delete;
        State& operator=(const State&) = delete;
        State(State&&) noexcept = default;
        State& operator=(State&&) noexcept = default;

        // Core lifecycle interface
        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void update(sf::Time fixedDeltaTime) = 0;
        virtual void render() = 0;

        // Called when a state is paused/resumed by stack operations
        virtual void pause() {}
        virtual void resume() {}

    protected:
        StateManager& m_stateManager;
        sf::RenderWindow& m_window;
    };

} // namespace Core

#endif // ENGINE_STATE_HPP

#endif // STATE_HPP_INCLUDED
