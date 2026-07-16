#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800,600}),
        "SFML 3");
    // Load referensi font teks
    sf::Font font;
    if (!font.openFromFile("resources/fonts/arial.ttf")){
        return -1;
    }

    // Inisiasi object shape yang digerakan
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    // Inisiasi kecepatan gerak object
    float speed = 0.5f;


    // Inisiasi fungsi display teks pakai referensi teks
    sf::String displayString = "Hello World";
    // format: sf::Text 'nama variabel' "namaFont, variabelTeks, ukuran"
    sf::Text text(font, displayString,24);

    auto bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    text.setFillColor(sf::Color::White);
    text.setPosition({50.f,50.f});

     // nengahin posisi teks
    text.setPosition({
        400.f - bounds.size.x / 2.f,
        300.f - bounds.size.y / 2.f
    });

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            shape.move({0.f,-speed});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            shape.move({0.f,speed});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            shape.move({-speed,0.f});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            shape.move({speed,0.f});

        window.clear();

        window.draw(shape);

        window.draw(text);

        window.display();
    }

    return 0;
}
