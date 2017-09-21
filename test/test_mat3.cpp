#include "test.hpp"

#include <xmath/mat3>

using namespace stx;

#include <iostream>
#include <xlogging>

namespace std {

std::ostream& operator<<(std::ostream& s, mat3 const& m) {
	s
	<< '[' << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ']'
	<< '[' << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ']'
	<< '[' << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ']';
	return s;
}

} // namespace std

namespace {

static float a    = M_PI * .5f;
static float sina = sin(a);
static float cosa = cos(a);

static mat3 rotx = {
	1,    0,     0,
	0, cosa, -sina,
	0, sina,  cosa
};
static mat3 roty = {
	 cosa, 0, sina,
	    0, 1,    0,
	-sina, 0, cosa
};
static mat3 rotz = {
	cosa, -sina, 0,
	sina,  cosa, 0,
	   0,     0, 1
};

} // namespace

static
void test_mat3_multiplication() {
	test(
		mat3(
			2,   3,  5,
			7,  11, 13,
			17, 19, 23) *
		mat3(
			29, 31, 37,
			41, 43, 47,
			53, 59, 61) ==
		mat3(
			 446,  486,  520,
			1343, 1457, 1569,
			2491, 2701, 2925)
	);
}

static
void test_mat3_rotation() {
	test((rotx * vec3::yaxis() - vec3::zaxis()).length2() < 1e-8f);
	test((roty * vec3::zaxis() - vec3::xaxis()).length2() < 1e-8f);
	test((rotz * vec3::xaxis() - vec3::yaxis()).length2() < 1e-8f);
}

static
void test_quat_to_mat3() {
	test(rotx == quat::angle_axis(a, vec3::xaxis()).to_mat3());
	// error("Should be: %%", rotx);
	// error("Is       : %%", quat::angle_axis(a, vec3::xaxis()).to_mat3());

	test(roty == quat::angle_axis(a, vec3::yaxis()).to_mat3());
	// error("Should be: %%", roty);
	// error("Is       : %%", quat::angle_axis(a, vec3::yaxis()).to_mat3());

	test(rotz == quat::angle_axis(a, vec3::zaxis()).to_mat3());
	// error("Should be: %%", rotz);
	// error("Is       : %%", quat::angle_axis(a, vec3::zaxis()).to_mat3());
}

static
void test_determinant() {
	test(mat3(0, 1, 2, 3, 2, 1, 1, 1, 0).determinant() == 3);
}

void test_mat3() {
	test_mat3_multiplication();
	test_mat3_rotation();
	test_quat_to_mat3();
	test_determinant();
}
