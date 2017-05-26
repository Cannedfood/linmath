#pragma once

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat3.hpp"

#include <initializer_list>

namespace stx {

/// A 4x4 matrix. @ingroup LinearMath
class mat4 {
public:
	union {
		float data[16];
		vec4  vectors[4];
	};

	constexpr
	mat4(std::nullptr_t) :
		vectors{vec4(), vec4(), vec4(), vec4()}
	{}

	constexpr explicit
	mat4(const mat3& m3) :
		mat4 {
			m3.data[0], m3.data[1], m3.data[2], 0,
			m3.data[3], m3.data[4], m3.data[5], 0,
			m3.data[6], m3.data[7], m3.data[8], 0,
			         0,          0,          0, 1
		}
	{}

	constexpr
	mat4(float scale = 1.f) :
		data {
			scale,     0,     0,     0,
			    0, scale,     0,     0,
			    0,     0, scale,     0,
			    0,     0,     0, scale
		}
	{}

	constexpr
	mat4(const vec4& scale) :
		data {
			scale.x,       0,       0,       0,
				  0, scale.y,       0,       0,
				  0,       0, scale.z,       0,
				  0,       0,       0, scale.w
		}
	{}

	constexpr
	mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) :
		vectors{ a, b, c, d }
	{}

	constexpr
	mat4(
		float aa, float ab, float ac, float ad,
		float ba, float bb, float bc, float bd,
		float ca, float cb, float cc, float cd,
		float da, float db, float dc, float dd) :
		data{
			aa, ab, ac, ad,
			ba, bb, bc, bd,
			ca, cb, cc, cd,
			da, db, dc, dd
		}
	{}

	constexpr inline operator const float*() const { return data; }
	constexpr inline operator       float*()       { return data; }

	constexpr inline const vec4& operator[](size_t idx) const { return vectors[idx]; }
	constexpr inline       vec4& operator[](size_t idx)       { return vectors[idx]; }

	constexpr
	mat4 operator*(const mat4& other) {
		mat4 result;
		for (size_t i = 0; i < 4; i++) {
			for (size_t k = 0; k < 4; k++) {
				result[i][k] =
					(*this)[i][0] * other[0][k] +
					(*this)[i][1] * other[1][k] +
					(*this)[i][2] * other[2][k] +
					(*this)[i][3] * other[3][k];
			}
		}
		return result;
	}

	constexpr
	vec3 operator*(const vec3& v) {
		return vec3{
			v.x * data[ 0] + v.y * data[ 1] + v.z * data[ 2] + data[ 3],
			v.x * data[ 4] + v.y * data[ 5] + v.z * data[ 6] + data[ 7],
			v.x * data[ 8] + v.y * data[ 9] + v.z * data[10] + data[11]
		};
	}

	constexpr
	vec4 operator*(const vec4& v) {
		return vec4{
			v.x * data[ 0] + v.y * data[ 1] + v.z * data[ 2] + v.w * data[ 3],
			v.x * data[ 4] + v.y * data[ 5] + v.z * data[ 6] + v.w * data[ 7],
			v.x * data[ 8] + v.y * data[ 9] + v.z * data[10] + v.w * data[11],
			v.x * data[12] + v.y * data[13] + v.z * data[14] + v.w * data[15]
		};
	}
};

} // namespace stx
