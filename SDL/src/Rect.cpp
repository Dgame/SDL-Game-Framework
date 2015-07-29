#include "Rect.hpp"
#include "Vector2.hpp"

#include <SDL.h>

namespace sdl {
    Rect::Rect(i32_t cx, i32_t cy, u32_t w, u32_t h) : x(cx), y(cy), width(w), height(h) {

    }

    SDL_Rect* Rect::copyInto(SDL_Rect* rect) const {
        if (rect) {
            rect->x = this->x;
            rect->y = this->y;
            rect->w = this->width;
            rect->h = this->height;
        }

        return rect;
    }

    bool Rect::isEmpty() const {
        SDL_Rect r;
        return SDL_RectEmpty(this->copyInto(&r)) == SDL_TRUE;
    }

    bool Rect::intersectWith(const Rect& other, Rect* intersection) const {
        SDL_Rect a;
        SDL_Rect b;

        if (!intersection)
            return SDL_HasIntersection(this->copyInto(&a), other.copyInto(&b)) == SDL_TRUE;

        SDL_Rect result;
        const SDL_bool intersects = SDL_IntersectRect(this->copyInto(&a), other.copyInto(&b), intersection->copyInto(&result));

        intersection->x = result.x;
        intersection->y = result.y;
        intersection->width = result.w;
        intersection->height = result.h;

        return intersects == SDL_TRUE;
    }

    Vector2i Rect::getEdgePosition(Edge edge) const {
        Vector2i pos;
        switch (edge) {
            case Edge::Top:
                pos.x = this->x + (this->width / 2);
                pos.y = this->y;
            break;
            case Edge::Bottom:
                pos.x = this->x + (this->width / 2);
                pos.y = this->y + this->height;
            break;
            case Edge::Left:
                pos.x = this->x;
                pos.y = this->y + (this->height / 2);
            break;
            case Edge::Right:
                pos.x = this->x + this->width;
                pos.y = this->y + (this->height / 2);
            break;
            case Edge::TopLeft:
                pos.x = this->x;
                pos.y = this->y;
            break;
            case Edge::TopRight:
                pos.x = this->x + this->width;
                pos.y = this->y;
            break;
            case Edge::BottomLeft:
                pos.x = this->x;
                pos.y = this->y + this->height;
            break;
            case Edge::BottomRight:
                pos.x = this->x + this->width;
                pos.y = this->y + this->height;
            break;
        }

        return pos;
    }

    Vector2i Rect::getCenter() const {
        return Vector2i(this->x + (this->width / 2), this->y + (this->height / 2));
    }

    bool operator ==(const Rect& lhs, const Rect& rhs) {
        SDL_Rect a;
        SDL_Rect b;
        return SDL_RectEquals(lhs.copyInto(&a), rhs.copyInto(&b)) == SDL_TRUE;
    }

    bool operator !=(const Rect& lhs, const Rect& rhs) {
        return !(lhs == rhs);
    }

    SDL_Rect* TryCopyInto(const Rect* rect, SDL_Rect* sdl_rect) {
        if (rect)
            return rect->copyInto(sdl_rect);
        return nullptr;
    }
}