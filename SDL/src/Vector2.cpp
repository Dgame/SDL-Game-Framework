#include <limits>
#include <SDL.h>

#include "Vector2.hpp"

namespace sdl {
    bool CompareFloats(f32_t a, f32_t b) {
        return std::abs(a - b) < std::numeric_limits<f32_t>::epsilon();
    }

    Vector2<i32_t>::Vector2(i32_t cx, i32_t cy) : x(cx), y(cy) { }
    Vector2<i32_t>::Vector2(const Vector2<f32_t>& vec) : Vector2(static_cast<i32_t>(vec.x), static_cast<i32_t>(vec.y)) { }

    SDL_Point* Vector2<i32_t>::copyInto(SDL_Point* point) const {
        if (point) {
            point->x = this->x;
            point->y = this->y;
        }

        return point;
    }

    bool operator ==(const Vector2<i32_t>& lhs, const Vector2<i32_t>& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    bool operator !=(const Vector2<i32_t>& lhs, const Vector2<i32_t>& rhs) {
        return !(lhs == rhs);
    }

    SDL_Point* TryCopyInto(const Vector2<i32_t>* vec, SDL_Point* sdl_point) {
        if (vec) {
            return vec->copyInto(sdl_point);
        }

        return nullptr;
    }

    Vector2<f32_t>::Vector2(f32_t cx, f32_t cy) : x(cx), y(cy) { }
    Vector2<f32_t>::Vector2(const Vector2<i32_t>& vec) : Vector2(vec.x, vec.y) { }

    bool operator ==(const Vector2<f32_t>& lhs, const Vector2<f32_t>& rhs) {
        return std::abs(lhs.x - rhs.x) < std::numeric_limits<f32_t>::epsilon() &&
               std::abs(lhs.y - rhs.y) < std::numeric_limits<f32_t>::epsilon();
    }

    bool operator !=(const Vector2<f32_t>& lhs, const Vector2<f32_t>& rhs) {
        return !(lhs == rhs);
    }
}
