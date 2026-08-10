#ifndef GAMEPLAYSTATE_HPP_INCLUDED
#define GAMEPLAYSTATE_HPP_INCLUDED

#ifndef STATES_GAMEPLAYSTATE_HPP
#define STATES_GAMEPLAYSTATE_HPP

#include "Engine/State.hpp"
#include <SFML/Graphics/Text.hpp>

namespace States {

    class GameplayState : public Core::State {
    public:
        GameplayState(Core::StateManager& stateManager, sf::RenderWindow& window);

        void handleEvent(const sf::Event& event) override;
        void update(sf::Time fixedDeltaTime) override;
        void render() override;

    private:
        sf::Font m_font;
        sf::Text m_hudText;
    };

} // namespace States

#endif // STATES_GAMEPLAYSTATE_HPP

#endif // GAMEPLAYSTATE_HPP_INCLUDED
