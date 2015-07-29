#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Surface.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "Renderer.hpp"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define R_MASK 0xff000000
#define G_MASK 0x00ff0000
#define B_MASK 0x0000ff00
#define A_MASK 0x000000ff
#else
#define R_MASK 0x000000ff
#define G_MASK 0x0000ff00
#define B_MASK 0x00ff0000
#define A_MASK 0xff000000
#endif

namespace sdl {
    Surface::Surface(u16_t w, u16_t h, u8_t d) {
        _srfc = SDL_CreateRGBSurface(0, w, h, d, R_MASK, G_MASK, B_MASK, A_MASK);
        if (!_srfc)
            std::cerr << "Invalid SDL_Surface*\n";
    }

    Surface::Surface(void* pixel_data, u16_t w, u16_t h, u8_t d) {
        const u16_t pitch = w * (d / 8);
        _srfc = SDL_CreateRGBSurfaceFrom(pixel_data, w, h, d, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
        if (!_srfc)
            std::cerr << "Invalid SDL_Surface*\n";
    }

    Surface::Surface(const std::string& filename) {
        _srfc = IMG_Load(filename.c_str());
        if (!_srfc)
            std::cerr << "Invalid SDL_Surface*\n";
    }

    Surface::Surface(SDL_Surface* srfc) : _srfc(srfc) {
        if (!srfc)
            std::cerr << "Invalid SDL_Surface*\n";
    }

    Surface::Surface(const Surface& other) {
        _srfc = other.get();
        if (_srfc)
            _srfc->refcount++;
        else
            std::cerr << "Invalid SDL_Surface*\n";
    }

    Surface::~Surface() {
        SDL_FreeSurface(_srfc);
    }

    Texture* Surface::asTextureOf(Renderer* renderer) const {
        return renderer->createTexture(_srfc, false);
    }

    void Surface::saveToFile(const char* filename) const {
        IMG_SavePNG(_srfc, filename);
    }

    void Surface::blit(const Surface& srfc, Rect* dst, const Rect* src) const {
        SDL_Rect sdl_src;
        SDL_Rect sdl_dst;

        SDL_BlitSurface(srfc.get(), TryCopyInto(src, &sdl_src), _srfc, TryCopyInto(dst, &sdl_dst));
    }

    u32_t Surface::width() const {
        return _srfc ? _srfc->w : 0;
    }

    u32_t Surface::height() const {
        return _srfc ? _srfc->h : 0;
    }

    void* Surface::pixels() const {
        return _srfc ? _srfc->pixels : nullptr;
    }

    SDL_PixelFormat* Surface::getFormat() const {
        return _srfc ? _srfc->format : nullptr;
    }

    Surface Surface::convert(const SDL_PixelFormat* fmt) const {
        return Surface(SDL_ConvertSurface(_srfc, fmt, 0));
    }

    void Surface::fill(const Color& col, const Rect* dst) const {
        if (_srfc) {
            SDL_Rect sdl_dst;

            SDL_FillRect(_srfc, TryCopyInto(dst, &sdl_dst), col.mapFor(_srfc->format));
        }
    }

    void Surface::setColorKey(const Color& col, bool enable) const {
        if (_srfc) {
            SDL_SetColorKey(_srfc, enable ? SDL_TRUE : SDL_FALSE, col.mapFor(_srfc->format));
        }
    }

    Color Surface::getColorKey() const {
        u32_t pixel = 0;

        if (_srfc) {
            SDL_GetColorKey(_srfc, &pixel);

            Color col;
            SDL_GetRGBA(pixel, _srfc->format, &col.red, &col.green, &col.blue, &col.alpha);

            return col;
        }

        return sdl::Color::Black;
    }

    void Surface::setColorMod(const Color& col) const {
        SDL_SetSurfaceColorMod(_srfc, col.red, col.green, col.blue);
        SDL_SetSurfaceAlphaMod(_srfc, col.alpha);
    }

    Color Surface::getColorMod() const {
        Color col;
        SDL_GetSurfaceColorMod(_srfc, &col.red, &col.green, &col.blue);
        SDL_GetSurfaceAlphaMod(_srfc, &col.alpha);

        return col;
    }

    void Surface::setBlendMode(u8_t blend_mode) const {
        SDL_SetSurfaceBlendMode(_srfc, static_cast<SDL_BlendMode>(blend_mode));
    }

    u8_t Surface::getBlendMode() const {
        SDL_BlendMode blend_mode;
        SDL_GetSurfaceBlendMode(_srfc, &blend_mode);

        return blend_mode;
    }
}
