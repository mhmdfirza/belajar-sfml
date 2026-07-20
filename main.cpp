#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

int main()
{
    // ----------- LOAD RESOURCES -----------
    // RENDER WINDOW
    sf::RenderWindow window(
        sf::VideoMode({1080,720}),
        "SFML 3");
    sf::Vector2 windowSize= window.getSize();
    // LOAD FONT
    sf::Font font;
    if (!font.openFromFile("resources/font/arial.ttf")){
        cout << "Error: Failed Load Font\n";
        return -1;
    }
    // LOAD TEXTURE
    sf::Texture texture;
    if (!texture.loadFromFile("resources/asset/cartoonshipGreen.png")){
        cout << "Error: Failed Load Asset\n";
        return -1;
    }
    // LOAD SHIP
    sf::Sprite ship(texture);
    ship.setScale({0.25f,0.25f});
    // yang dimaksud setOrigin tuh, origin dari object itu sendri
    sf::FloatRect boundsShip = ship.getLocalBounds();
    ship.setOrigin({boundsShip.size.x / 2.0f, boundsShip.size.y / 2.0f});

    // LOAD Peluru
    sf::CircleShape bullet(10.f);
    bullet.setFillColor(sf::Color::Yellow);

    // LOAD TEXT
    sf::String displayString = "Mainan Tembak tembak";
    sf::Text text(font, displayString,24);
    auto boundsText = text.getLocalBounds();
    text.setOrigin({
        boundsText.position.x + boundsText.size.x / 2.f,
        boundsText.position.y + boundsText.size.y / 2.f
    });
    text.setFillColor(sf::Color::White);

    // --------- SET OBJECT & TEXT KE TENGAH -------
    ship.setPosition({
                     static_cast<float>(windowSize.x)/2.f,
                     static_cast<float>(windowSize.y)/2.f
                     });
    text.setPosition({
                     static_cast<float>(windowSize.x)/2.f,
                     // static_cast<float>(windowsSize.x)/2.f
                     20}
                     );

    // LOAD MUSIC
    sf::Music music;
    if (!music.openFromFile("resources/music/aud1.mp3")){
        cout << "Error: Failed Load Music\n";
        return -1;
    }
    music.play();
    music.setVolume(50);

    struct Player
    {
        sf::Sprite sprite;
        float speed = 0.5f;
    };

    struct Bullet
    {
        sf::CircleShape shape;
        sf::Vector2f velocity;
    };

    Player ship;
    Bullet bullet;

    float angle = ship.sprite.getRotation().asDegrees();
    float radian = angle * 3.14159265f / 180.f;

    sf::Vector2f direction(
        std::cos(radian),
        std::sin(radian)
    );

    bullet.velocity = direction * speedBullet;

    float speed = 15.f;

    // ----------- RENDER GAME MAIN -----------
    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }

        // logika pergerakan
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            ship.move({0.f,-speed});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            ship.move({0.f,speed});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            ship.move({-speed,0.f});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            ship.move({speed,0.f});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            ship.move({0.f,-speed});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            ship.move({0.f,speed});

        // logika rotasi
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            ship.rotate(sf::degrees(-0.5));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            ship.rotate(sf::degrees(0.5));


        window.clear();

        window.draw(ship);

        window.draw(text);

        window.display();
    }

    return 0;
}
