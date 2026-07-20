#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

//int main()
//{
//    // ----------- LOAD RESOURCES -----------
//    // RENDER WINDOW
//    sf::RenderWindow window(
//        sf::VideoMode({1080,720}),
//        "SFML 3");
//    sf::Vector2 windowSize= window.getSize();
//    // LOAD FONT
//    sf::Font font;
//    if (!font.openFromFile("resources/font/arial.ttf")){
//        cout << "Error: Failed Load Font\n";
//        return -1;
//    }
//    // LOAD TEXTURE
//    sf::Texture texture;
//    if (!texture.loadFromFile("resources/asset/cartoonshipGreen.png")){
//        cout << "Error: Failed Load Asset\n";
//        return -1;
//    }
//    // LOAD SHIP
//    sf::Sprite ship(texture);
//    ship.setScale({0.25f,0.25f});
//    // yang dimaksud setOrigin tuh, origin dari object itu sendri
//    sf::FloatRect boundsShip = ship.getLocalBounds();
//    ship.setOrigin({boundsShip.size.x / 2.0f, boundsShip.size.y / 2.0f});
//
//    // LOAD Peluru
//    sf::CircleShape bullet(10.f);
//    bullet.setFillColor(sf::Color::Yellow);
//
//    // LOAD TEXT
//    sf::String displayString = "Mainan Tembak tembak";
//    sf::Text text(font, displayString,24);
//    auto boundsText = text.getLocalBounds();
//    text.setOrigin({
//        boundsText.position.x + boundsText.size.x / 2.f,
//        boundsText.position.y + boundsText.size.y / 2.f
//    });
//    text.setFillColor(sf::Color::White);
//
//    // --------- SET OBJECT & TEXT KE TENGAH -------
//    ship.setPosition({
//                     static_cast<float>(windowSize.x)/2.f,
//                     static_cast<float>(windowSize.y)/2.f
//                     });
//    text.setPosition({
//                     static_cast<float>(windowSize.x)/2.f,
//                     // static_cast<float>(windowsSize.x)/2.f
//                     20}
//                     );
//
//    // LOAD MUSIC
//    sf::Music music;
//    if (!music.openFromFile("resources/music/aud1.mp3")){
//        cout << "Error: Failed Load Music\n";
//        return -1;
//    }
//    music.play();
//    music.setVolume(50);
//
//    float speed = 1.f;
//    float offset = 20.f;
//
//    // ----------- RENDER GAME MAIN -----------
//    while(window.isOpen())
//    {
//        while(const std::optional event = window.pollEvent())
//        {
//            if(event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // logika pergerakan
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
//            ship.move({0.f,-speed});
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
//            ship.move({0.f,speed});
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
//            ship.move({-speed,0.f});
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//            ship.move({speed,0.f});
//
//        // logika rotasi
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//            ship.rotate(sf::degrees(-0.5));
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//            ship.rotate(sf::degrees(0.5));
//
//        // rencananya buat fungsi puter 180, tapi perlu tambahin motion muternya biar ga langsung
////        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
////            ship.rotate(sf::degrees(180.f));
////        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
////            ship.rotate(sf::degrees(180.f));
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//            float.bullet(ship.x, ship.y - offset);
//
//        window.clear();
//
//        window.draw(ship);
//
//        window.draw(text);
//
//        window.display();
//    }
//
//    return 0;
//}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Origin Alignment");

    // Create Object A (The object whose origin will change)
    sf::CircleShape objectA(sf::Vector2f({50.f}));
    objectA.setFillColor(sf::Color::Blue);
    objectA.setPosition({400.f, 300.f});

    // Create Object B (The reference point)
    sf::CircleShape objectB({10.f});
    objectB.setFillColor(sf::Color::Red);
    objectB.setPosition({500.f, 400.f});

    // 1. Get global positions as vectors
    sf::Vector2f posA = objectA.getPosition();
    sf::Vector2f posB = objectB.getPosition();

    // 2. Calculate the relative offset vector
    sf::Vector2f localOffset = posA - posB;

    // 3. Set the new origin
    objectA.setOrigin(localOffset);

    // Optional: Reset position to Object B if you want Object A
    // to visually snap and pivot directly on top of Object B
    objectA.setPosition(posB);

    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }

    while(window.isOpen()){
            while(const std::optional event = window.pollEvent())
            {
                if(event->is<sf::Event::Closed>())
                window.close();
            }

        // Object A will now rotate perfectly around Object B's position
        objectA.rotate(0.1f);

        window.clear();
        window.draw(objectA);
        window.draw(objectB);
        window.display();
    }

    return 0;
}
