#pragma once

#include <cmath>
#include <cstddef>

namespace stx {

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
	};

	constexpr inline explicit
	vec3(float f = 0.f) :
		x(f), y(f), z(f)
	{}

	constexpr inline
	vec3(float x, float y, float z) :
		x(x), y(y), z(z)
	{}

	constexpr inline operator const float*() const { return xyz; }
	constexpr inline operator       float*()       { return xyz; }

	constexpr inline const float& operator[](size_t idx) const { return xyz[idx]; }
	constexpr inline       float& operator[](size_t idx)       { return xyz[idx]; }


	constexpr inline vec3 operator+(const vec3& other) const { return vec3{x + other.x, y + other.y, z + other.z}; }
	constexpr inline vec3 operator-(const vec3& other) const { return vec3{x - other.x, y - other.y, z - other.z}; }
	constexpr inline vec3 operator*(const vec3& other) const { return vec3{x * other.x, y * other.y, z * other.z}; }
	constexpr inline vec3 operator/(const vec3& other) const { return vec3{x / other.x, y / other.y, z / other.z}; }

	constexpr inline vec3 operator*(float f) const { return vec3{x * f, y * f, z * f}; }
	constexpr inline vec3 operator/(float f) const { return vec3{x / f, y / f, z / f}; }

	constexpr inline vec3 operator+=(const vec3& other) { return *this = *this + other; }
	constexpr inline vec3 operator-=(const vec3& other) { return *this = *this - other; }
	constexpr inline vec3 operator*=(const vec3& other) { return *this = *this * other; }
	constexpr inline vec3 operator/=(const vec3& other) { return *this = *this / other; }

	constexpr inline vec3 operator*=(float f) { return *this = *this * f; }
	constexpr inline vec3 operator/=(float f) { return *this = *this / f; }

	constexpr inline vec3 operator-() const { return vec3{-x, -y, -z}; }

	constexpr inline bool operator==(const vec3& other) const {
		return x == other.x && y == other.y && y == other.y;
	}

	constexpr inline vec3  cross(const vec3& v) const {
		return vec3{
			y * v.z - v.y * z,
			z * v.x - v.z * x,
			x * v.y - v.x * y
		};
	}

	 constexpr inline float dot(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }
	 constexpr inline float length2()          const { return dot(*this); }
	 inline float length()           const { return sqrtf(length2()); }

	 constexpr inline vec3 normalize()   const { return *this / length(); }
	 constexpr inline vec3& make_normal() { *this = normalize(); return *this; }


	 constexpr inline vec3 max(const vec3& v) const {
		return vec3 {
			x > v.x ? x : v.x,
			y > v.y ? y : v.y,
			z > v.z ? z : v.z
		};
	}
	constexpr inline vec3 min(const vec3& v) const {
		return vec3{
			x < v.x ? x : v.x,
			y < v.y ? y : v.y,
			z < v.z ? z : v.z
		};
	}
	constexpr inline vec3 clamp(const vec3& mn, const vec3& mx) const { return min(mx).max(mn); }
};

constexpr inline float dot    (const vec3& a, const vec3& b) { return a.dot(b); }
constexpr inline vec3  cross  (const vec3& a, const vec3& b) { return a.cross(b); }
constexpr inline float length2(const vec3& v)   { return v.length2(); }
inline float length (const vec3& v)   { return v.length(); }

constexpr
vec3 rgb(unsigned char r, unsigned char g, unsigned char b) {
	return vec3{ r / 255.f, g / 255.f, b / 255.f };
}

} // namespace stx
