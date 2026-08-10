#include "States/GameplayState.hpp"
#include "Engine/StateManager.hpp"

namespace States {

    GameplayState::GameplayState(Core::StateManager& stateManager, sf::RenderWindow& window)
        : Core::State(stateManager, window)
        , m_font()
        , m_hudText(m_font)
    {
        m_hudText.setString("GAMEPLAY STATE ACTIVE\nPress BACKSPACE for Main Menu");
        m_hudText.setCharacterSize(32);
        m_hudText.setFillColor(sf::Color::Green);
        m_hudText.setPosition({ 350.0f, 300.0f });
    }

    void GameplayState::handleEvent(const sf::Event& event) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Backspace) {
                m_stateManager.popState(); // Pops back to menu if pushed, or handles transition
            }
        }
    }

    void GameplayState::update(sf::Time fixedDeltaTime) {
        // Spaceship movement and collision checks go here
    }

    void GameplayState::render() {
        m_window.draw(m_hudText);
    }

} // namespace States
