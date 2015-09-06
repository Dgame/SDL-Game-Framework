#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include <string>
#include <memory>

#include "types.hpp"
#include "Vector2.hpp"
#include "Texture.hpp"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

namespace sdl {
    class Surface;

    struct Color;
    struct Rect;

    class Renderer {
    public:
        Renderer() = default;
        explicit Renderer(SDL_Renderer*);

        void setDrawColor(const Color&) const;
        Color getDrawColor() const;

        void clear(const Color* col = nullptr) const;

        Texture createTexture(const std::string&);
        Texture createTexture(Surface&);
        Texture createTexture(u16_t, u16_t, u32_t, u8_t);

        void copy(Texture&, const Rect*, const Rect* src = nullptr) const;
        void copy(Texture&, const Rect*, f64_t, const Rect* src = nullptr, const Vector2i* center = nullptr, u8_t flip = 0) const;

        void setRenderTarget(Texture&) const;

        void setScale(f32_t, f32_t) const;
        void setScale(const Vector2f&) const;
        Vector2f getScale() const;

        void setViewport(const Rect*) const;
        Rect getViewport() const;

        void drawLine(const Vector2i&, const Vector2i&) const;
        void drawPoint(const Vector2i&) const;
        void drawRect(const Rect&) const;
        void fillRect(const Rect&) const;

        void setBlendMode(u8_t) const;
        u8_t getBlendMode() const;

        void present() const;

    private:
        std::shared_ptr<SDL_Renderer> _renderer;
    };
}

#endif
