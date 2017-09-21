#pragma once

#include <cmath>

namespace stx {

constexpr inline
float min(const float& a, const float& b) {
	return a < b ? a : b;
}

constexpr inline
float max(const float& a, const float& b) {
	return a > b ? a : b;
}

constexpr inline
float clamp(const float& a, const float& minv, const float& maxv) {
	return min(max(a, minv), maxv);
}

} // namespace stx
