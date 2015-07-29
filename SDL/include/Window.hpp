#ifndef SDL_GAME_WINDOW_HPP
#define SDL_GAME_WINDOW_HPP

#include <string>
#include <vector>

#include "types.hpp"

#include "Vector2.hpp"

struct SDL_Window;

namespace sdl {
    struct Rect;

    class Surface;
    class Renderer;
    class Color;

    class Window {
    public:
        explicit Window(const std::string&, const Vector2i&, u32_t, u32_t, u32_t flags = 0);
        Window(const Window&) = delete;
        virtual ~Window();

        Renderer* createRenderer(u32_t, i16_t driver_index = -1);

        void clear(const Color&) const;

        void display() const;
        void blit(Surface&, Rect* dst = nullptr, const Rect* src = nullptr) const;

        void setTitle(const char*) const;
        const char* getTitle() const;

        void setSize(u32_t, u32_t) const;
        void fetchSize(u32_t*, u32_t*) const;

        u32_t width() const;
        u32_t height() const;

        void setPosition(u32_t, u32_t) const;
        void setPosition(const Vector2i&) const;
        Vector2i getPosition() const;

        u32_t getID() const;

        i32_t getDisplayIndex() const;
        Rect getDisplayBounds() const;

        void show() const;
        void hide() const;
        void focus() const;
        void restore() const;
        void minimize() const;
        void maximize() const;

        void setBorder(bool) const;
        void setIcon(const Surface&) const;

        u32_t getFlags() const;
        void setFullscreen(u32_t) const;

    private:
        static u16_t _wnd_count;

        SDL_Window* _wnd;
        std::vector<Renderer*> _renderer;
    };
} // end namespace

#endif
