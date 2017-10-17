#include "test.hpp"

#include <xmath/quat>
#include <xmath/mat3>
#include <xmath/units>

#include <xlogging>

using namespace stx;

static
void test_angle_axis() {
	quat q, req;

	q = quat::angle_axis(45.0_deg, vec3::yaxis());
	req = quat(.924f, 0, .383, 0);
	test((q - req).length2() < 1e-6f);
	q = quat::angle_axis(45.0_deg, vec3::xaxis());
	req = quat(.924f, .383f, 0, 0);
	test((q - req).length2() < 1e-6f);
	q = quat::angle_axis(45.0_deg, vec3::zaxis());
	req = quat(.924f, 0, 0, .383);
	test((q - req).length2() < 1e-6f);
}

static
void test_quat_operations() {
	test(
		((quat(2, 3, 5, 7) * quat(11, 13, 17, 19)) - quat(-235, 35, 123, 101)).length2() == 0
	);

	test(
		((quat(11, 13, 17, 19) * quat(2, 3, 5, 7)) - quat(-235, 83, 55, 129)).length2() == 0
	);

	quat q = quat(2, 3, 5, 7).normalize();
	test((q * q.conjugate() - quat()).length2() < 1e-7f);
}

static
void test_look_at_look_along() {
	vec3
		to1 = vec3(-1, -2, -3).normalize(),
		to2 = vec3(-1, -2,  3).normalize(),
		to3 = vec3(-1,  2, -3).normalize(),
		to4 = vec3( 1,  2,  3).normalize(),
		to5 = vec3( 1, -2, -3).normalize(),
		to6 = vec3( 1, -2,  3).normalize();

	test((quat::look_along(to1) * vec3::forward() - to1).length2() < 0.02f);
	test((quat::look_along(to2) * vec3::forward() - to2).length2() < 0.02f);
	test((quat::look_along(to3) * vec3::forward() - to3).length2() < 0.02f);
	test((quat::look_along(to4) * vec3::forward() - to4).length2() < 0.02f);
	test((quat::look_along(to5) * vec3::forward() - to5).length2() < 0.02f);
	test((quat::look_along(to6) * vec3::forward() - to6).length2() < 0.02f);

	stx::vec3 edgecase1 = vec3(0, 0, 0);
	stx::vec3 edgecase2 = vec3::up();

	test(quat::look_along(edgecase1) == quat());
	test(quat::look_along(edgecase2) == quat::angle_axis(90.0_deg, vec3::xaxis()));

	stx::vec3 got = quat::look_along(to2) * vec3::forward();
	info(
		"have: %% %% %% should: %% %% %%; error: %%",
		got.x, got.y, got.z,
		to2.x, to2.y, to2.z,
		(got - to2).length2()
	);
}

void test_quat() {
	test_quat_operations();
	test_angle_axis();
	test_look_at_look_along();
}
