#pragma once

#include <cmath>

namespace stx {

/// A 2 dimensional vector. @ingroup stxmath
class vec2 {
public:
	union {
		struct {
			float x, y;
		};
		float xy[2];
	};

	constexpr explicit
	vec2(float f = 0.f) :
		x(f), y(f)
	{}

	constexpr
	vec2(float x, float y) :
		x(x), y(y)
	{}

	constexpr operator const float*() const { return xy; }
	constexpr operator float*() { return xy; }

	constexpr vec2 operator+(const vec2& other) const { return vec2(x + other.x, y + other.y); }
	constexpr vec2 operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }
	constexpr vec2 operator*(const vec2& other) const { return vec2(x * other.x, y * other.y); }
	constexpr vec2 operator/(const vec2& other) const { return vec2(x / other.x, y / other.y); }

	constexpr vec2 operator*(float f) const { return vec2(x * f, y * f); }
	constexpr vec2 operator/(float f) const { return vec2(x / f, y / f); }

	constexpr vec2 operator+=(const vec2& other) { return *this = *this + other; }
	constexpr vec2 operator-=(const vec2& other) { return *this = *this - other; }
	constexpr vec2 operator*=(const vec2& other) { return *this = *this * other; }
	constexpr vec2 operator/=(const vec2& other) { return *this = *this / other; }

	constexpr vec2& operator*=(float f) { return *this = *this * f; }
	constexpr vec2& operator/=(float f) { return *this = *this / f; }

	constexpr vec2 operator-() const { return vec2{-x, -y}; }

	constexpr bool operator==(const vec2& other) const {
		return x == other.x && y == other.y;
	}
	constexpr bool operator!=(const vec2& other) const {
		return x != other.x || y != other.y;
	}

	constexpr float dot(const vec2& v) const { return x * v.x + y * v.y; }
	constexpr float length2() const { return dot(*this); }
	float length() const { return sqrtf(length2()); }

	vec2  normalized()      const { return *this / length(); }
	vec2& make_normalized()       { return *this /= length(); }

	constexpr vec2 max(const vec2& v) const {
		return vec2{
			x > v.x ? x : v.x,
			y > v.y ? y : v.y
		};
	}
	constexpr vec2 min(const vec2& v) const {
		return vec2{
			x < v.x ? x : v.x,
			y < v.y ? y : v.y
		};
	}
	constexpr vec2 clamp(const vec2& mn, const vec2& mx) const { return min(mx).max(mn); }

	constexpr vec2 round() const { return vec2(std::round(x), std::round(y)); }
	constexpr vec2 ceil()  const { return vec2(std::ceil(x), std::ceil(y)); }
	constexpr vec2 floor() const { return vec2(std::floor(x), std::floor(y)); }

	constexpr static unsigned Dimensions() { return 2; }
};

inline constexpr float dot    (const vec2& a, const vec2& b) { return a.dot(b); }
inline constexpr float length2(const vec2& v) { return v.length2(); }
inline float length (const vec2& v) { return v.length(); }

} // namespace stx
