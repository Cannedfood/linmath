#pragma once

#include "vec3.hpp"
#include "quat.hpp"

#include <initializer_list>
#include <cstring>

namespace stx {

/// A 3x3 matrix. All accessors are column-major. @ingroup stxmath
class mat3 {
public:
	union {
		float data[9];
		vec3  vectors[3];
	};

	constexpr
	mat3(std::nullptr_t) :
		vectors{vec3(), vec3(), vec3()}
	{}

	constexpr
	mat3(float scale = 1.f) :
		data {
			scale,     0,     0,
			    0, scale,     0,
			    0,     0, scale
		}
	{}

	constexpr /// Column constructor
	mat3(const vec3& a, const vec3& b, const vec3& c) :
		vectors{ a, b, c }
	{}

	constexpr // Row major constructor (ACCESS IS COLUMN MAJOR)
	mat3(
		float aa, float ab, float ac,
		float ba, float bb, float bc,
		float ca, float cb, float cc) :
		data{
			aa, ba, ca,
			ab, bb, cb,
			ac, bc, cc
		}
	{}

	mat3 transpose() const noexcept {
		return mat3(
			data[0], data[3], data[6],
			data[1], data[4], data[7],
			data[2], data[5], data[8]
		);
	}

	float determinant() const {
		return
			vectors[0][0] * vectors[1][1] * vectors[2][2] +
			vectors[0][1] * vectors[1][2] * vectors[2][0] +
			vectors[0][2] * vectors[1][0] * vectors[2][1] -
			vectors[0][2] * vectors[1][1] * vectors[2][0] -
			vectors[0][1] * vectors[1][0] * vectors[2][2] -
			vectors[0][0] * vectors[1][2] * vectors[2][1];
	}

	constexpr operator const float*() const noexcept { return data; }
	constexpr operator       float*()                { return data; }

	template<typename Idx>
	constexpr const vec3& operator[](Idx idx) const noexcept { return vectors[idx]; }
	template<typename Idx>
	constexpr       vec3& operator[](Idx idx)       noexcept { return vectors[idx]; }

	constexpr mat3 operator*(mat3 const& other) const {
		return mat3(
			*this * other[0],
			*this * other[1],
			*this * other[2]
		);
	}

	constexpr vec3 operator*(vec3 const& v) const {
		return vec3(
			v.x * vectors[0][0] + v.y * vectors[1][0] + v.z * vectors[2][0],
			v.x * vectors[0][1] + v.y * vectors[1][1] + v.z * vectors[2][1],
			v.x * vectors[0][2] + v.y * vectors[1][2] + v.z * vectors[2][2]
		);
	}

	inline
	bool operator==(const mat3& other) const noexcept {
		for(size_t i = 0; i < 9; i++) {
			if(fabs(data[i] - other.data[i]) > 1e-6f) return false;
		}
		return true;
	}
};

inline
quat::quat(mat3 const& m) :
	quat()
{
	this->w = sqrtf(1 + m[0][0] + m[1][1] + m[2][2]);
	float w4 = w * 4;
	this->x = (m[2][1] - m[1][2]) / w4;
	this->y = (m[0][2] - m[2][0]) / w4;
	this->z = (m[1][0] - m[0][1]) / w4;
}

inline
mat3 quat::to_mat3() const noexcept {
	mat3 result;

	float const xx      = x * x;
	float const xy      = x * y;
	float const xz      = x * z;
	float const xw      = x * w;

	float const yy      = y * y;
	float const yz      = y * z;
	float const yw      = y * w;

	float const zz      = z * z;
	float const zw      = z * w;

	return mat3(
		1 - 2 * (yy + zz),     2 * (xy - zw), 2 * (xz + yw),
		    2 * (xy + zw), 1 - 2 * (xx + zz), 2 * (yz - xw),
		    2 * (xz - yw),     2 * (yz + xw), 1 - 2 * (xx + yy)
	);
}

} // namespace stx
