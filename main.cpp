#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1080,720}),
        "SFML 3");

    // Load referensi font teks
    sf::Font font;
    if (!font.openFromFile("resources/font/arial.ttf")){
        return -1;
    }

    // Load texture
    sf::Texture texture;
    if (!texture.loadFromFile("resources/asset/cartoonshipGreen.png")){
        return -1;
    }

    // Sprite nampel di texture
    sf::Sprite ship(texture);
    ship.setScale({0.5f,0.5f});
    sf::FloatRect boundsShip = ship.getLocalBounds();
    ship.setOrigin({boundsShip.size.x / 2.0f, boundsShip.size.y / 2.0f});

    // Inisiasi object shape yang digerakan
    //sf::RectangleShape shape(sf::Vector2(100.f,100.f));
    //shape.setFillColor(sf::Color::Green);
    //shape.setOrigin({50.f,50.f});

    // Inisiasi display teks
    sf::String displayString = "Mainan Tembak tembak";
    // format: sf::Text 'nama variabel' "namaFont, variabelTeks, ukuran"
    sf::Text text(font, displayString,24);

    auto boundsText = text.getLocalBounds();

    text.setOrigin({
        boundsText.position.x + boundsText.size.x / 2.f,
        boundsText.position.y + boundsText.size.y / 2.f
    });

    text.setFillColor(sf::Color::White);
    text.setPosition({50.f,50.f});

     // nengahin posisi teks
    text.setPosition({
        1080.f - boundsText.size.x / 2.f,
        720.f - boundsText.size.y / 2.f
    });

    // structure proyektil peluru
    struct projectile{
        sf::CircleShape shape;
        sf::Vector2f velocity;
    };

    std::vector<projectile> bullets;
    float bulletSpeed = 600.f;

    // stucture ship
    struct ship {
        // Sprite nampel di texture
        sf::Sprite object(texture);
        object.setScale({0.5f,0.5f});
        sf::FloatRect boundsObject= object.getLocalBounds();
        object.setOrigin({boundsObject.size.x / 2.0f, boundsObject.size.y / 2.0f});

        sf::Vector2f position;
        float rotation;

        // kecepatan gerak objek
        float speed = 0.5f;

        // kecepatan rotasi objek
        float rotationVelocity = 90.f;
    };


    // inisiasi musik
    sf::Music lagu;
    if (!lagu.openFromFile("resources/music/aud1.mp3")){
        std::cout << "Error: Failed Load Music\n";
        return -1;
    }

    // buka window
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

        // logika rotasi
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            ship.rotate(sf::degrees(-2.f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            ship.rotate(sf::degrees(2.f));



        if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Space) {
            Projectile peluruBaru;
            peluruBaru.shape.setRadius(5.f);
            peluruBaru.shape.setFillColor(sf::Color::Yellow);

            // Spawn di posisi ship
            peluruBaru.shape.setPosition(ship.getPosition());

            // Set direction (e.g., shooting straight up)
            peluruBaru.velocity = sf::Vector2f(0.f, -1.f) * speedPeluru;

            peluru.push_back(peluruBaru);
        };

        for (auto& peluru : peluru){
            peluru.shape.move(peluru.velocity)
        }

        window.clear();

        window.draw(ship);

        window.draw(text);

        window.display();
    }

    return 0;
}
