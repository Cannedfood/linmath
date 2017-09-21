#pragma once

#include "mat4.hpp"
#include "vec2.hpp"

namespace stx {

static
mat4 perspective(float fovy, float width, float height, float zNear, float zFar) {
#ifdef xassert
	xassert(zNear < zFar);
	xassert(zNear == zNear);
	xassert(zFar == zFar);
	xassert(fovy == fovy);
	xassert(fovy > 0);
	xassertmsg(fovy < M_PI, "FOV is in radians and has to be smaller than 180 degrees (smaller than pi)");
#endif

	float const aspect      = width / height;
	float const tanHalfFovy = tan(fovy / 2.f);

	mat4 result = mat4::zero();
	result[0][0] = 1.f / (aspect * tanHalfFovy);
	result[1][1] = 1.f / tanHalfFovy;
	result[2][3] = -1.f;

	// Depth zero to one
	result[2][2] = zFar / (zNear - zFar);
	result[3][2] = -(zFar * zNear) / (zFar - zNear);

	// Depth negative one to one
	// result[2][2] = - (zFar + zNear) / (zFar - zNear);
	// result[3][2] = - (2.f * zFar * zNear) / (zFar - zNear);

	return result;
}

constexpr static
mat4 orthographic(vec2 const& size, float zNear, float zFar) {
#ifdef xassert
	xassert(zNear < zFar);
	xassert(zNear == zNear && zFar == zFar);
	xassert(size.x != 0 && size.y != 0);
	xassert(size.x == size.x && size.y == size.y);
#endif // defined(xassert)

	mat4 result = mat4::identity();

	result[0][0] = 2.f / -size.x;
	result[1][1] = 2.f / -size.y;
	result[3][0] = 0;
	result[3][1] = 0;

	// Depth zero to one
	// result[2][2] = -1.f / (zFar - zNear);
	// result[3][2] = -zNear / (zFar - zNear);

	// Depth negative one to one
	// result[2][2] = -2.f / (zFar - zNear);
	// result[3][2] = -(zFar + zNear) / (zFar - zNear);

	return result;
}

constexpr static
mat4 ui_space(vec2 const& size = vec2(1)) {
#ifdef xassert
	xassert(size.x >= 1);
	xassert(size.y >= 1);
#endif // defined(xassert)

	mat4 transform;
	transform[0][0] =  2 / size.x;
	transform[1][1] = -2 / size.y;
	transform[3][0] = -1;
	transform[3][1] =  1;
	return transform;
}

} // namespace stx
