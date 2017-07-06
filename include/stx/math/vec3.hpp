#pragma once

#include <cmath>
#include <cstddef>

namespace stx {

class vec2;

/// A 3 dimensional vector or rgb color. @ingroup stxmath
class vec3 {
public:
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		float xyz[3];
		float rgb[3];
	};

	constexpr explicit
	vec3(float f = 0.f) :
		x(f), y(f), z(f)
	{}

	constexpr inline
	vec3(float x, float y, float z) :
		x(x), y(y), z(z)
	{}

	constexpr explicit operator const float*() const noexcept { return xyz; }
	constexpr explicit operator       float*()       noexcept { return xyz; }

	constexpr const float& operator[](size_t idx) const noexcept { return xyz[idx]; }
	constexpr       float& operator[](size_t idx)       noexcept { return xyz[idx]; }


	constexpr vec3 operator+(const vec3& other) const noexcept { return vec3{x + other.x, y + other.y, z + other.z}; }
	constexpr vec3 operator-(const vec3& other) const noexcept { return vec3{x - other.x, y - other.y, z - other.z}; }
	constexpr vec3 operator*(const vec3& other) const noexcept { return vec3{x * other.x, y * other.y, z * other.z}; }
	constexpr vec3 operator/(const vec3& other) const noexcept { return vec3{x / other.x, y / other.y, z / other.z}; }

	constexpr vec3 operator*(float f) const noexcept { return vec3{x * f, y * f, z * f}; }
	constexpr vec3 operator/(float f) const noexcept { return vec3{x / f, y / f, z / f}; }

	constexpr vec3 operator+=(const vec3& other) { return *this = *this + other; }
	constexpr vec3 operator-=(const vec3& other) { return *this = *this - other; }
	constexpr vec3 operator*=(const vec3& other) { return *this = *this * other; }
	constexpr vec3 operator/=(const vec3& other) { return *this = *this / other; }

	constexpr vec3 operator*=(float f) { return *this = *this * f; }
	constexpr vec3 operator/=(float f) { return *this = *this / f; }

	constexpr vec3 operator-() const noexcept { return vec3{-x, -y, -z}; }

	constexpr bool operator==(const vec3& other) const noexcept {
		return x == other.x && y == other.y && y == other.y;
	}
	constexpr bool operator!=(const vec3& other) const noexcept {
		return x != other.x || y != other.y || y != other.y;
	}

	constexpr vec3 cross(const vec3& v) const noexcept {
		return vec3{
			y * v.z - v.y * z,
			z * v.x - v.z * x,
			x * v.y - v.x * y
		};
	}

	 constexpr float dot(const vec3& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
	 constexpr float length2()          const noexcept { return dot(*this); }
	 float length()                     const noexcept { return sqrtf(length2()); }

	 // constexpr TODO: make these two constexpr as soon as length() is
	 vec3  normalize() const noexcept { return *this / length(); }
	 vec3& make_normal()     { *this = normalize(); return *this; }


	 constexpr vec3 max(const vec3& v) const noexcept {
		return vec3 {
			x > v.x ? x : v.x,
			y > v.y ? y : v.y,
			z > v.z ? z : v.z
		};
	}
	constexpr vec3 min(const vec3& v) const noexcept {
		return vec3{
			x < v.x ? x : v.x,
			y < v.y ? y : v.y,
			z < v.z ? z : v.z
		};
	}
	constexpr vec3 clamp(const vec3& mn, const vec3& mx) const noexcept { return min(mx).max(mn); }

	constexpr static vec3 xaxis() { return vec3(1, 0, 0); }
	constexpr static vec3 yaxis() { return vec3(0, 1, 0); }
	constexpr static vec3 zaxis() { return vec3(0, 0, 1); }

	constexpr static unsigned dimensions() { return 3; }

	vec2&       as_vec2()       { return *((vec2*) xyz); }
	vec2 const& as_vec2() const { return *((vec2 const*) xyz); }
};

inline constexpr float dot    (const vec3& a, const vec3& b) { return a.dot(b); }
inline constexpr vec3  cross  (const vec3& a, const vec3& b) { return a.cross(b); }
inline constexpr float length2(const vec3& v)   { return v.length2(); }
inline float           length (const vec3& v)   { return v.length(); }

static constexpr
vec3 rgb(unsigned char r, unsigned char g, unsigned char b) {
	return vec3{ r / 255.f, g / 255.f, b / 255.f };
}

} // namespace stx
