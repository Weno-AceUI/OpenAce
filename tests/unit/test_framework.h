#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test result tracking
typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
} TestResults;

// Global test results
static TestResults test_results = {0, 0, 0};

// Test assertion macros
#define ASSERT(condition, message) do { \
    if (!(condition)) { \
        printf("Assertion failed: %s\n", message); \
        printf("File: %s, Line: %d\n", __FILE__, __LINE__); \
        test_results.failed_tests++; \
        return; \
    } \
    test_results.passed_tests++; \
} while(0)

#define ASSERT_EQUAL(expected, actual, message) do { \
    if ((expected) != (actual)) { \
        printf("Assertion failed: %s\n", message); \
        printf("Expected: %d, Got: %d\n", (int)(expected), (int)(actual)); \
        printf("File: %s, Line: %d\n", __FILE__, __LINE__); \
        test_results.failed_tests++; \
        return; \
    } \
    test_results.passed_tests++; \
} while(0)

#define ASSERT_STR_EQUAL(expected, actual, message) do { \
    if (strcmp((expected), (actual)) != 0) { \
        printf("Assertion failed: %s\n", message); \
        printf("Expected: %s, Got: %s\n", (expected), (actual)); \
        printf("File: %s, Line: %d\n", __FILE__, __LINE__); \
        test_results.failed_tests++; \
        return; \
    } \
    test_results.passed_tests++; \
} while(0)

// Test case definition
#define TEST_CASE(name) void name(void)

// Test suite definition
#define TEST_SUITE(name) void name(void)

// Test runner
#define RUN_TEST(test) do { \
    printf("Running test: %s\n", #test); \
    test(); \
    test_results.total_tests++; \
} while(0)

// Print test results
#define PRINT_TEST_RESULTS() do { \
    printf("\nTest Results:\n"); \
    printf("Total Tests: %d\n", test_results.total_tests); \
    printf("Passed: %d\n", test_results.passed_tests); \
    printf("Failed: %d\n", test_results.failed_tests); \
} while(0)

#endif // TEST_FRAMEWORK_H 