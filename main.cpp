#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameplay.hpp"

int main() {
    Game gameplay;

    // 1. Buat Jendela
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Main Menu Space Shooter");

    // 2. Buat Kotak Tombol
    sf::RectangleShape button(sf::Vector2f(200.f, 50.f));
    button.setPosition(300.f, 250.f);
    button.setFillColor(sf::Color::Green);

    // 3. Muat Font dan Teks Tombol
    sf::Font font;
    if (!font.loadFromFile("/resources/font/arial.ttf")) {
        std::cout << "Gagal memuat font!" << std::endl;
        return -1;
    }

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Start");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(335.f, 260.f);

    // 4. Loop Utama
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // 5. Cek Aksi Klik Mouse
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Ambil posisi kursor mouse
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Periksa apakah kursor berada di dalam area tombol
                    if (button.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Tombol berhasil diklik!" << std::endl;
                    }
                }
            }
        }

        // 6. Render Gambar ke Jendela
        window.clear(sf::Color::Black);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
