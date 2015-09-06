#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"

#include <SDL.h>
#include <iostream>

namespace sdl {
    Texture::Texture(SDL_Texture* tex, u32_t w, u32_t h) : _tex(tex, SDL_DestroyTexture), _width(w), _height(h) {
        if (!tex)
            std::cerr << "Invalid SDL_Texture*\n";
    }

    void Texture::query(u32_t* w, u32_t* h, u8_t* access) const {
        i32_t my_w, my_h, sdl_access;

        SDL_QueryTexture(_tex.get(), nullptr, &sdl_access, &my_w, &my_h);

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

        SDL_LockTexture(_tex.get(), TryCopyInto(area, &rect), &pixels, pitch);

        return pixels;
    }

    void Texture::unlock() const {
        SDL_UnlockTexture(_tex.get());
    }

    void Texture::update(const void* pixels, const Rect* area, i32_t pitch) const {
        SDL_Rect rect;

        SDL_UpdateTexture(_tex.get(), TryCopyInto(area, &rect), pixels, pitch);
    }

    void Texture::setColorMod(const Color& col) const {
        SDL_SetTextureColorMod(_tex.get(), col.red, col.green, col.blue);
    }

    Color Texture::getColorMod() const {
        Color col;

        SDL_GetTextureColorMod(_tex.get(), &col.red, &col.green, &col.blue);
        SDL_GetTextureAlphaMod(_tex.get(), &col.alpha);

        return col;
    }

    void Texture::setOpcacity(u8_t alpha) const {
        SDL_SetTextureAlphaMod(_tex.get(), alpha);
    }

    u8_t Texture::getOpcacity() const {
        u8_t alpha;

        SDL_GetTextureAlphaMod(_tex.get(), &alpha);

        return alpha;
    }

    void Texture::setBlendMode(u8_t blend_mode) const {
        SDL_SetTextureBlendMode(_tex.get(), static_cast<SDL_BlendMode>(blend_mode));
    }

    u8_t Texture::getBlendMode() const {
        SDL_BlendMode blend_mode;
        SDL_GetTextureBlendMode(_tex.get(), &blend_mode);

        return blend_mode;
    }
}
