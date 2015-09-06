#include "Renderer.hpp"
#include "Color.hpp"
#include "Surface.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

#include <SDL.h>
#include <iostream>

namespace sdl {
    Renderer::Renderer(SDL_Renderer* renderer) : _renderer(renderer, SDL_DestroyRenderer) {

    }

    void Renderer::setDrawColor(const Color& col) const {
        SDL_SetRenderDrawColor(_renderer.get(), col.red, col.green, col.blue, col.alpha);
    }

    Color Renderer::getDrawColor() const {
        Color col;
        SDL_GetRenderDrawColor(_renderer.get(), &col.red, &col.green, &col.blue, &col.alpha);

        return col;
    }

    void Renderer::clear(const Color* col) const {
        if (col)
            this->setDrawColor(*col);
        SDL_RenderClear(_renderer.get());
    }

    Texture Renderer::createTexture(const std::string& filename) {
        Surface srfc(filename);
        return this->createTexture(srfc);
    }

    Texture Renderer::createTexture(Surface& srfc) {
        SDL_Surface* raw = srfc.raw();
        SDL_Texture* sdl_tex = SDL_CreateTextureFromSurface(_renderer.get(), raw);
        if (!sdl_tex) {
            std::cerr << "Error by creating a SDL_Texture*\n";
        }

        return Texture(sdl_tex, raw->w, raw->h);
    }

    Texture Renderer::createTexture(u16_t w, u16_t h, u32_t format, u8_t access) {
        auto sdl_access = static_cast<SDL_TextureAccess>(access);

        SDL_Texture* sdl_tex = SDL_CreateTexture(
            _renderer.get(),
            format,
            sdl_access,
            w, h
        );

        if (!sdl_tex) {
            std::cerr << "Error by creating a SDL_Texture*\n";
        }

        return Texture(sdl_tex, w, h);
    }

    void Renderer::copy(Texture& tex, const Rect* dst, const Rect* src) const {
        SDL_Rect sdl_src;
        SDL_Rect sdl_dst;

        SDL_RenderCopy(
            _renderer.get(),
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
            _renderer.get(),
            tex.raw(),
            TryCopyInto(src, &sdl_src),
            TryCopyInto(dst, &sdl_dst),
            angle,
            TryCopyInto(center, &sdl_point),
            sdl_flip
        );
    }

    void Renderer::setRenderTarget(Texture& tex) const {
        SDL_SetRenderTarget(_renderer.get(), tex.raw());
    }

    void Renderer::setScale(f32_t sx, f32_t sy) const {
        SDL_RenderSetScale(_renderer.get(), sx, sy);
    }

    void Renderer::setScale(const Vector2f& scale) const {
        SDL_RenderSetScale(_renderer.get(), scale.x, scale.y);
    }

    Vector2f Renderer::getScale() const {
        Vector2f scale;
        SDL_RenderGetScale(_renderer.get(), &scale.x, &scale.y);

        return scale;
    }

    void Renderer::setViewport(const Rect* viewport) const {
        SDL_Rect rect;
        SDL_RenderSetViewport(_renderer.get(), TryCopyInto(viewport, &rect));
    }

    Rect Renderer::getViewport() const {
        SDL_Rect rect;
        SDL_RenderGetViewport(_renderer.get(), &rect);

        return Rect(rect.x, rect.y, rect.w, rect.h);
    }

    void Renderer::drawLine(const Vector2i& start, const Vector2i& end) const {
        SDL_RenderDrawLine(_renderer.get(), start.x, start.y, end.x, end.y);
    }

    void Renderer::drawPoint(const Vector2i& vec) const {
        SDL_RenderDrawPoint(_renderer.get(), vec.x, vec.y);
    }

    void Renderer::drawRect(const Rect& rect) const {
        SDL_Rect sdl_rect;
        SDL_RenderDrawRect(_renderer.get(), rect.copyInto(&sdl_rect));
    }

    void Renderer::fillRect(const Rect& rect) const {
        SDL_Rect sdl_rect;
        SDL_RenderFillRect(_renderer.get(), rect.copyInto(&sdl_rect));
    }

    void Renderer::setBlendMode(u8_t blend_mode) const {
        SDL_SetRenderDrawBlendMode(_renderer.get(), static_cast<SDL_BlendMode>(blend_mode));
    }

    u8_t Renderer::getBlendMode() const {
        SDL_BlendMode blend_mode;
        SDL_GetRenderDrawBlendMode(_renderer.get(), &blend_mode);

        return blend_mode;
    }

    void Renderer::present() const {
        SDL_RenderPresent(_renderer.get());
    }
}
