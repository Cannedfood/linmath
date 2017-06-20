#pragma once

#include <cmath>

#include "vec3.hpp"

namespace stx {

class mat4;
class mat3;

/// A quaternion used for rotation. @ingroup stxmath
class quat {
public:
	union {
		struct {
			float w, x, y, z;
		};
		float wxyz[3];
	};

	constexpr inline
	quat() :
		quat(0, 1, 0, 0)
	{}

	constexpr inline
	quat(float w, float x, float y, float z) :
		w(w), x(x), y(y), z(z)
	{}

	constexpr inline quat operator+(const quat& other) const { return quat{w + other.w, x + other.x, y + other.y, z + other.z}; }
	constexpr inline quat operator-(const quat& other) const { return quat{w + other.w, x - other.x, y - other.y, z - other.z}; }
	constexpr quat operator*(const quat& other) const {
		return {
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w
		};
	}
	constexpr inline quat operator/(const quat& other) const { return (*this) * other.conjugate(); }

	inline quat operator*(float f) const { return quat{w/f, x*f, y*f, z*f}; }
	inline quat operator/(float f) const { return quat{w/f, x/f, y/f, z/f}; }

	constexpr inline quat operator*=(const quat& other) { return *this = *this * other; }
	constexpr inline quat operator/=(const quat& other) { return *this = *this * other.conjugate(); }
	constexpr inline quat operator+=(const quat& other) { return *this = *this + other; }
	constexpr inline quat operator-=(const quat& other) { return *this = *this - other; }

	constexpr inline quat operator-() const { return quat{-w,-x,-y,-z }; }

	constexpr inline quat conjugate() const { return -(*this); }

	constexpr inline float length2() const { return w * w + x * x + y * y + z * z; }
	inline float length() const { return sqrtf(length2()); }

	quat normalize() const {
		return quat(*this).make_normalized();
	}

	quat& make_normalized() {
		float l = length();
		w /= l;
		x /= l;
		y /= l;
		z /= l;
		return *this;
	}

	mat3 to_mat3() const;

	mat4 to_mat4() const;

	static quat AngleAxis(float angle, vec3 axis) {
		float sinangle = sinf(angle / 2.f);
		return quat{
			cosf(angle / 2.f),
			axis.x * sinangle,
			axis.y * sinangle,
			axis.z * sinangle
		};
	}

	constexpr inline
	vec3 compress() { return vec3{x, y, z}; }

	inline static
	quat Decompress(const vec3& v) {
		float w = sqrtf(1 - v.length2());
		return quat {
			w, v.x, v.y, v.z
		};
	}
};

} // namespace stx
