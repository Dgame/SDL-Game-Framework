#include "Sprite.hpp"

#include "Renderer.hpp"
#include "Texture.hpp"
#include "Surface.hpp"

namespace sdl {
    Sprite::Sprite(Renderer* renderer) : _renderer(renderer) { }

    void Sprite::load(const std::string& filename) {
        _texture = _renderer->createTexture(filename);

        _rect.width = _texture.width();
        _rect.height = _texture.height();
    }

    void Sprite::load(const Surface& srfc) {
        _texture = _renderer->createTexture(srfc);

        _rect.width = _texture.width();
        _rect.height = _texture.height();
    }

    void Sprite::move(f32_t dx, f32_t dy) {
        this->position.x += dx;
        this->position.y += dy;

        _rect.x = this->position.x;
        _rect.y = this->position.y;
    }

    void Sprite::move(const Vector2f& offset) {
        this->position += offset;

        _rect.x = this->position.x;
        _rect.y = this->position.y;
    }

    void Sprite::draw() const {
        _renderer->copy(_texture, _rect, this->angle);
    }
}
