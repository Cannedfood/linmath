#include "test.hpp"

#include <xmath/vec2>
#include <xmath/vec3>
#include <xmath/vec4>

using namespace stx;

namespace {

template<typename vecN>
void test_vecN() {
	constexpr size_t N = vecN::Dimensions();

	vecN v;
	for (size_t i = 0; i < N; i++)
		test(v[i] == 0);

	v = vecN(1);
	for (size_t i = 0; i < N; i++)
		test(v[i] == 1);

	v *= 2;
	for (size_t i = 0; i < N; i++)
		test(v[i] == 2);

	v *= v;
	for (size_t i = 0; i < N; i++)
		test(v[i] == 4);

	v += v;
	for (size_t i = 0; i < N; i++)
		test(v[i] == 8);

	v -= v;
	for (size_t i = 0; i < N; i++)
		test(v[i] == 0);
}

void test_vec2() {
	test_vecN<vec2>();
}

void test_vec3() {
	test_vecN<vec3>();

	{
		vec3 v1(5, 10, 8);
		vec3 v2(100, 3, 60);

		vec3 cross_v1_v2 = v1.cross(v2);

		test(v1.dot(cross_v1_v2) == 0);
		test(v2.dot(cross_v1_v2) == 0);
	}
}

void test_vec4() {
	test_vecN<vec4>();
}

} // namespace

void test_vec() {
	test_vec2();
	test_vec3();
	test_vec4();
}
