#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#ifndef ENGINE_STATEMANAGER_HPP
#define ENGINE_STATEMANAGER_HPP

#include "Engine/State.hpp"
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Core {

    /**
     * @brief Manages state transitions using stack-based Finite State Machine logic.
     * Uses deferred state modifications to protect object lifecycles during updates.
     */
    class StateManager {
    public:
        enum class Action {
            Push,
            Pop,
            Change,
            Clear
        };

        StateManager() = default;
        ~StateManager() = default;

        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;

        // Defer modifications to end-of-frame
        void pushState(std::unique_ptr<State> newState);
        void popState();
        void changeState(std::unique_ptr<State> newState);
        void clearStates();

        // Forward processing calls to the top active state
        void processEvents(const sf::Event& event);
        void update(sf::Time fixedDeltaTime);
        void render();

        // Safe mutation application
        void applyPendingChanges();

        [[nodiscard]] bool isEmpty() const noexcept { return m_stateStack.empty(); }

    private:
        struct PendingChange {
            Action action;
            std::unique_ptr<State> state{ nullptr };
        };

    private:
        std::vector<std::unique_ptr<State>> m_stateStack;
        std::vector<PendingChange> m_pendingList;
    };

} // namespace Core

#endif // ENGINE_STATEMANAGER_HPP

#endif // STATEMANAGER_HPP_INCLUDED
