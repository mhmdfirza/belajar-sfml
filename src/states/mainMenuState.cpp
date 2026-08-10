#ifndef MAINMENUSTATE_CPP_INCLUDED
#define MAINMENUSTATE_CPP_INCLUDED

#include "States/MainMenuState.hpp"
#include "States/GameplayState.hpp"
#include "Engine/StateManager.hpp"
#include <iostream>

namespace States {

    MainMenuState::MainMenuState(Core::StateManager& stateManager, sf::RenderWindow& window)
        : Core::State(stateManager, window)
        , m_font()
        , m_titleText(m_font)
        , m_instructionText(m_font)
    {
        // For Milestone 2 verification, we create visually distinct text
        // SFML 3 default font handling or loading fallback
        if (!m_font.openFromFile("assets/fonts/arial.ttf")) {
            std::cout << "[INFO]: Font loading skipped for initial state verification test.\n";
        }

        m_titleText.setString("MAIN MENU");
        m_titleText.setCharacterSize(48);
        m_titleText.setFillColor(sf::Color::Yellow);
        m_titleText.setPosition({ 450.0f, 200.0f });

        m_instructionText.setString("Press ENTER to Play\nPress ESCAPE to Exit");
        m_instructionText.setCharacterSize(24);
        m_instructionText.setFillColor(sf::Color::White);
        m_instructionText.setPosition({ 450.0f, 350.0f });
    }

    void MainMenuState::handleEvent(const sf::Event& event) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                // Transition to gameplay state safely
                m_stateManager.changeState(std::make_unique<GameplayState>(m_stateManager, m_window));
            }
        }
    }

    void MainMenuState::update(sf::Time fixedDeltaTime) {
        // Menu animations will go here in UI milestone
    }

    void MainMenuState::render() {
        m_window.draw(m_titleText);
        m_window.draw(m_instructionText);
    }

} // namespace States


#endif // MAINMENUSTATE_CPP_INCLUDED
