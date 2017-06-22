#pragma once

#include <cmath>

namespace stx {

/// A 4 dimensional vector or rgba color. @ingroup stxmath
class vec4 {
public:
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
		float xyzw[4];
		float rgba[4];
	};

	constexpr explicit
	vec4(float f = 0.f) :
		x(f), y(f), z(f), w(f)
	{}

	constexpr inline
	vec4(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w)
	{}

	constexpr operator const float*() const noexcept { return xyzw; }
	constexpr operator       float*()       { return xyzw; }

	constexpr vec4 operator+(const vec4& other) const noexcept { return vec4{x+other.x, y+other.y, z+other.z, w+other.w}; }
	constexpr vec4 operator-(const vec4& other) const noexcept { return vec4{x-other.x, y-other.y, z-other.z, w-other.w}; }
	constexpr vec4 operator*(const vec4& other) const noexcept { return vec4{x*other.x, y*other.y, z*other.z, w*other.w}; }
	constexpr vec4 operator/(const vec4& other) const noexcept { return vec4{x/other.x, y/other.y, z/other.z, w/other.w}; }

	constexpr vec4 operator*(float f) const noexcept { return vec4{x * f, y * f, z * f, w * f}; }
	constexpr vec4 operator/(float f) const noexcept { return vec4{x / f, y / f, z / f, w / f}; }

	constexpr vec4 operator+=(const vec4& other) { return *this = *this + other; }
	constexpr vec4 operator-=(const vec4& other) { return *this = *this - other; }
	constexpr vec4 operator*=(const vec4& other) { return *this = *this * other; }
	constexpr vec4 operator/=(const vec4& other) { return *this = *this / other; }

	constexpr vec4 operator*=(float f) { return *this = *this * f; }
	constexpr vec4 operator/=(float f) { return *this = *this / f; }

	constexpr vec4 operator-() const noexcept { return vec4{-x, -y, -z, -w}; }

	constexpr bool operator==(const vec4& other) const noexcept {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	constexpr bool operator!=(const vec4& other) const noexcept {
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}

	constexpr float dot(const vec4& v) const noexcept { return x * v.x + y * v.y + z * v.z + w * v.w; }
	constexpr float length2()          const noexcept { return dot(*this); }
	float length()                     const noexcept { return sqrtf(length2()); }

	// TODO: make these two constexpr if as length() is
	vec4  normalize()   const noexcept { return *this / length(); }
	vec4& make_normal() { *this = normalize(); return *this; }


	constexpr vec4 max(const vec4& v) const noexcept {
		return vec4{
			x > v.x ? x : v.x,
			y > v.y ? y : v.y,
			z > v.z ? z : v.z,
			w > v.w ? w : v.w
		};
	}
	constexpr vec4 min(const vec4& v) const noexcept {
		return vec4{
			x < v.x ? x : v.x,
			y < v.y ? y : v.y,
			z < v.z ? z : v.z,
			w < v.w ? w : v.w
		};
	}
	constexpr vec4 clamp(const vec4& mn, const vec4& mx) const noexcept { return min(mx).max(mn); }

	constexpr float sum() const noexcept { return x + y + z + w; }

	constexpr static unsigned Dimensions() { return 3; }
};

inline constexpr float dot    (const vec4& a, const vec4& b) { return a.dot(b); }
inline constexpr float length2(const vec4& v)   { return v.length2(); }
inline float           length (const vec4& v)   { return v.length(); }

static constexpr
vec4 rgba(unsigned char r, unsigned char g, unsigned char b, double a = 1.0) {
	return vec4 { r / 255.f, g / 255.f, b/255.f, (float)a };
}

} // namespace stx
