#pragma once

#include "mat3.hpp"
#include "mat4.hpp"
#include "quat.hpp"

namespace stx {

/// Converts a quaternion to a 3x3 rotation matrix. @ingroup stxmath
/// Adapted from java source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
mat3 rotate(const quat& q) {
	mat3 m;

	float sqw = q.w * q.w;
	float sqx = q.x * q.x;
	float sqy = q.y * q.y;
	float sqz = q.z * q.z;
	m[0][0] = sqx - sqy - sqz + sqw; // since sqw + sqx + sqy + sqz =1
	m[1][1] = -sqx + sqy - sqz + sqw;
	m[2][2] = -sqx - sqy + sqz + sqw;

	float tmp1 = q.x * q.y;
	float tmp2 = q.z * q.w;
	m[0][1] = 2.0 * (tmp1 + tmp2);
	m[1][0] = 2.0 * (tmp1 - tmp2);

	tmp1 = q.x * q.z;
	tmp2 = q.y * q.w;
	m[0][2] = 2.0 * (tmp1 - tmp2);
	m[2][0] = 2.0 * (tmp1 + tmp2);

	tmp1 = q1.y * q.z;
	tmp2 = q1.x * q.w;
	m[1][2] = 2.0 * (tmp1 + tmp2);
	m[1][2] = 2.0 * (tmp1 - tmp2);
}

/// Generates a scaling 3x3 matrix. @ingroup stxmath
mat3 scale(const vec3& v) {
	return mat3 {
		v.x, 0, 0,
		0, v.y, 0,
		0, 0, v.z
	};
}

} // namespace stx
