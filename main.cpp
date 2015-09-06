#include "SDL/include/Window.hpp"
#include "SDL/include/Renderer.hpp"
#include "SDL/include/Event.hpp"
#include "SDL/include/Color.hpp"
#include "SDL/include/Sprite.hpp"

int main() {
    sdl::Window wnd("Test - App", sdl::Vector2i(100, 100), 640, 480);
    sdl::Renderer renderer(wnd, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // renderer.setDrawColor(sdl::Color::White);

    sdl::Sprite quad(renderer);
    quad.load("quad.png");
    quad.setPosition(100, 100);

    bool running = true;
    sdl::Event event;

    while (running) {
        renderer.clear();

        while (running && sdl::PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                break;

                case SDL_KEYDOWN:
                    quad.move(5, -5);
                    quad.rotate(22.5);

                    if (event.keyboard.key == SDLK_ESCAPE) {
                        running = false;
                    }
                break;
            }
        }

        quad.draw();

        renderer.present();
    }
}
