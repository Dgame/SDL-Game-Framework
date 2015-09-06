#ifndef SDL_TEXTURE_HPP
#define SDL_TEXTURE_HPP

#include <string>

#include "types.hpp"

struct SDL_Texture;

namespace sdl {
    class Renderer;
    class Surface;

    struct Rect;
    struct Color;

    class Texture {
    public:
        Texture() = default;
        explicit Texture(SDL_Texture*);
        explicit Texture(Renderer&, const std::string&);
        explicit Texture(Renderer&, Surface&);
        explicit Texture(Renderer&, u16_t, u16_t, u32_t, u8_t);
        Texture(const Texture&) = delete;
        virtual ~Texture();

        void load(Renderer&, const std::string&);
        void load(Renderer&, Surface&);

        void query(u32_t*, u32_t*, u8_t* access = nullptr) const;

        SDL_Texture* raw() const {
            return _tex;
        }

        void* lock(const Rect* area = nullptr, i32_t* pitch = nullptr) const;
        void unlock() const;

        void update(const void*, const Rect*, i32_t) const;

        void setColorMod(const Color&) const;
        Color getColorMod() const;

        void setOpcacity(u8_t) const;
        u8_t getOpcacity() const;

        void setBlendMode(u8_t) const;
        u8_t getBlendMode() const;

        u32_t width() const {
            return _width;
        }

        u32_t height() const {
            return _height;
        }

    private:
        SDL_Texture* _tex = nullptr;

        u32_t _width = 0;
        u32_t _height = 0;
    };
}

#endif
