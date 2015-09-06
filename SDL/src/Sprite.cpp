#include "Sprite.hpp"

#include "Renderer.hpp"
#include "Surface.hpp"

namespace sdl {
    Sprite::Sprite(Renderer& renderer) : _renderer(&renderer) {

    }

    void Sprite::load(const std::string& filename) {
        _texture = _renderer->createTexture(filename);

        _rect.width = _texture.width();
        _rect.height = _texture.height();
    }

    void Sprite::load(Surface& srfc) {
        _texture = _renderer->createTexture(srfc);

        _rect.width = _texture.width();
        _rect.height = _texture.height();
    }

    void Sprite::setPosition(f32_t x, f32_t y) {
        _position.x = x;
        _position.y = y;

        _rect.x = _position.x;
        _rect.y = _position.y;
    }

    void Sprite::setPosition(const Vector2f& pos) {
        this->setPosition(pos.x, pos.y);
    }

    void Sprite::move(f32_t dx, f32_t dy) {
        _position.x += dx;
        _position.y += dy;

        _rect.x = _position.x;
        _rect.y = _position.y;
    }

    void Sprite::move(const Vector2f& offset) {
        _position += offset;

        _rect.x = _position.x;
        _rect.y = _position.y;
    }

    void Sprite::draw() {
        _renderer->copy(_texture, &_rect, this->angle);
    }
}
