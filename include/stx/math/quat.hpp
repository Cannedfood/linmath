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

	constexpr inline quat operator+(const quat& other) const noexcept { return quat(w + other.w, x + other.x, y + other.y, z + other.z); }
	constexpr inline quat operator-(const quat& other) const noexcept { return quat(w + other.w, x - other.x, y - other.y, z - other.z); }
	constexpr quat operator*(const quat& other) const noexcept {
		return quat(
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w
		);
	}
	constexpr inline quat operator/(const quat& other) const noexcept { return (*this) * other.conjugate(); }

	inline quat operator*(float f) const noexcept { return quat(w/f, x*f, y*f, z*f); }
	inline quat operator/(float f) const noexcept { return quat(w/f, x/f, y/f, z/f); }

	constexpr inline quat operator*=(const quat& other) { return *this = *this * other; }
	constexpr inline quat operator/=(const quat& other) { return *this = *this * other.conjugate(); }
	constexpr inline quat operator+=(const quat& other) { return *this = *this + other; }
	constexpr inline quat operator-=(const quat& other) { return *this = *this - other; }

	constexpr inline quat operator-() const noexcept { return quat(-w,-x,-y,-z); }

	constexpr inline quat conjugate() const noexcept { return -(*this); }

	constexpr inline float length2() const noexcept { return w * w + x * x + y * y + z * z; }
	inline float length() const noexcept { return sqrtf(length2()); }

	constexpr inline
	bool operator==(quat const& other) const noexcept { return other.w == w && other.x == x && other.y == y && other.z == z; }
	constexpr inline
	bool operator!=(quat const& other) const noexcept { return other.w != w || other.x != x || other.y != y || other.z != z; }

	quat normalize() const noexcept {
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

	mat3 to_mat3() const noexcept;
	mat4 to_mat4() const noexcept;

	static quat angle_axis(float angle, vec3 const& axis) {
		float const sinangle = sinf(angle / 2.f);
		float const cosangle = cosf(angle / 2.f);
		return quat(
			cosangle,
			axis.x * sinangle,
			axis.y * sinangle,
			axis.z * sinangle
		);
	}

	static quat roll_pitch_yaw(vec3 const& v) {
		// Adapted from https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		quat q;

		float const t0 = cosf(v.z * 0.5);
		float const t1 = sinf(v.z * 0.5);
		float const t2 = cosf(v.x * 0.5);
		float const t3 = sinf(v.x * 0.5);
		float const t4 = cosf(v.y * 0.5);
		float const t5 = sinf(v.y * 0.5);

		q.w = t0 * t2 * t4 + t1 * t3 * t5;
		q.x = t0 * t3 * t4 - t1 * t2 * t5;
		q.y = t0 * t2 * t5 + t1 * t3 * t4;
		q.z = t1 * t2 * t4 - t0 * t3 * t5;

		return q;
	}

	static quat head_rotation(vec3 const& v) {
		return quat::angle_axis(v.z, vec3::zaxis()) * quat::angle_axis(v.x, vec3::xaxis()) * quat::angle_axis(v.y, vec3::yaxis());
	}

	constexpr inline
	vec3 compress() { return vec3{x, y, z}; }

	inline static
	quat decompress(const vec3& v) {
		float w = sqrtf(1 - v.length2());
		return quat(
			w, v.x, v.y, v.z
		);
	}
};

} // namespace stx
