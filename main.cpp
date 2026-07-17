#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1080,720}),
        "SFML 3");

    // Load referensi font teks
    sf::Font font;
    if (!font.openFromFile("resources/fonts/arial.ttf")){
        return -1;
    }

    // Load texture
    sf::Texture texture;
    if (!texture.loadFromFile("resources/assets/cartoonshipGreen.png")){
        return -1;
    }

    // sprite nampel di texture
    sf::Sprite ship(texture);
    ship.setScale({0.5f,0.5f});
    sf::FloatRect boundsShip = ship.getLocalBounds();
    ship.setOrigin({boundsShip.size.x / 2.0f, boundsShip.size.y / 2.0f});

    // Inisiasi object shape yang digerakan
    //sf::RectangleShape shape(sf::Vector2(100.f,100.f));
    //shape.setFillColor(sf::Color::Green);
    //shape.setOrigin({50.f,50.f});

    // Inisiasi kecepatan gerak object
    float speed = 0.5f;
    float rotationVelocity = 90.f;

    // Inisiasi fungsi display teks pakai referensi teks
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

    // structure projectile
    struct Projectile{
        sf::CircleShape shape;
        sf::Vector2 velocity;
    };

    std::vector<Projectile> peluru;
    float speedPeluru = 600.f;


    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            ship.move({0.f,-speed});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            ship.move({0.f,speed});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            ship.move({-speed,0.f});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            ship.move({speed,0.f});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            ship.rotate(sf::degrees(-10));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            ship.rotate(sf::degrees(10));
        window.clear();

        window.draw(ship);

        window.draw(text);

        window.display();
    }

    return 0;
}
