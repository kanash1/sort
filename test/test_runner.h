#pragma once

#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <tuple>
#include <utility>

#include "collection_output.h"

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    TestRunner(const TestRunner&) = delete;
    TestRunner(TestRunner&&) = delete;
    void operator=(const TestRunner&) = delete;
    void operator=(TestRunner&&) = delete;

    static TestRunner& Get() {
        static TestRunner instance;
        return instance;
    }

    template <class TestFunc, class... TestArgs>
    static void RunTest(TestFunc func, const std::string& test_name, TestArgs... args) {
        Get().RunTestImpl(func, test_name, std::forward<TestArgs>(args)...);
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    TestRunner() {}

    template <class TestFunc, class... TestArgs>
    void RunTestImpl(TestFunc func, const std::string& test_name, TestArgs... args) {
        try {
            std::apply(func, std::make_tuple(args...));
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
        catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    int fail_count = 0;
};

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)
#define TEST_UNIQ_ID GLUE(id, __LINE__)

#define ASSERT_EQUAL(x, y) {                    \
  std::ostringstream TEST_UNIQ_ID;              \
  TEST_UNIQ_ID << #x << " != " << #y << ", "    \
    << __FILE__ << ":" << __LINE__;             \
  AssertEqual(x, y, TEST_UNIQ_ID.str());        \
}

#define ASSERT(x) {                     \
  std::ostringstream TEST_UNIQ_ID;      \
  TEST_UNIQ_ID << #x << " is false, "   \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, TEST_UNIQ_ID.str());        \
}

#define RUN_TEST(func, ...) \
  TestRunner::RunTest(func, #func,  __VA_ARGS__)

#endif // !TEST_RUNNER_H