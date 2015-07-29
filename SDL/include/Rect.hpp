#ifndef SDL_RECT_HPP
#define SDL_RECT_HPP

#include "types.hpp"

#include "Vector2.hpp"

struct SDL_Rect;

namespace sdl {
    enum class Edge {
        Top,
        Bottom,
        Left,
        Right,

        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    struct Rect {
        i32_t x = 0;
        i32_t y = 0;
        u32_t width = 0;
        u32_t height = 0;

        Rect() = default;
        explicit Rect(i32_t, i32_t, u32_t, u32_t);

        SDL_Rect* copyInto(SDL_Rect*) const;

        bool isEmpty() const;
        bool intersectWith(const Rect&, Rect* intersection = nullptr) const;

        Vector2i getEdgePosition(Edge) const;
        Vector2i getCenter() const;
    };

    bool operator ==(const Rect&, const Rect&);
    bool operator !=(const Rect&, const Rect&);

    SDL_Rect* TryCopyInto(const Rect*, SDL_Rect*);
}

#endif
