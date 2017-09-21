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

	constexpr vec3 operator+=(const vec3& other) noexcept { return (*this) = (*this) + other; }
	constexpr vec3 operator-=(const vec3& other) noexcept { return (*this) = (*this) - other; }
	constexpr vec3 operator*=(const vec3& other) noexcept { return (*this) = (*this) * other; }
	constexpr vec3 operator/=(const vec3& other) noexcept { return (*this) = (*this) / other; }

	constexpr vec3 operator*=(float f) noexcept { return (*this) = (*this) * f; }
	constexpr vec3 operator/=(float f) noexcept { return (*this) = (*this) / f; }

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

	constexpr vec3 mix(vec3 const& other, float k) const noexcept {
		return (*this) + (other - *this) * k;
	}

	vec3 mix(vec3 const& other, float k, float step, float unit = 1) const noexcept {
		return mix(other, 1 - powf(1 - k, step / unit));
	}

	 // constexpr TODO: make constexpr as soon as length() is
	vec3  normalize() const noexcept { return (*this) / length(); }

	vec3& make_mix(vec3 const& other, float k) noexcept { return (*this) = mix(other, k); }
	vec3& make_mix(vec3 const& other, float k, float step, float unit = 1) noexcept { return (*this) = mix(other, k, step, unit); }
	vec3& make_normal() noexcept { return (*this) = normalize(); }

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

	static vec3 look_along(vec3 const& dir) noexcept {
		if(dir.is_null()) return vec3();

		float look_up_dist   = sqrtf(dir.z * dir.z + dir.x * dir.x);
		float look_up_height = dir.y;

		if(look_up_dist == 0) { // Edgecase: directly below or above
			return vec3(copysignf(M_PI * .5f, look_up_height), 0, 0);
		}

		float look_up_angle = atanf(look_up_height / look_up_dist);

		float turn_dist   = -dir.z;
		float turn_height = dir.x;

		float turn_angle = -atan2f(turn_height, turn_dist);

		return vec3(look_up_angle, turn_angle, 0);
	}

	constexpr static vec3 xaxis() noexcept { return vec3(1, 0, 0); }
	constexpr static vec3 yaxis() noexcept { return vec3(0, 1, 0); }
	constexpr static vec3 zaxis() noexcept { return vec3(0, 0, 1); }

	constexpr static vec3 forward() noexcept { return -zaxis(); }
	constexpr static vec3 back()    noexcept { return  zaxis(); }
	constexpr static vec3 right()   noexcept { return  xaxis(); }
	constexpr static vec3 left()    noexcept { return -xaxis(); }
	constexpr static vec3 up()      noexcept { return  yaxis(); }
	constexpr static vec3 down()    noexcept { return -yaxis(); }

	constexpr static unsigned dimensions() noexcept { return 3; }

	vec2&       as_vec2()       noexcept { return *((vec2*) xyz); }
	vec2 const& as_vec2() const noexcept { return *((vec2 const*) xyz); }

	constexpr bool valid() const noexcept { return x == x && y == y && z == z; }
	constexpr bool is_null() const noexcept { return x == 0 && y == 0 && z == 0; }
};

constexpr inline
vec3 operator*(float f, vec3 const& v) noexcept { return v * f; }
constexpr inline
vec3 operator/(float f, vec3 const& v) noexcept { return vec3(f / v.x, f / v.y, f / v.z); }

inline constexpr float dot    (const vec3& a, const vec3& b) noexcept { return a.dot(b); }
inline constexpr vec3  cross  (const vec3& a, const vec3& b) noexcept { return a.cross(b); }
inline constexpr float length2(const vec3& v)                noexcept { return v.length2(); }
inline float           length (const vec3& v)                noexcept { return v.length(); }

inline constexpr vec3 mix(const vec3& a, const vec3& b, float k) noexcept {
	return a.mix(b, k);
}

inline vec3 mix(const vec3& a, const vec3& b, float k, float step, float unit = 1) noexcept {
	return a.mix(b, k, step, unit);
}

static constexpr
vec3 rgb(unsigned char r, unsigned char g, unsigned char b) noexcept {
	return vec3{ r / 255.f, g / 255.f, b / 255.f };
}

} // namespace stx
