#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Window.hpp"

#include "Vector2.hpp"
#include "Rect.hpp"
#include "Surface.hpp"
#include "Renderer.hpp"
#include "Color.hpp"

namespace {
    void _initSDL() {
        SDL_Init(SDL_INIT_VIDEO);
        // load support for the JPG and PNG image formats
        const i32_t flags = IMG_INIT_JPG | IMG_INIT_PNG;
        const i32_t initted = IMG_Init(flags);
        if ((initted & flags) != flags) {
            std::cerr << "IMG_Init: Failed to init required jpg and png support!" << std::endl;
            std::cerr << "IMG_Init: " << IMG_GetError() << std::endl;
        }
        // Load support for TTF
        if (TTF_Init() == -1) {
            std::cerr << "TTF_Init: failed: " << TTF_GetError() << std::endl;
        }
    }
}

namespace sdl {
    u16_t Window::_wnd_count = 0;

    Window::Window(const std::string& title, const Vector2i& pos, u32_t w, u32_t h, u32_t flags) {
        if (_wnd_count == 0)
            _initSDL();

        _wnd_count++;

        _wnd = SDL_CreateWindow(
            title.c_str(),
            pos.x, pos.y,
            w, h,
            flags
        );

        if (!_wnd)
            std::cerr << "Error by creating a SDL_Window*\n";
    }

    Window::~Window() {
        for (Renderer* rend : _renderer) {
            delete rend;
        }

        SDL_DestroyWindow(_wnd);

        _wnd_count--;
        if (_wnd_count == 0) {
            // unload the dynamically loaded image libraries
            IMG_Quit();
            SDL_Quit();
        }
    }

    Renderer* Window::createRenderer(u32_t flags, i16_t driver_index) {
        Renderer* my_renderer = new Renderer(_wnd, flags, driver_index);
        _renderer.emplace_back(my_renderer);

        return my_renderer;
    }

    void Window::clear(const Color& col) const {
        SDL_Surface* wnd_srfc = SDL_GetWindowSurface(_wnd);
        SDL_FillRect(wnd_srfc, nullptr, col.mapFor(wnd_srfc->format));
    }

    void Window::display() const {
        SDL_UpdateWindowSurface(_wnd);
    }

    void Window::blit(Surface& srfc, Rect* dst, const Rect* src) const {
        SDL_Surface* wnd_srfc = SDL_GetWindowSurface(_wnd);

        SDL_Rect sdl_src;
        SDL_Rect sdl_dst;

        SDL_BlitSurface(srfc.get(), TryCopyInto(src, &sdl_src), wnd_srfc, TryCopyInto(dst, &sdl_dst));
    }

    void Window::setTitle(const char* title) const {
        SDL_SetWindowTitle(_wnd, title);
    }

    const char* Window::getTitle() const {
        return SDL_GetWindowTitle(_wnd);
    }

    void Window::setSize(u32_t w, u32_t h) const {
        SDL_SetWindowSize(_wnd, w, h);
    }

    void Window::fetchSize(u32_t* w, u32_t* h) const {
        i32_t tw, th;
        SDL_GetWindowSize(_wnd, &tw, &th);

        if (w)
            *w = tw >= 0 ? tw : 0;
        if (h)
            *h = th >= 0 ? th : 0;
    }

    u32_t Window::width() const {
        u32_t w;
        this->fetchSize(&w, nullptr);

        return w;
    }

    u32_t Window::height() const {
        u32_t h;
        this->fetchSize(nullptr, &h);

        return h;
    }

    void Window::setPosition(u32_t cx, u32_t cy) const {
        SDL_SetWindowPosition(_wnd, cx, cy);
    }

    void Window::setPosition(const Vector2i& pos) const {
        SDL_SetWindowPosition(_wnd, pos.x, pos.y);
    }

    Vector2i Window::getPosition() const {
        Vector2i pos;
        SDL_GetWindowPosition(_wnd, &pos.x, &pos.y);

        return pos;
    }

    u32_t Window::getID() const {
        return SDL_GetWindowID(_wnd);
    }

    i32_t Window::getDisplayIndex() const {
        return SDL_GetWindowDisplayIndex(_wnd);
    }

    Rect Window::getDisplayBounds() const {
        const i32_t index = this->getDisplayIndex();

        Rect rect;
        if (index >= 0) {
            SDL_Rect sdl_rect;
            SDL_GetDisplayBounds(index, &sdl_rect);

            rect.x = sdl_rect.x;
            rect.y = sdl_rect.y;
            rect.width = sdl_rect.w;
            rect.height = sdl_rect.h;
        }

        return rect;
    }

    void Window::show() const {
        SDL_ShowWindow(_wnd);
    }

    void Window::hide() const {
        SDL_HideWindow(_wnd);
    }

    void Window::focus() const {
        SDL_RaiseWindow(_wnd);
    }

    void Window::restore() const {
        SDL_RestoreWindow(_wnd);
    }

    void Window::minimize() const {
        SDL_MinimizeWindow(_wnd);
    }

    void Window::maximize() const {
        SDL_MaximizeWindow(_wnd);
    }

    void Window::setBorder(bool use_border) const {
        SDL_SetWindowBordered(_wnd, use_border ? SDL_TRUE : SDL_FALSE);
    }

    void Window::setIcon(const Surface& srfc) const {
        SDL_SetWindowIcon(_wnd, srfc.get());
    }

    u32_t Window::getFlags() const {
        return SDL_GetWindowFlags(_wnd);
    }

    void Window::setFullscreen(u32_t flags) const {
        // TODO: check for correct Flags?
        SDL_SetWindowFullscreen(_wnd, flags);
    }
}
