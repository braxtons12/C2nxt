#ifndef STD_THREAD_TEST
#define STD_THREAD_TEST

#include <C2nxt/StdAtomic.h>
#include <C2nxt/StdThread.h>

#include "Criterion.h"

void LambdaFunction(add_one) {
	let binding = lambda_binding(i32*);
	*(binding._1) += 1;
}

void LambdaFunction(add_loop) {
	let binding = lambda_binding(StdThreadLambda);
	ranged_for(i, 0, 5) {
		lambda_call(binding._1);
	}
}

TEST(StdThread, test_one) {
	i32 val = 0;

	{
		let add_one_lambda = lambda(add_one, &val);
		let thread_lambda = lambda(add_loop, add_one_lambda);
		let_mut res = std_thread_new(lambda_cast(thread_lambda, StdThreadLambda));
		[[maybe_unused]] StdJThread thread = std_result_unwrap(res);

		TEST_ASSERT_NOT_EQUAL(std_this_thread_get_id(), std_thread_get_id(&thread));
	}

	TEST_ASSERT_EQUAL(val, 5);
}

TEST(StdThread, test_multiple) {
	i32 val = 0;

	{
		let add_one_lambda = lambda(add_one, &val);
		let thread_lambda = lambda(add_loop, add_one_lambda);
		let_mut res = std_thread_new(lambda_cast(thread_lambda, StdThreadLambda));
		[[maybe_unused]] StdJThread thread = std_result_unwrap(res);
		let_mut res2 = std_thread_new(lambda_cast(thread_lambda, StdThreadLambda));
		[[maybe_unused]] StdJThread thread2 = std_result_unwrap(res2);

		TEST_ASSERT_NOT_EQUAL(std_this_thread_get_id(), std_thread_get_id(&thread));
		TEST_ASSERT_NOT_EQUAL(std_this_thread_get_id(), std_thread_get_id(&thread2));
		TEST_ASSERT_NOT_EQUAL(std_thread_get_id(&thread), std_thread_get_id(&thread2));
	}

	TEST_ASSERT_TRUE(val >= 5);
}

void LambdaFunction(add_one_synchronized) {
	let binding = lambda_binding(atomic_i32*);
	ignore(atomic_fetch_add(binding._1, 1));
}

TEST(StdThread, test_synchronized) {
	atomic_i32 val = 0;

	{
		let add_one_lambda = lambda(add_one_synchronized, &val);
		let thread_lambda = lambda(add_loop, add_one_lambda);
		let_mut res = std_thread_new(lambda_cast(thread_lambda, StdThreadLambda));
		[[maybe_unused]] StdJThread thread = std_result_unwrap(res);
		let_mut res2 = std_thread_new(lambda_cast(thread_lambda, StdThreadLambda));
		[[maybe_unused]] StdJThread thread2 = std_result_unwrap(res2);

		TEST_ASSERT_NOT_EQUAL(std_this_thread_get_id(), std_thread_get_id(&thread));
		TEST_ASSERT_NOT_EQUAL(std_this_thread_get_id(), std_thread_get_id(&thread2));
		TEST_ASSERT_NOT_EQUAL(std_thread_get_id(&thread), std_thread_get_id(&thread2));
	}

	TEST_ASSERT_EQUAL(atomic_load(&val), 10);
}

#endif // STD_THREAD_TEST