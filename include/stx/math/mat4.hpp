#pragma once

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat3.hpp"
#include "quat.hpp"

#include <initializer_list>

namespace stx {

/// A 4x4 matrix. @ingroup stxmath
class mat4 {
public:
	union {
		float data[16];
		vec4  vectors[4];
	};

	constexpr explicit
	mat4(const mat3& m3) :
		mat4(
			m3.data[0], m3.data[3], m3.data[6], 0,
			m3.data[1], m3.data[4], m3.data[7], 0,
			m3.data[2], m3.data[5], m3.data[8], 0,
			         0,          0,          0, 1
		)
	{}

	constexpr explicit
	mat4(float scale = 1.f) :
		mat4(
			scale,     0,     0,     0,
			    0, scale,     0,     0,
			    0,     0, scale,     0,
			    0,     0,     0,     1
		)
	{}

	constexpr explicit
	mat4(const vec4& scale) :
		mat4(
			scale.x,       0,       0,       0,
				  0, scale.y,       0,       0,
				  0,       0, scale.z,       0,
				  0,       0,       0, scale.w
		)
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
			aa, ba, ca, da,
			ab, bb, cb, db,
			ac, bc, cc, dc,
			ad, bd, cd, dd
		}
	{}

	constexpr operator const float*() const noexcept { return data; }
	constexpr operator       float*()       noexcept { return data; }

	template<typename Idx>
	constexpr inline const vec4& operator[](Idx idx) const noexcept { return vectors[idx]; }
	template<typename Idx>
	constexpr inline       vec4& operator[](Idx idx)       noexcept { return vectors[idx]; }

	constexpr
	mat4 scale(const vec3& scale) const noexcept {
		return (*this) * scaling(scale);
	}

	constexpr
	mat4 translate(const vec3& off) const noexcept {
		return (*this) * translation(off);
	}

	constexpr
	mat4 transpose() const noexcept {
		mat4 copy;
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				copy[i][j] = (*this)[j][i];
			}
		}
		return copy;
	}

	mat4 rotate(quat const& q) const noexcept {
		return (*this) * rotation(q);
	}

	constexpr
	mat4 operator*(const mat4& other) const noexcept {
		return mat4(
			*this * other[0],
			*this * other[1],
			*this * other[2],
			*this * other[3]
		);
	}

	constexpr
	mat4 operator*(const mat3& other) const noexcept {
		return (*this) * mat4(other);
	}

	constexpr
	vec3 operator*(const vec3& v) const noexcept {
		return vec3(
			v.x * vectors[0][0] + v.y * vectors[1][0] + v.z * vectors[2][0] + vectors[3][0],
			v.x * vectors[0][1] + v.y * vectors[1][1] + v.z * vectors[2][1] + vectors[3][1],
			v.x * vectors[0][2] + v.y * vectors[1][2] + v.z * vectors[2][2] + vectors[3][2]
		);
	}

	constexpr
	vec4 operator*(const vec4& v) const noexcept {
		return vec4(
			v.x * vectors[0][0] + v.y * vectors[1][0] + v.z * vectors[2][0] + v.w * vectors[3][0],
			v.x * vectors[0][1] + v.y * vectors[1][1] + v.z * vectors[2][1] + v.w * vectors[3][1],
			v.x * vectors[0][2] + v.y * vectors[1][2] + v.z * vectors[2][2] + v.w * vectors[3][2],
			v.x * vectors[0][3] + v.y * vectors[1][3] + v.z * vectors[2][3] + v.w * vectors[3][3]
		);
	}

	static
	mat4 rotation(quat const& q) noexcept {
		return mat4(q.to_mat3());
	}

	constexpr static
	mat4 translation(vec3 const& v) noexcept {
		mat4 result;
		result[3].x = v.x;
		result[3].y = v.y;
		result[3].z = v.z;
		return result;
	}

	constexpr
	vec3 translation() const noexcept {
		return vec3(vectors[3][0], vectors[3][1], vectors[3][2]);
	}

	static
	mat4 transform(quat const& rotation, vec3 const& translation, vec3 const& scale = vec3(1)) {
		mat4 result = mat4(mat3(scale) * rotation.to_mat3());
		result[3].x = translation.x;
		result[3].y = translation.y;
		result[3].z = translation.z;
		return result;
	}

	constexpr static
	mat4 scaling(vec3 const& v) noexcept {
		mat4 result;
		result[0][0] = v.x;
		result[1][1] = v.y;
		result[2][2] = v.z;
		return result;
	}

	constexpr static
	mat4 zero() {
		return mat4(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		);
	}

	constexpr static
	mat4 identity() {
		return mat4(1.f);
	}

	mat3 to_mat3() {
		mat3 result;

		for(size_t i = 0; i < 3; i++) {
			for(size_t j = 0; j < 3; j++) {
				result[i][j] = (*this)[i][j];
			}
		}

		return result;
	}
};

inline
mat4 quat::to_mat4() const noexcept {
	return mat4(quat::to_mat3());
}

} // namespace stx
