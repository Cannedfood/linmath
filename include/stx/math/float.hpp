#pragma once

#include <cmath>

namespace stx {

constexpr inline
float min(float a, float b) {
	return a < b ? a : b;
}

constexpr inline
float max(float a, float b) {
	return a > b ? a : b;
}

constexpr inline
float clamp(float x, float a, float b) {
	return max(a, min(b, x));
}

constexpr inline
float mix(float a, float b, float k) {
	return a * (1 - k) + b * k;
}

constexpr inline
float clamped_mix(float a, float b, float k) {
	k = clamp(k, 0, 1);
	return a * (1 - k) + b * k;
}

inline
float mix(float a, float b, float k, float time_step, float time_unit = 1) {
	return mix(a, b, 1 - powf(1 - k, time_step / time_unit));
}

} // namespace stx
