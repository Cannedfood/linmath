#pragma once

#include "vec3.hpp"

#include <initializer_list>
#include <cstring>

namespace stx {

/// A 3x3 matrix. \ingroup LinearMath
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
		data{aa, ab, ac, ba, bb, bc, ca, cb, cc}
	{}

	constexpr
	operator const float*() const { return data; }
	operator       float*()       { return data; }

	const vec3& operator[](size_t idx) const { return vectors[idx]; }
	      vec3& operator[](size_t idx)       { return vectors[idx]; }

	inline mat3 operator*(const mat3& other) {
		mat3 result;
		for (size_t i = 0; i < 3; i++) {
			for (size_t k = 0; k < 3; k++) {
				result[i][k] =
					(*this)[i][0] * other[0][k] +
					(*this)[i][1] * other[1][k] +
					(*this)[i][2] * other[2][k];
			}
		}
		return result;
	}

	inline vec3 operator*(const vec3& v) {
		return vec3{
			v.x * data[0] + v.y * data[1] + v.z * data[2],
			v.x * data[3] + v.y * data[4] + v.z * data[5],
			v.x * data[6] + v.y * data[7] + v.z * data[8],
		};
	}

	inline
	bool operator==(const mat3& other) const {
		return std::memcmp(data, other.data, sizeof(data)) == 0;
	}
};

} // namespace stx
