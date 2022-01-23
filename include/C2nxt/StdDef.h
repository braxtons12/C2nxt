/// @file StdDef.h
/// @author Braxton Salyer <braxtonsalyer@gmail.com>
/// @brief StdDef provides various `#define`s for performing basic tasks and macro-related
/// functions.
/// @version 0.2
/// @date 2022-01-19
///
/// MIT License
/// @copyright Copyright (c) 2022 Braxton Salyer <braxtonsalyer@gmail.com>
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

/// @defgroup std_def Standard Defines
/// This module provides various `#define`s for performing basic tasks and macro-related functions,
/// and some small meta-programming functionality

#include <C2nxt/mpl/StdArgLists.h>
#include <C2nxt/mpl/StdPPBool.h>
#include <C2nxt/mpl/StdPPMath.h>
#include <C2nxt/mpl/StdPPStrings.h>
#include <C2nxt/mpl/StdPPTuple.h>
#include <stdbool.h>

#ifndef STD_DEF
	/// @brief definitions related to Standard Defines
	#define STD_DEF

	/// @brief The major portion of the version number of the C2nxt library
	/// e.g. in "x.y.z", the "x" part.
	/// @ingroup std_def
	#define STD_VERSION_MAJOR 0
	/// @brief The minor portion of the version number of the C2nxt library
	/// e.g. in "x.y.z", the "y" part.
	/// @ingroup std_def
	#define STD_VERSION_MINOR 2
	/// @brief The patch portion of the version number of the C2nxt library
	/// e.g. in "x.y.z", the "z" part.
	/// @ingroup std_def
	#define STD_VERSION_PATCH 0

	/// @brief The version number of the C2nxt library parsed into a single 32-bit integer
	/// Each portion of the version number will take 8 bits in the resulting integer,
	/// with the total parsed version number comprising of the lower 24 bits.
	/// The layout is `00000000xxxxxxxxyyyyyyyyzzzzzzzz` where:
	/// * `xxxxxxxx` comprises `STD_VERSION_MAJOR`
	/// * `yyyyyyyy` comprises `STD_VERSION_MINOR`
	/// * `zzzzzzzz` comprises `STD_VERSION_PATCH`
	/// @ingroup std_def
	#define STD_VERSION \
		((STD_VERSION_MAJOR << 16) | (STD_VERSION_MINOR << 8) | (STD_VERSION_PATCH << 0))

	/// @brief Provides a semi-unique variable name with `x` as a prefix
	///
	/// Useful inside macros to prevent name-collision and/or shadowing.
	/// Does not create a __truly__ unique variable name, so must be used with some care, but is
	/// good for most circumstances. The produced name is not cachable/storable and depends on
	/// `__LINE__`, so cannot be re-referenced later in a file, so this is only useful for
	/// one-time-use names or for use inside macros
	///
	/// @param x - The prefix for the variable name
	///
	/// @return The resulting variable name
	/// @ingroup std_def
	#define UNIQUE_VAR(x) CONCAT3(x, _4x2_, __LINE__)

	/// @brief Returns the type of the given expression
	///
	/// @param value - The expression to get the resulting type of
	///
	/// @return the type of the expression
	/// @ingroup std_def
	#define typeof(value) __typeof__(value)

	#if defined(__clang__)
		/// @brief Disables the preceding/following function at compile-time
		///
		/// Forces a compiler error with the given message if the associated function is called.
		///
		/// @param message - The error message for the compiler to show the user
		/// @ingroup std_def
		#define std_disable(message) __attribute__((diagnose_if(true, (message), "error")))
		/// @brief Disables the preceding/following function at compile-time, based on the given
		/// `condition`
		///
		/// Forces a compiler error with the given message if the associated function is called and
		/// `condition` evaluates to `true`. `condition` can include parameters to the function if
		/// this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_disable_if(a < b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether the function should be disabled
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_disable_if(condition, message) \
			__attribute__((diagnose_if((condition), (message), "error")))
		/// @brief Enables the preceding/following function at compile-time, based on the given
		/// `condition`
		///
		/// Forces a compiler error with the given message if the associated function is called and
		/// `condition` evaluates to `false`. `condition` can include parameters to the function if
		/// this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_enable_if(a > b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether the function should be enabled
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_enable_if(condition, message) std_disable_if(!(condition), (message))
		/// @brief Emits a warning for using the preceding/following function at compile-time, based
		/// on the given `condition`
		///
		/// Forces a compiler warning with the given message if the associated function is called
		/// and `condition` evaluates to `true`. `condition` can include parameters to the function
		/// if this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_warn_if(a < b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether using the function should cause a
		/// warning
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_warn_if(condition, message) \
			__attribute__((diagnose_if((condition), (message), "warning")))
	#else
		/// @brief Disables the preceding/following function at compile-time
		///
		/// Forces a compiler error with the given message if the associated function is called.
		///
		/// @param message - The error message for the compiler to show the user
		/// @ingroup std_def
		#define std_disable(message) __attribute__((error(message)))
		/// @brief Disables the preceding/following function at compile-time, based on the given
		/// `condition`
		///
		/// Forces a compiler error with the given message if the associated function is called and
		/// `condition` evaluates to `true`. `condition` can include parameters to the function if
		/// this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_disable_if(a < b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether the function should be disabled
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_disable_if(condition, message)
		/// @brief Enables the preceding/following function at compile-time, based on the given
		/// `condition`
		///
		/// Forces a compiler error with the given message if the associated function is called and
		/// `condition` evaluates to `false`. `condition` can include parameters to the function if
		/// this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_enable_if(a > b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether the function should be enabled
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_enable_if(condition, message)
		/// @brief Emits a warning for using the preceding/following function at compile-time, based
		/// on the given `condition`
		///
		/// Forces a compiler warning with the given message if the associated function is called
		/// and `condition` evaluates to `true`. `condition` can include parameters to the function
		/// if this is applied as a postfix, thus enabling things like:
		/// @code {.c}
		/// int func(int a, int b) std_warn_if(a < b, "a must be greater than b") {
		/// 	// do things here...
		/// }
		/// @endcode
		///
		/// @param condition - The condition indicating whether using the function should cause a
		/// warning
		/// @param message - The error message for the compiler to show the user
		///
		/// @note This is only available when compiling with Clang
		///
		/// @ingroup std_def
		#define std_warn_if(condition, message)
	#endif

	/// @brief Specify that the given scope is unreachable
	/// @ingroup std_def
	#define unreachable() __builtin_unreachable()
	/// @brief Specify that the given variable of function may be unused
	/// @ingroup std_def
	#define maybe_unused __attribute__((unused))
	/// @brief Specify that the following function should always be inlined
	/// @ingroup std_def
	#define always_inline __attribute__((always_inline))

	/// @brief Use this macro to declare a variable that will have a cleanup function called on it
	/// at scope end.
	///
	/// This allows for automatic RAII-style handling of resources by guaranteeing that the variable
	/// will have whatever cleanup needs performed on it completed at scope end.
	///
	/// @param scope_end_func - The function to call on the declared variable when it goes out of
	/// scope
	/// @ingroup std_def
	#define scoped(scope_end_func) __attribute__((cleanup(scope_end_func)))

	/// @brief Declare a variable with `let` to create a `const` variable with inferred type.
	///
	/// `let` declares the variable as const and infers the type from the value being assigned to
	/// it. A variable declared with `let` will be `const` and thus read only. `let` should be
	/// preferred for all variable declarations, whenever possible.
	/// @ingroup std_def
	#define let const __auto_type
	/// @brief Declare a variable with `let_mut` to create a mutable variable with inferred type.
	///
	/// `let_mut` declares the variable and infers the type from the value being assigned to it.
	/// A variable declared with `let_mut` will be mutable and thus able to be modified.
	/// `let_mut` should be preferred for all variable declarations when mutability is required,
	/// whenever possible.
	///
	/// @note When compiling with GCC, `let_mut` may infer the constness of the value being assigned
	/// as part of the type, which means a `const_cast` or temporary ignoring of
	/// "-Wdiscarded-qualifiers" may be necessary
	/// @ingroup std_def
	#define let_mut __auto_type

	/// @brief shorthand for writing `T_ptr`, used for generating typedef names needed for macros
	/// that require an alphanumeric name for `T*`
	///
	/// @param T - The type to generate a name for "pointer to" for
	///
	/// @ingroup std_def
	#define Ptr(T) CONCAT2(T, _ptr)
	/// @brief shorthand for writing `T_ptr`, used for generating typedef names needed for macros
	/// that require an alphanumeric name for `T*` when implying reference-like semantics
	///
	/// @param T - The type to generate a name for "pointer to" for
	///
	/// @ingroup std_def
	#define Ref(T) CONCAT2(T, _ref)
	/// @brief shorthand for writing `const_T_ptr`, used for generating typedef names needed for
	/// macros that require an alphanumeric name for `const T*` when implying reference-like
	/// semantics
	///
	/// @param T - The type to generate a name for "pointer to const" for
	///
	/// @ingroup std_def
	#define ConstRef(T) CONCAT3(const_, T, _ref)

	/// @brief Shorthand for writing a `for` loop.
	///
	/// Expands to a `for` loop with loop variable `var` initialized to `begin` and ending at `end`
	/// non-inclusive.
	/// Example:
	/// @code {.c}
	/// // loops over the range [0, 10)
	/// ranged_for(i, 0, 10) {
	///		// do something here ...
	/// }
	/// @endcode
	///
	/// @param var - The name of the loop variable
	/// @param begin - The initial value for `var`
	/// @param end - The stop value for `var`
	/// @ingroup std_def
	#define ranged_for(var, begin, end) for(let_mut var = (begin); (var) < (end); ++(var))

	/// @brief Ignores the given parameters.
	///
	/// Use to ignore the passed parameters, preventing compiler warnings for parameters that are
	/// intentionally unused
	/// @ingroup std_def
	#define ignore(...) (void)(__VA_ARGS__)

	/// @brief Casts to the type `Type`.
	///
	/// This should be preferred for making non-lossy conversions between types (eg `i8`
	/// to `i32` or `void*` to `cstring`)
	///
	/// @param Type - The type to cast to
	/// @ingroup std_def
	#define static_cast(Type) (Type)
	/// @brief Casts to the type `Type`.
	///
	/// This should be preferred for making lossy conversions between types (eg `i32` to `f32` or
	/// `u64` to `i64`)
	///
	/// @param Type - The type to cast to
	/// @ingroup std_def
	#define narrow_cast(Type) (Type)
	/// @brief Casts to the type `Type`.
	///
	/// This should be preferred when casting away const-ness of a value
	/// (eg `const_cstring` to `cstring`)
	///
	/// @param Type - The type to cast to
	/// @ingroup std_def
	#define const_cast(Type) (Type)

	#undef false
	/// @brief Define the boolean constant `false`
	///
	/// Redefine `false` as casted to bool to enforce correct type inference with `let` and
	/// `let_mut`
	/// @ingroup std_def
	#define false static_cast(bool)(0)

	#undef true
	/// @brief Define the boolean constant `true`
	///
	/// Redefine `true` as casted to bool to enforce correct type inference with `let` and
	/// `let_mut`
	/// @ingroup std_def
	#define true static_cast(bool)(1)

	/// @brief Concatenates an arbitrary number of arguments
	///
	/// The arguments must be alphanumeric, macro-concatenation compatible sequences of characters
	///
	/// @param ... - The arguments to concatenate
	/// @ingroup std_pp_strings
	#define CONCAT(...) CONCAT2_DEFERRED(CONCAT, PP_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
	/// @brief Concatenates an arbitrary number of arguments, with one additional layer of
	/// indirection
	///
	/// The arguments must be alphanumeric, macro-concatenation compatible sequences of characters.
	/// This is useful for use in a macro chain when the result must be deferred through one-further
	/// stage of macro replacement than the normal `CONCAT(...)` provides
	///
	/// @param ... - The arguments to concatenate
	/// @ingroup std_pp_strings
	#define CONCAT_DEFERRED(...) CONCAT(__VA_ARGS__)

	/// @brief Creates a scope for wrapping an arbitrary number of variable declarations in with
	/// subsequent uses of `SCOPE_VARIABLE()`.
	/// The net scope will make up one single compound-statement.
	/// @ingroup std_def
	#define BEGIN_SCOPED_VARIABLES()                                           \
		for(let_mut UNIQUE_VAR(scope_break) = 0; UNIQUE_VAR(scope_break) != 1; \
			UNIQUE_VAR(scope_break) = 1)

	/// @brief Wraps the given variable declaration(s) in a containing scope.
	/// The scope must have been previously initiated with `BEGIN_SCOPED_VARIABLES()`.
	/// Variable declarations must be compatible with the initialization statement (aka the "clause"
	/// statement) in a for loop.
	/// The net scope will make one a single compound-statement
	/// @ingroup std_def
	#define SCOPE_VARIABLE(...) \
		for(__VA_ARGS__; UNIQUE_VAR(scope_break) != 1; UNIQUE_VAR(scope_break) = 1)

	#if STD_PLATFORM_COMPILER_CLANG
		#define IGNORE_RESERVED_IDENTIFIER_WARNING_START \
			_Pragma("GCC diagnostic push")               \
				_Pragma("GCC diagnostic ignored \"-Wreserved-identifier\"")
		#define IGNORE_RESERVED_IDENTIFIER_WARNING_STOP _Pragma("GCC diagnostic pop")

		#define IGNORE_SHADOW_WARNING_START \
			_Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wshadow\"")
		#define IGNORE_SHADOW_WARNING_STOP _Pragma("GCC diagnostic pop")

		#define IGNORE_SWITCH_ENUM_WARNING_START \
			_Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wswitch-enum\"")
		#define IGNORE_SWITCH_ENUM_WARNING_STOP _Pragma("GCC diagnostic pop")
	#endif // STD_PLATFORM_COMPILER_CLANG
#endif	   // STD_DEF
