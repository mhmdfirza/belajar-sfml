#include "Engine/StateManager.hpp"
#include <cassert>

namespace Core {

    void StateManager::pushState(std::unique_ptr<State> newState) {
        m_pendingList.push_back({ Action::Push, std::move(newState) });
    }

    void StateManager::popState() {
        m_pendingList.push_back({ Action::Pop, nullptr });
    }

    void StateManager::changeState(std::unique_ptr<State> newState) {
        m_pendingList.push_back({ Action::Change, std::move(newState) });
    }

    void StateManager::clearStates() {
        m_pendingList.push_back({ Action::Clear, nullptr });
    }

    void StateManager::processEvents(const sf::Event& event) {
        if (!m_stateStack.empty()) {
            m_stateStack.back()->handleEvent(event);
        }
    }

    void StateManager::update(sf::Time fixedDeltaTime) {
        if (!m_stateStack.empty()) {
            m_stateStack.back()->update(fixedDeltaTime);
        }
    }

    void StateManager::render() {
        // Draw bottom-up if you want stacked UI transparency, or top-only for focus
        if (!m_stateStack.empty()) {
            m_stateStack.back()->render();
        }
    }

    void StateManager::applyPendingChanges() {
        for (auto& change : m_pendingList) {
            switch (change.action) {
                case Action::Push:
                    if (!m_stateStack.empty()) {
                        m_stateStack.back()->pause();
                    }
                    m_stateStack.push_back(std::move(change.state));
                    break;

                case Action::Pop:
                    if (!m_stateStack.empty()) {
                        m_stateStack.pop_back(); // Automatically invokes destructor via unique_ptr
                    }
                    if (!m_stateStack.empty()) {
                        m_stateStack.back()->resume();
                    }
                    break;

                case Action::Change:
                    if (!m_stateStack.empty()) {
                        m_stateStack.pop_back();
                    }
                    m_stateStack.push_back(std::move(change.state));
                    break;

                case Action::Clear:
                    m_stateStack.clear();
                    break;
            }
        }
        m_pendingList.clear();
    }

} // namespace Core
