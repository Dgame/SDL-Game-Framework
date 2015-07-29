#ifndef SDL_VECTOR_HPP
#define SDL_VECTOR_HPP

#include <cmath>

#include "types.hpp"

struct SDL_Point;

namespace sdl {
    bool CompareFloats(f32_t, f32_t);

    template <typename T>
    struct Vector2;

    template <>
    struct Vector2<i32_t> {
        i32_t x = 0;
        i32_t y = 0;

        Vector2() = default;
        explicit Vector2(i32_t, i32_t);
        Vector2(const Vector2<f32_t>&);

        SDL_Point* copyInto(SDL_Point*) const;
    };

    using Vector2i = Vector2<i32_t>;

    bool operator ==(const Vector2<i32_t>&, const Vector2<i32_t>&);
    bool operator !=(const Vector2<i32_t>&, const Vector2<i32_t>&);

    SDL_Point* TryCopyInto(const Vector2<i32_t>*, SDL_Point*);

    template <>
    struct Vector2<f32_t> {
        f32_t x = 0;
        f32_t y = 0;

        Vector2() = default;
        explicit Vector2(f32_t, f32_t);
        Vector2(const Vector2<i32_t>&);
    };

    using Vector2f = Vector2<f32_t>;

    bool operator ==(const Vector2<f32_t>&, const Vector2<f32_t>&);
    bool operator !=(const Vector2<f32_t>&, const Vector2<f32_t>&);

    template <typename T>
    Vector2<T> operator +(const Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T> operator -(const Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T> operator *(const Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T> operator /(const Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T> operator %(const Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T> operator +(const Vector2<T>&, T);

    template <typename T>
    Vector2<T> operator -(const Vector2<T>&, T);

    template <typename T>
    Vector2<T> operator *(const Vector2<T>&, T);

    template <typename T>
    Vector2<T> operator /(const Vector2<T>&, T);

    template <typename T>
    Vector2<T> operator %(const Vector2<T>&, T);

    template <typename T>
    Vector2<T>& operator +=(Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T>& operator -=(Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T>& operator *=(Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T>& operator /=(Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T>& operator %=(Vector2<T>&, const Vector2<T>&);

    template <typename T>
    Vector2<T>& operator +=(Vector2<T>&, T);

    template <typename T>
    Vector2<T>& operator -=(Vector2<T>&, T);

    template <typename T>
    Vector2<T>& operator *=(Vector2<T>&, T);

    template <typename T>
    Vector2<T>& operator /=(Vector2<T>&, T);

    template <typename T>
    Vector2<T>& operator %=(Vector2<T>&, T);

    #include "Vector2.inl"
}

#endif
