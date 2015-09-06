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
        explicit Sprite(Renderer&);
        Sprite(const Sprite&) = delete;

        void load(const std::string&);
        void load(Surface&);

        const Rect& getRect() const {
            return _rect;
        }

        void setPosition(f32_t, f32_t);
        void setPosition(const Vector2f&);

        void move(f32_t, f32_t);
        void move(const Vector2f&);

        void rotate(f32_t rotation) {
            _rotation += rotation;
            if (_rotation > 360 || _rotation < -360)
                _rotation = 0;
        }

        void setRotation(f32_t rotation) {
            _rotation = rotation;
        }

        void scale(f32_t offset) {
            _scale += offset;
        }

        void setScale(f32_t offset) {
            _scale = offset;
        }

        void draw();

    private:
        Vector2f _position;
        f32_t _rotation = 0;
        f32_t _scale = 1;

        Renderer* _renderer;
        Texture _texture;
        Rect _rect;
    };
}

#endif
