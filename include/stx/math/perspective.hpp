#pragma once

#include "mat4.hpp"
#include "vec2.hpp"

namespace stx {

mat4 perspective(float fov, float width, float height, float zNear, float zFar) {
#ifdef xassert
	xassert(zNear < zFar);
	xassert(zNear == zNear);
	xassert(zFar == zFar);
	xassert(fov > 0);
	xassert(fov == fov);
#endif

	float const h = cosf(0.5f * fov) / sin(0.5f * fov);
	float const w = h * height / width;

	mat4 result = mat4::zero();
	result[0][0] = w;
	result[1][1] = h;
	result[2][3] = -1;

	result[2][2] = -(zFar + zNear) / (zFar - zNear);
	result[3][2] = -(2 * zFar * zNear) / (zFar - zNear);

	// mProjection[2][2] = zFar / (zNear - zFar);
	// mProjection[3][2] = -(zFar * zNear) / (zFar - zNear);

	return result;
}

mat4 orthographic(vec2 const& size, float zNear, float zFar) {
#ifdef xassert
	xassert(zNear < zFar);
	xassert(zNear == zNear && zFar == zFar);
	xassert(size.x != 0 && size.y != 0);
	xassert(size.x == size.x && size.y == size.y);
#endif // defined(xassert)

	mat4 result = mat4().scale(vec3(1 / size.x, 1 / size.y, 2 / (zFar - zNear))).translate(vec3(0, 0, -zNear));

	return result;
}

mat4 ui_space(vec2 const& size = vec2(1)) {
	return mat4::scaling(vec3(1 / size.x, -1 / size.y, 1)).translate(vec3(-1, 1, 0));
}

} // namespace stx
