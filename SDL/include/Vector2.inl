template <typename T>
Vector2<T> operator +(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
Vector2<T> operator -(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
Vector2<T> operator *(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
Vector2<T> operator /(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename T>
Vector2<T> operator %(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(lhs.x % rhs.x, lhs.y % rhs.y);
}

template <typename T>
Vector2<T> operator +(const Vector2<T>& lhs, T rhs) {
    return Vector2<T>(lhs.x + rhs, lhs.y + rhs);
}

template <typename T>
Vector2<T> operator -(const Vector2<T>& lhs, T rhs) {
    return Vector2<T>(lhs.x - rhs, lhs.y - rhs);
}

template <typename T>
Vector2<T> operator *(const Vector2<T>& lhs, T rhs) {
    return Vector2<T>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T>
Vector2<T> operator /(const Vector2<T>& lhs, T rhs) {
    return Vector2<T>(lhs.x / rhs, lhs.y / rhs);
}

template <typename T>
Vector2<T> operator %(const Vector2<T>& lhs, T rhs) {
    return Vector2<T>(lhs.x % rhs, lhs.y % rhs);
}

template <typename T>
Vector2<T>& operator +=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    return lhs;
}

template <typename T>
Vector2<T>& operator -=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;

    return lhs;
}

template <typename T>
Vector2<T>& operator *=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;

    return lhs;
}

template <typename T>
Vector2<T>& operator /=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;

    return lhs;
}

template <typename T>
Vector2<T>& operator %=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x %= rhs.x;
    lhs.y %= rhs.y;

    return lhs;
}

template <typename T>
Vector2<T>& operator +=(Vector2<T>& lhs, T rhs) {
    lhs.x += rhs;
    lhs.y += rhs;

    return lhs;
}

template <typename T>
Vector2<T>& operator -=(Vector2<T>& lhs, T rhs) {
    lhs.x -= rhs;
    lhs.y -= rhs;

    return lhs;
}

template <typename T>
Vector2<T>& operator *=(Vector2<T>& lhs, T rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;

    return lhs;
}

template <typename T>
Vector2<T>& operator /=(Vector2<T>& lhs, T rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;

    return lhs;
}

template <typename T>
Vector2<T>& operator %=(Vector2<T>& lhs, T rhs) {
    lhs.x %= rhs;
    lhs.y %= rhs;

    return lhs;
}
