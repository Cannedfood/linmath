#pragma once

#include <cmath>

namespace stx {

template<typename T> constexpr inline
T min(const T& a, const T& b) {
	return a < b ? a : b;
}

template<typename T> constexpr inline
T max(const T& a, const T& b) {
	return a > b ? a : b;
}

template<typename T> constexpr inline
T clamp(const T& a, const T& minv, const T& maxv) {
	return min(max(a, minv), maxv);
}

} // namespace stx
