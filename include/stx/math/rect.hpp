#pragma once

#include "vec2.hpp"
#include "vec3.hpp"

namespace stx {

/// A axis aligned rectangle defined by maximum and minimum @ingroup stxmath
struct quad {
	union {
		struct {
			vec2 min;
			vec2 max;
		};
		struct {
			float minx;
			float miny;
			float maxx;
			float maxy;
		};
	};

	constexpr
	quad() : quad(0, 0, 0, 0) {}

	constexpr
	quad(vec2 const& mn, vec2 const& mx) : min(mn), max(mx) {}

	constexpr
	quad(float mnx, float mny, float mxx, float mxy) : min(mnx, mny), max(mxx, mxy) {}

	constexpr
	vec2 size() const noexcept { return max - min; }

	constexpr
	float width() const noexcept { return max.x - min.x; }

	constexpr
	float height() const noexcept { return max.y - min.y; }
};

/// A axis aligned rectangle defined by minumum and size @ingroup stxmath
struct rect {
	union {
		struct {
			vec2 position;
			vec2 size;
		};
		struct {
			float x;
			float y;
			float width;
			float height;
		};
	};

	constexpr
	rect() : rect(0, 0, 0, 0) {}

	constexpr
	rect(vec2 const& pos, vec2 const& sz) : position(pos), size(sz) {}

	constexpr
	rect(float x, float y, float w, float h) : position(x, y), size(w, h) {}

	constexpr inline
	vec2 max() const noexcept { return position + size; }
};

/// A axis aligned cuboid defined by maximum and minimum @ingroup stxmath
struct box {
	union {
		struct {
			vec3 min;
			vec3 max;
		};
		struct {
			float minx;
			float miny;
			float minz;
			float maxx;
			float maxy;
			float maxz;
		};
	};
};

/// A axis aligned cuboid defined by minumum and size @ingroup stxmath
struct cuboid {
	union {
		struct {
			vec3 position;
			vec3 size;
		};
		struct {
			float x;
			float y;
			float z;
			float width;
			float height;
			float depth;
		};
	};
};

} // namespace stx
