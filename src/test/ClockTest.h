#include <C2nxt/time/StdClock.h>

#if __has_include(<unistd.h>)
	#define HAS_SLEEP 1
	#include <unistd.h>
#else
	#define HAS_SLEEP 0
#endif

void test_system_clock(void) {
	let min_val = std_min_value(i64);
	let max_val = std_max_value(i64);

	TEST_ASSERT_TRUE(std_clock_resolution(&std_system_clock) == STD_CLOCK_MICROSECONDS);
	TEST_ASSERT_TRUE(
		std_ratio_equal(std_clock_resolution_as_ratio(&std_system_clock), std_microseconds_period));
	TEST_ASSERT_TRUE(std_time_point_equal(std_clock_min_time_point(&std_system_clock),
										  std_time_point_new(std_microseconds(min_val))));
	TEST_ASSERT_TRUE(std_time_point_equal(std_clock_max_time_point(&std_system_clock),
										  std_time_point_new(std_microseconds(max_val))));

	let first = std_clock_now(&std_system_clock);
	let second = std_clock_now(&std_system_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than_or_equal(first, second));

#if HAS_SLEEP
	sleep(1);
	let third = std_clock_now(&std_system_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than(first, third));
#endif
}

#if !STD_NO_MONOTONIC_CLOCK
void test_steady_clock(void) {
	let min_val = std_min_value(i64);
	let max_val = std_max_value(i64);

	TEST_ASSERT_TRUE(std_clock_resolution(&std_steady_clock) == STD_CLOCK_NANOSECONDS);
	TEST_ASSERT_TRUE(
		std_ratio_equal(std_clock_resolution_as_ratio(&std_steady_clock), std_nanoseconds_period));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_min_time_point(&std_steady_clock),
		std_time_point_new_with_clock(std_nanoseconds(min_val), &std_steady_clock)));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_max_time_point(&std_steady_clock),
		std_time_point_new_with_clock(std_nanoseconds(max_val), &std_steady_clock)));

	let first = std_clock_now(&std_steady_clock);
	let second = std_clock_now(&std_steady_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than_or_equal(first, second));

	#if HAS_SLEEP
	sleep(1);
	let third = std_clock_now(&std_steady_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than(first, third));
	#endif
}
#endif // !STD_NO_MONOTONIC_CLOCK

void test_high_resolution_clock(void) {
	let min_val = std_min_value(i64);
	let max_val = std_max_value(i64);

#if !STD_NO_MONOTONIC_CLOCK
	TEST_ASSERT_TRUE(std_clock_resolution(&std_high_resolution_clock) == STD_CLOCK_NANOSECONDS);
	TEST_ASSERT_TRUE(std_ratio_equal(std_clock_resolution_as_ratio(&std_high_resolution_clock),
									 std_nanoseconds_period));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_min_time_point(&std_high_resolution_clock),
		std_time_point_new_with_clock(std_nanoseconds(min_val), &std_high_resolution_clock)));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_max_time_point(&std_high_resolution_clock),
		std_time_point_new_with_clock(std_nanoseconds(max_val), &std_high_resolution_clock)));
#else
	TEST_ASSERT_TRUE(std_clock_resolution(&std_high_resolution_clock) == STD_CLOCK_MICROSECONDS);
	TEST_ASSERT_TRUE(std_ratio_equal(std_clock_resolution_as_ratio(&std_high_resolution_clock),
									 std_microseconds_period));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_min_time_point(&std_high_resolution_clock),
		std_time_point_new_with_clock(std_microseconds(min_val), &std_high_resolution_clock)));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_max_time_point(&std_high_resolution_clock),
		std_time_point_new_with_clock(std_microseconds(max_val), &std_high_resolution_clock)));
#endif // !STD_NO_MONOTONIC_CLOCK

	let first = std_clock_now(&std_high_resolution_clock);
	let second = std_clock_now(&std_high_resolution_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than_or_equal(first, second));

#if HAS_SLEEP
	sleep(1);
	let third = std_clock_now(&std_high_resolution_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than(first, third));
#endif
}

void test_utc_clock(void) {
	let min_val = std_min_value(i64);
	let max_val = std_max_value(i64);

	TEST_ASSERT_TRUE(std_clock_resolution(&std_utc_clock) == STD_CLOCK_MICROSECONDS);
	TEST_ASSERT_TRUE(
		std_ratio_equal(std_clock_resolution_as_ratio(&std_utc_clock), std_microseconds_period));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_min_time_point(&std_utc_clock),
		std_time_point_new_with_clock(std_microseconds(min_val), &std_utc_clock)));
	TEST_ASSERT_TRUE(std_time_point_equal(
		std_clock_max_time_point(&std_utc_clock),
		std_time_point_new_with_clock(std_microseconds(max_val), &std_utc_clock)));

	let first = std_clock_now(&std_utc_clock);
	let second = std_clock_now(&std_utc_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than_or_equal(first, second));

#if HAS_SLEEP
	sleep(1);
	let third = std_clock_now(&std_utc_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than(first, third));
#endif
}

void test_local_clock(void) {
	// TODO(braxtons12): Come up with a reliable way to test min and max time point, considering the
	// UTC offset will be different for each person who runs the tests

	// let min_val = std_min_value(i64);
	// let max_val = std_max_value(i64);

	TEST_ASSERT_TRUE(std_clock_resolution(&std_local_clock) == STD_CLOCK_MICROSECONDS);
	TEST_ASSERT_TRUE(
		std_ratio_equal(std_clock_resolution_as_ratio(&std_local_clock), std_microseconds_period));
	//	TEST_ASSERT_TRUE(std_time_point_equal(
	//		std_clock_min_time_point(&std_local_clock),
	//		std_time_point_new_with_clock(std_microseconds(min_val), &std_local_clock)));
	//	TEST_ASSERT_TRUE(std_time_point_equal(
	//		std_clock_max_time_point(&std_local_clock),
	//		std_time_point_new_with_clock(std_microseconds(max_val), &std_local_clock)));

	let first = std_clock_now(&std_local_clock);
	let second = std_clock_now(&std_local_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than_or_equal(first, second));

#if HAS_SLEEP
	sleep(1);
	let third = std_clock_now(&std_local_clock);
	TEST_ASSERT_TRUE(std_time_point_less_than(first, third));
#endif
}

static bool run_clock_tests(void) {
	RUN_TEST(test_system_clock);
	RUN_TEST(test_steady_clock);
	RUN_TEST(test_high_resolution_clock);
	RUN_TEST(test_utc_clock);
	RUN_TEST(test_local_clock);

	return true;
}