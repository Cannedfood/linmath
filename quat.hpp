#pragma once

#include <cmath>

#include "vec3.hpp"

/// A quaternion used for rotation. \ingroup LinearMath
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

	constexpr inline
	vec3 operator*(const vec3& v) const {
		float n   = x * 2.f;
        float n2  = y * 2.f;
        float n3  = z * 2.f;
        float n4  = x * n;
        float n5  = y * n2;
        float n6  = z * n3;
        float n7  = x * n2;
        float n8  = x * n3;
        float n9  = y * n3;
        float n10 = w * n;
        float n11 = w * n2;
        float n12 = w * n3;

        return vec3 {
			(1 - (n5 + n6)) * v.x + (n7 - n12) * v.y + (n8 + n11) * v.z,
			(n7 + n12) * v.x + (1 - (n4 + n6)) * v.y + (n9 - n10) * v.z,
			(n8 - n11) * v.x + (n9 + n10) * v.y + (1 - (n4 + n5)) * v.z
		};
	}

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
