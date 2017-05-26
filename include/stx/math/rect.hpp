#pragma once

#include "vec2.hpp"

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
