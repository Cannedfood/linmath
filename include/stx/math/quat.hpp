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

	constexpr
	quat() :
		quat(1, 0, 0, 0)
	{}

	constexpr
	quat(float w, float x, float y, float z) :
		w(w), x(x), y(y), z(z)
	{}

	explicit
	quat(mat3 const& m);

	constexpr quat operator+(const quat& other) const noexcept { return quat(w + other.w, x + other.x, y + other.y, z + other.z); }
	constexpr quat operator-(const quat& other) const noexcept { return quat(w - other.w, x - other.x, y - other.y, z - other.z); }
	constexpr quat operator*(const quat& other) const noexcept {
		return quat(
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w
		);
	}
	constexpr quat operator/(const quat& other) const noexcept { return (*this) * other.conjugate(); }

	constexpr quat operator*(float f) const noexcept { return quat(w * f, x * f, y * f, z * f); }
	constexpr quat operator/(float f) const noexcept { return (*this) * (1.f / f); }

	constexpr quat operator*=(const quat& other) { return *this = *this * other; }
	constexpr quat operator/=(const quat& other) { return *this = *this * other.conjugate(); }
	constexpr quat operator+=(const quat& other) { return *this = *this + other; }
	constexpr quat operator-=(const quat& other) { return *this = *this - other; }

	constexpr quat operator-() const noexcept { return quat(-w,-x,-y,-z); }

	constexpr
	bool operator==(quat const& other) const noexcept { return other.w == w && other.x == x && other.y == y && other.z == z; }
	constexpr
	bool operator!=(quat const& other) const noexcept { return other.w != w || other.x != x || other.y != y || other.z != z; }

	constexpr float length2() const noexcept { return w * w + x * x + y * y + z * z; }
	float length() const noexcept { return sqrtf(length2()); }

	constexpr quat conjugate() const noexcept { return -(*this); }

	constexpr float dot(quat const& q) const noexcept {
		return q.w * w + q.x * x + q.y * y + q.z * z;
	}

	quat lerp(quat const& other, float k) const noexcept {
		if(other.dot(*this) < 0)
			return (*this + (other.conjugate() - *this) * k).normalize();
		else
			return (*this + (other - *this) * k).normalize();
	}

	quat lerp(quat const& other, float k, float step, float unit = 1) const noexcept {
		return lerp(other, 1 - powf(1 - k, step / unit));
	}

	quat slerp(quat const& other, float k) const noexcept {
		float dot = w * other.w + x * other.x + y * other.y + z * other.z;

		if(fabs(dot) > 0.9995f) {
			return lerp(other, k);
		}

		quat v1 = other;

		if(dot < 0) {
			v1  = other.conjugate();
			dot = -dot;
		}
		else {
			v1 = other;
		}

		if(dot > 1) dot = 1;

		float theta   = acosf(dot) * k;

		quat v2 = (v1 - (*this) * dot).normalize();

		return (*this) * cosf(theta) + v2 * sinf(theta);
	}

	quat slerp(quat const& other, float k, float step, float unit = 1) const noexcept {
		return slerp(other, 1 - powf(1 - k, step / unit));
	}

	quat normalize() const noexcept {
		float l = length();
		return quat(w / l, x / l, y / l, z / l);
	}

	constexpr quat& make_conjugate()  noexcept { return (*this) = conjugate(); }
	quat& make_normalized() noexcept { return (*this) = normalize(); }
	quat& make_lerp(quat const& other, float k) noexcept { return (*this) = lerp(other, k); }
	quat& make_lerp(quat const& other, float k, float step, float unit = 1) noexcept { return (*this) = lerp(other, k, step, unit); }
	quat& make_slerp(quat const& other, float k, float step, float unit = 1) noexcept { return (*this) = slerp(other, k, step, unit); }
	quat& make_slerp(quat const& other, float k) noexcept { return (*this) = slerp(other, k); }

	mat3 to_mat3() const noexcept;
	mat4 to_mat4() const noexcept;

	static quat angle_axis(float angle, vec3 const& axis) noexcept {
		float const sinangle = sinf(angle / 2.f);
		float const cosangle = cosf(angle / 2.f);
		return quat(
			cosangle,
			axis.x * sinangle,
			axis.y * sinangle,
			axis.z * sinangle
		);
	}

	quat extract_axis(vec3 const& axis) const {
		vec3 ra( x, y, z ); // rotation axis
		vec3 p = axis * ::stx::dot(ra, axis.normalize()); // return projection v1 on to v2  (parallel component)
		quat twist(w, p.x, p.y, p.z);
		twist.make_normalized();
		return twist;
	}

	// TODO: implement with up
	static quat look_at(vec3 const& origin, vec3 const& at) noexcept {
		vec3 v = vec3::look_at(origin, at);

		return quat::angle_axis(v.x, vec3::right()) * quat::angle_axis(v.y, vec3::up());
	}

	static quat roll_pitch_yaw(vec3 const& v) noexcept {
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

	static quat head_rotation(vec3 const& v) noexcept {
		return quat::angle_axis(v.z, vec3::zaxis()) * quat::angle_axis(v.x, vec3::xaxis()) * quat::angle_axis(v.y, vec3::yaxis());
	}

	constexpr
	vec3 compress() noexcept { return vec3{x, y, z}; }

	static
	quat decompress(const vec3& v) noexcept {
		float w = sqrtf(1 - v.length2());
		return quat(
			w, v.x, v.y, v.z
		);
	}
};

} // namespace stx
