#include <../engine/engine.hpp>
#include <iostream>
#include <exception>

int main() {
    try {
        constexpr unsigned int WINDOW_WIDTH = 1080;
        constexpr unsigned int WINDOW_HEIGHT = 720;
        constexpr std::string_view WINDOW_TITLE = "Space Shooter v0.1 - Engine Core";

        Core::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        engine.run();
    }
    catch (const std::exception& e) {
        std::cerr << "[CRITICAL ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "[CRITICAL ERROR]: Unknown exception occurred!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
