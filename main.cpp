#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
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
    ship.setPosition({
                     window.getSize().x / 2.0f,
                     window.getSize().y / 2.0f
                     });
    sf::Vector2f shipPosition = ship.getPosition();

    // LOAD PELURU
    sf::CircleShape bullet(0.1f);
    bullet.setFillColor(sf::Color::Yellow);
    struct Bullet{
        sf::CircleShape shape;
        sf::Vector2f velocity;
    };
    sf::FloatRect boundsBullet = bullet.getLocalBounds();
    bullet.setOrigin({boundsBullet.size.x/2.0f, boundsBullet.size.y/2.0f});
    sf::Vector2f bulletPosition({shipPosition.x + 5.0f, shipPosition.y});

    std::vector<Bullet> bullets;

    sf::Clock fireClock;
    const float fireRate = 0.2f;

    sf::Clock deltaClock;

    // LOAD TEXT
    sf::String displayString = "Mainan Tembak tembak";
    sf::Text text(font, displayString,24);
    auto boundsText = text.getLocalBounds();
    text.setOrigin({boundsText.position.x + boundsText.size.x / 2.f, boundsText.position.y + boundsText.size.y / 2.f});
    text.setFillColor(sf::Color::White);

    // --------- SET OBJECT & TEXT KE TENGAH -------
    ship.setPosition({static_cast<float>(windowSize.x)/2.f, static_cast<float>(windowSize.y)/2.f});
    text.setPosition({static_cast<float>(windowSize.x)/2.f, static_cast<float>(windowSize.y)/6.f});
    // static_cast<float>(windowsSize.x)/2.f

    // LOAD MUSIC uncomment shift+ctrl+x
//    sf::Music music;
//    if (!music.openFromFile("resources/music/aud1.mp3")){
//        cout << "Error: Failed Load Music\n";
//        return -1;
//    }
//    music.play();
//    music.setVolume(50);

    float speed = 1.f;

    // ----------- RENDER GAME MAIN -----------
    while(window.isOpen())
    {
        float dt = deltaClock.restart().asSeconds();

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

        // logika rotasi (nengok)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            ship.rotate(sf::degrees(-0.5));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            ship.rotate(sf::degrees(0.5));

        // rencananya buat fungsi puter 180, tapi perlu tambahin motion muternya biar ga langsung
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//            ship.rotate(sf::degrees(180.f));
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//            ship.rotate(sf::degrees(180.f));
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//            float.bullet(ship.x, ship.y - offset);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&& fireClock.getElapsedTime().asSeconds()>=fireRate)
        {
            window.draw(bullet);// spawn bullet dan tembak ke arah yang dilihat oleh object

            // sudut rotasi kapal dalam radian
            float angleRad = ship.getRotation().asRadians();

            // kecepatan peluru
            float bulletSpeed = 500.f;

            // hitung arah vektor bergerak maju
            sf::Vector2f bulletVelocity(
                std::sin(angleRad) * speed,
                -std::cos(angleRad) * speed
                                        );
            // moncong depan kapal
            float offset = (boundsShip.size.y * ship.getScale().y)/ 2.0f;
            sf::Vector2f spawnPos = {
                ship.getPosition().x + offset * std::sin(angleRad),
                ship.getPosition().y - offset * std::cos(angleRad)
                };

            Bullet newBullet;
            newBullet.shape.setRadius(5.f);
            newBullet.shape.setFillColor(sf::Color::Yellow);
            newBullet.shape.setOrigin ({5.f,5.f});
            newBullet.shape.setPosition(spawnPos);
            newBullet.velocity = bulletVelocity;

            // masuk magazine
            bullets.push_back(newBullet);

            // rest cooldown temban
            fireClock.restart();
        }

        // gerakan peluru
        for (auto& b : bullets){
            b.shape.move(b.velocity*dt);
        }

        // Render gambar
        window.clear(sf::Color::Black);

        window.draw(ship);

        window.draw(text);

        for(const auto& b: bullets){
            window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}
