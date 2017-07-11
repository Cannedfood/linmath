#pragma once

#include "vec3.hpp"
#include "quat.hpp"

#include <initializer_list>
#include <cstring>

namespace stx {

/// A 3x3 matrix. @ingroup stxmath
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

	constexpr
	mat3(const vec3& a, const vec3& b, const vec3& c) :
		vectors{ a, b, c }
	{}

	constexpr
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

	constexpr operator const float*() const noexcept { return data; }
	constexpr operator       float*()                { return data; }

	template<typename Idx>
	constexpr const vec3& operator[](Idx idx) const noexcept { return vectors[idx]; }
	template<typename Idx>
	constexpr       vec3& operator[](Idx idx)       noexcept { return vectors[idx]; }

	constexpr inline mat3 operator*(const mat3& other) const {
		mat3 result;
		for (size_t row = 0; row < 3; row++) {
			for (size_t clmn = 0; clmn < 3; clmn++) {
				result[clmn][row] =
					(*this)[clmn][0] * other[0][row] +
					(*this)[clmn][1] * other[1][row] +
					(*this)[clmn][2] * other[2][row];
			}
		}
		return result;
	}

	inline vec3 operator*(vec3 const& v) const {
		return vec3{
			v.x * data[0] + v.y * data[1] + v.z * data[2],
			v.x * data[3] + v.y * data[4] + v.z * data[5],
			v.x * data[6] + v.y * data[7] + v.z * data[8],
		};
	}

	inline
	bool operator==(const mat3& other) const noexcept {
		return std::memcmp(data, other.data, sizeof(data)) == 0;
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

	float xx      = x * x;
	float xy      = x * y;
	float xz      = x * z;
	float xw      = x * w;

	float yy      = y * y;
	float yz      = y * z;
	float yw      = y * w;

	float zz      = z * z;
	float zw      = z * w;

	result[0][0] = 1 - 2 * (yy + zz);
	result[1][0] =     2 * (xy - zw);
	result[2][0] =     2 * (xz + yw);
	result[0][1] =     2 * (xy + zw);
	result[1][1] = 1 - 2 * (xx + zz);
	result[2][1] =     2 * (yz - xw);
	result[0][2] =     2 * (xz - yw);
	result[1][2] =     2 * (yz + xw);
	result[2][2] = 1 - 2 * (xx + yy);

	return result;
}

} // namespace stx
