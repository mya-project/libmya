#pragma once

/**
 * Returns an array compound literal with the given type and then this size.
 *
 * It should be used with functions that expects arguments like:
 *   fun(int *arr, size_t arr_size);
 *
 * Example:
 *   fun(ARR_ARG(char, 1, 2, 3));
 */
#define ARR_ARG(type, ...) (type[]){ __VA_ARGS__ }, (sizeof((type[]){ __VA_ARGS__ }) / sizeof(type))

/**
 * Same as ARR_ARG() macro, but with the specific type token_type_t.
 */
#define ARR_TT(...) ARR_ARG(token_type_t, __VA_ARGS__)
