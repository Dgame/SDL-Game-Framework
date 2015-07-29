#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include <vector>
#include "types.hpp"

#include "Vector2.hpp"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

namespace sdl {
    class Texture;

    struct Color;
    struct Rect;

    class Renderer {
    public:
        explicit Renderer(SDL_Window*, u8_t, i16_t driver_index = -1);
        Renderer(const Renderer&) = delete;
        virtual ~Renderer();

        void setDrawColor(const Color&) const;
        Color getDrawColor() const;

        void clear(const Color* col = nullptr) const;

        Texture* createTexture(SDL_Surface*, bool);
        Texture* createTexture(u16_t, u16_t, u32_t, u8_t);

        void copy(Texture*, const Rect*, const Rect* src = nullptr) const;
        void copy(Texture*, const Rect*, f64_t, const Rect* src = nullptr, const Vector2i* center = nullptr, u8_t flip = 0) const;

        void setRenderTarget(Texture*) const;

        void setScale(f32_t, f32_t) const;
        void setScale(const Vector2f&) const;
        Vector2f getScale() const;

        void setViewport(const Rect*) const;
        Rect getViewport() const;

        void drawLine(const Vector2i&, const Vector2i&) const;
        // void drawLines(const Vector2i*, u32_t) const;

        void drawPoint(const Vector2i&) const;
        // void drawPoints(const Vector2i*, u32_t) const;

        void drawRect(const Rect&) const;
        // void drawRects(const Rect*, u32_t) const;

        void fillRect(const Rect&) const;
        // void fillRects(const Rect*, u32_t) const;

        void setBlendMode(u8_t) const;
        u8_t getBlendMode() const;

        void present() const;

    private:
        SDL_Renderer* _renderer;
        std::vector<Texture*> _textures;
    };
}

#endif
