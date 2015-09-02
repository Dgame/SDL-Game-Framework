#ifndef SDL_SPRITE_HPP
#define SDL_SPRITE_HPP

#include <string>

#include "types.hpp"
#include "Vector2.hpp"

namespace sdl {
    class Renderer;
    class Texture;
    class Surface;

    class Sprite {
    public:
        Vector2f position;
        f32_t rotation = 0;
        f32_t scale = 1;

        explicit Sprite(Renderer*);

        void load(const std::string&);
        void load(const Surface&);

        void draw() const;

        const Rect& getRect() const {
            return _rect;
        }

        void move(f32_t dx, f32_t dy);
        void move(const Vector2f& offset);

    private:
        Renderer* _renderer;
        Texture* _texture;
        Rect* _rect;
    };
}

#endif
