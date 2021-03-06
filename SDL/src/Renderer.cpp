#include "Renderer.hpp"
#include "Window.hpp"
#include "Surface.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

#include <SDL.h>
#include <iostream>

namespace sdl {
    Renderer::Renderer(Window& wnd, u32_t flags, i16_t driver_index) {
        _renderer = SDL_CreateRenderer(wnd.raw(), driver_index, flags);
    }

    Renderer::~Renderer() {
        SDL_DestroyRenderer(_renderer);
    }

    void Renderer::setDrawColor(const Color& col) const {
        SDL_SetRenderDrawColor(_renderer, col.red, col.green, col.blue, col.alpha);
    }

    Color Renderer::getDrawColor() const {
        Color col;
        SDL_GetRenderDrawColor(_renderer, &col.red, &col.green, &col.blue, &col.alpha);

        return col;
    }

    void Renderer::clear(const Color* col) const {
        if (col)
            this->setDrawColor(*col);
        SDL_RenderClear(_renderer);
    }

    void Renderer::copy(Texture& tex, const Rect* dst, const Rect* src) const {
        SDL_Rect sdl_src;
        SDL_Rect sdl_dst;

        SDL_RenderCopy(
            _renderer,
            tex.raw(),
            TryCopyInto(src, &sdl_src),
            TryCopyInto(dst, &sdl_dst)
        );
    }

    void Renderer::copy(Texture& tex, const Rect* dst, f64_t angle, const Rect* src, const Vector2i* center, u8_t flip) const {
        auto sdl_flip = static_cast<SDL_RendererFlip>(flip);

        SDL_Rect sdl_src;
        SDL_Rect sdl_dst;
        SDL_Point sdl_point;

        SDL_RenderCopyEx(
            _renderer,
            tex.raw(),
            TryCopyInto(src, &sdl_src),
            TryCopyInto(dst, &sdl_dst),
            angle,
            TryCopyInto(center, &sdl_point),
            sdl_flip
        );
    }

    void Renderer::setRenderTarget(Texture& tex) const {
        SDL_SetRenderTarget(_renderer, tex.raw());
    }

    void Renderer::setScale(f32_t sx, f32_t sy) const {
        SDL_RenderSetScale(_renderer, sx, sy);
    }

    void Renderer::setScale(const Vector2f& scale) const {
        SDL_RenderSetScale(_renderer, scale.x, scale.y);
    }

    Vector2f Renderer::getScale() const {
        Vector2f scale;
        SDL_RenderGetScale(_renderer, &scale.x, &scale.y);

        return scale;
    }

    void Renderer::setViewport(const Rect* viewport) const {
        SDL_Rect rect;
        SDL_RenderSetViewport(_renderer, TryCopyInto(viewport, &rect));
    }

    Rect Renderer::getViewport() const {
        SDL_Rect rect;
        SDL_RenderGetViewport(_renderer, &rect);

        return Rect(rect.x, rect.y, rect.w, rect.h);
    }

    void Renderer::drawLine(const Vector2i& start, const Vector2i& end) const {
        SDL_RenderDrawLine(_renderer, start.x, start.y, end.x, end.y);
    }

    void Renderer::drawPoint(const Vector2i& vec) const {
        SDL_RenderDrawPoint(_renderer, vec.x, vec.y);
    }

    void Renderer::drawRect(const Rect& rect) const {
        SDL_Rect sdl_rect;
        SDL_RenderDrawRect(_renderer, rect.copyInto(&sdl_rect));
    }

    void Renderer::fillRect(const Rect& rect) const {
        SDL_Rect sdl_rect;
        SDL_RenderFillRect(_renderer, rect.copyInto(&sdl_rect));
    }

    void Renderer::setBlendMode(u8_t blend_mode) const {
        SDL_SetRenderDrawBlendMode(_renderer, static_cast<SDL_BlendMode>(blend_mode));
    }

    u8_t Renderer::getBlendMode() const {
        SDL_BlendMode blend_mode;
        SDL_GetRenderDrawBlendMode(_renderer, &blend_mode);

        return blend_mode;
    }

    void Renderer::present() const {
        SDL_RenderPresent(_renderer);
    }
}
