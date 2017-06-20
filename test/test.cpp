#include "test.hpp"

#include <cstddef>
#include <iostream>

#include <mutex>

// Test compile only
int tests = 0;
int fails = 0;

std::mutex lock;

void _testResult(const char* file, int line, const char* fn, const char* test, bool value) {
	static const char* last_fn = nullptr;

	std::lock_guard<std::mutex> guard(lock);
	++tests;
	if(value) {
		if(last_fn != fn) {
			std::cout << file << ": " << fn << "'" << std::endl;
			last_fn = fn;
		}
	}
	else {
		std::cerr << file << ":" << line << ": error in '" << fn << "' test(" << test << ")  " << "FAIL" << std::endl;
		++fails;
	}
}

extern void test_vec();
extern void test_mat3();
extern void test_mat4();
extern void test_quat();

int main(int argc, char const** argv) {
	test_vec();
	test_mat3();
	test_mat4();
	test_quat();

	std::cout << "tests: "  << tests << std::endl;
	std::cout << "passed: " << tests - fails << std::endl;
	std::cout << "FAILED: " << fails << std::endl;

	return fails == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
