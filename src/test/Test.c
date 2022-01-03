#include <C2nxt/StdAssert.h>
#include <C2nxt/StdRange.h>
#include <C2nxt/StdLambda.h>
#include <unity.h>

#include "ArrayTest.h"
#include "CheckedMathTest.h"
#include "GcdAndLcmTest.h"
#include "RatioTest.h"
#include "StringTest.h"
#include "VectorTest.h"
#include "LambdaTest.h"

void setUp(void) {
}

void tearDown(void) {
}

i32 main(i32 argc, const_cstring* argv) {
	ignore(argc, argv);

	UNITY_BEGIN();
	TEST_ASSERT_TRUE_MESSAGE(run_string_tests(), "String Tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_array_tests(), "Array tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_vector_tests(), "Vector tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_checked_math_tests(), "Checked Math tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_gcd_and_lcm_tests(), "GCD and LCM tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_ratio_tests(), "StdRatio tests failed to pass");
	TEST_ASSERT_TRUE_MESSAGE(run_lambda_tests(), "StdLambda tests failed to pass");

	return UNITY_END();
}