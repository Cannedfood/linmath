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

	constexpr operator const float*() const noexcept { return xy; }
	constexpr operator float*() { return xy; }

	constexpr vec2 operator+(const vec2& other) const noexcept { return vec2(x + other.x, y + other.y); }
	constexpr vec2 operator-(const vec2& other) const noexcept { return vec2(x - other.x, y - other.y); }
	constexpr vec2 operator*(const vec2& other) const noexcept { return vec2(x * other.x, y * other.y); }
	constexpr vec2 operator/(const vec2& other) const noexcept { return vec2(x / other.x, y / other.y); }

	constexpr vec2 operator*(float f) const noexcept { return vec2(x * f, y * f); }
	constexpr vec2 operator/(float f) const noexcept { return vec2(x / f, y / f); }

	constexpr vec2 operator+=(const vec2& other) { return *this = *this + other; }
	constexpr vec2 operator-=(const vec2& other) { return *this = *this - other; }
	constexpr vec2 operator*=(const vec2& other) { return *this = *this * other; }
	constexpr vec2 operator/=(const vec2& other) { return *this = *this / other; }

	constexpr vec2& operator*=(float f) { return *this = *this * f; }
	constexpr vec2& operator/=(float f) { return *this = *this / f; }

	constexpr vec2 operator-() const noexcept { return vec2{-x, -y}; }

	constexpr bool operator==(const vec2& other) const noexcept {
		return x == other.x && y == other.y;
	}
	constexpr bool operator!=(const vec2& other) const noexcept {
		return x != other.x || y != other.y;
	}

	constexpr float dot(const vec2& v) const noexcept { return x * v.x + y * v.y; }
	constexpr float length2() const noexcept { return dot(*this); }
	float length() const noexcept { return sqrtf(length2()); }

	constexpr vec2 mix(vec2 const& other, float k) const noexcept {
		return (*this) * k + other * (1 - k);
	}

	vec2 mix(vec2 const& other, float k, float step, float unit = 1) const noexcept {
		float adjusted_k = powf(k, step / unit);
		return mix(other, adjusted_k);
	}

	vec2  normalized()      const noexcept { return *this / length(); }
	vec2& make_normalized()       { return *this /= length(); }

	constexpr vec2 max(const vec2& v) const noexcept {
		return vec2{
			x > v.x ? x : v.x,
			y > v.y ? y : v.y
		};
	}
	constexpr vec2 min(const vec2& v) const noexcept {
		return vec2{
			x < v.x ? x : v.x,
			y < v.y ? y : v.y
		};
	}
	constexpr vec2 clamp(const vec2& mn, const vec2& mx) const noexcept { return min(mx).max(mn); }

	constexpr vec2 round() const noexcept { return vec2(std::round(x), std::round(y)); }
	constexpr vec2 ceil()  const noexcept { return vec2(std::ceil(x), std::ceil(y)); }
	constexpr vec2 floor() const noexcept { return vec2(std::floor(x), std::floor(y)); }

	constexpr static unsigned dimensions() { return 2; }
};

constexpr inline
vec2 operator*(float f, vec2 const& v) noexcept { return v * f; }
constexpr inline
vec2 operator/(float f, vec2 const& v) noexcept { return vec2(f / v.x, f / v.y); }

inline constexpr vec2 mix(const vec2& a, const vec2& b, float k) {
	return a.mix(b, k);
}

inline vec2 mix(const vec2& a, const vec2& b, float k, float step, float unit = 1) {
	return a.mix(b, k, step, unit);
}

inline constexpr float dot    (const vec2& a, const vec2& b) { return a.dot(b); }
inline constexpr float length2(const vec2& v) { return v.length2(); }
inline float length (const vec2& v) { return v.length(); }

} // namespace stx
