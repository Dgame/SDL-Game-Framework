#include "Texture.hpp"
#include "Surface.hpp"
#include "Renderer.hpp"
#include "Rect.hpp"
#include "Color.hpp"

#include <SDL.h>
#include <iostream>

namespace sdl {
    Texture::Texture(SDL_Texture* tex) : _tex(tex) {

    }
    
    Texture::Texture(Renderer& renderer, const std::string& filename) {
        this->load(renderer, filename);
    }

    Texture::Texture(Renderer& renderer, Surface& srfc) {
        this->load(renderer, srfc);
    }

    Texture::Texture(Renderer& renderer, u16_t w, u16_t h, u32_t format, u8_t access) : _width(w), _height(h) {
        auto sdl_access = static_cast<SDL_TextureAccess>(access);

        _tex = SDL_CreateTexture(
            renderer.raw(),
            format,
            sdl_access,
            w, h
        );

        if (!_tex)
            std::cerr << "Error by creating a SDL_Texture*\n";
    }

    Texture::~Texture() {
        SDL_DestroyTexture(_tex);
    }

    void Texture::load(Renderer& renderer, const std::string& filename) {
        Surface srfc(filename);
        this->load(renderer, srfc);
    }

    void Texture::load(Renderer& renderer, Surface& srfc) {
        if (_tex)
            SDL_DestroyTexture(_tex);

        _width = srfc.width();
        _height = srfc.height();

        _tex = SDL_CreateTextureFromSurface(renderer.raw(), srfc.raw());
        if (!_tex)
            std::cerr << "Error by creating a SDL_Texture*\n";
    }

    void Texture::query(u32_t* w, u32_t* h, u8_t* access) const {
        i32_t my_w, my_h, sdl_access;

        SDL_QueryTexture(_tex, nullptr, &sdl_access, &my_w, &my_h);

        if (w)
            *w = my_w >= 0 ? my_w : 0;
        if (h)
            *h = my_h >= 0 ? my_h : 0;
        if (access)
            *access = static_cast<SDL_TextureAccess>(sdl_access);
    }

    void* Texture::lock(const Rect* area, i32_t* pitch) const {
        void* pixels;
        SDL_Rect rect;

        SDL_LockTexture(_tex, TryCopyInto(area, &rect), &pixels, pitch);

        return pixels;
    }

    void Texture::unlock() const {
        SDL_UnlockTexture(_tex);
    }

    void Texture::update(const void* pixels, const Rect* area, i32_t pitch) const {
        SDL_Rect rect;

        SDL_UpdateTexture(_tex, TryCopyInto(area, &rect), pixels, pitch);
    }

    void Texture::setColorMod(const Color& col) const {
        SDL_SetTextureColorMod(_tex, col.red, col.green, col.blue);
    }

    Color Texture::getColorMod() const {
        Color col;

        SDL_GetTextureColorMod(_tex, &col.red, &col.green, &col.blue);
        SDL_GetTextureAlphaMod(_tex, &col.alpha);

        return col;
    }

    void Texture::setOpcacity(u8_t alpha) const {
        SDL_SetTextureAlphaMod(_tex, alpha);
    }

    u8_t Texture::getOpcacity() const {
        u8_t alpha;

        SDL_GetTextureAlphaMod(_tex, &alpha);

        return alpha;
    }

    void Texture::setBlendMode(u8_t blend_mode) const {
        SDL_SetTextureBlendMode(_tex, static_cast<SDL_BlendMode>(blend_mode));
    }

    u8_t Texture::getBlendMode() const {
        SDL_BlendMode blend_mode;
        SDL_GetTextureBlendMode(_tex, &blend_mode);

        return blend_mode;
    }
}
