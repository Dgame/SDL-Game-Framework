#ifndef SDL_SPRITE_HPP
#define SDL_SPRITE_HPP

#include <string>

#include "Rect.hpp"
#include "Texture.hpp"

#include "types.hpp"
#include "Vector2.hpp"

namespace sdl {
    class Renderer;
    class Surface;

    class Sprite {
    public:
        f32_t angle = 0;
        f32_t rotation = 0;
        f32_t scale = 1;

        explicit Sprite(Renderer&);

        void load(const std::string&);
        void load(Surface&);

        void draw();

        const Rect& getRect() const {
            return _rect;
        }

        void setPosition(f32_t, f32_t);
        void setPosition(const Vector2f&);

        void move(f32_t, f32_t);
        void move(const Vector2f&);

    private:
        Vector2f _position;
        Renderer* _renderer;
        Texture _texture;
        Rect _rect;
    };
}

#endif
