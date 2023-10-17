#include <algorithm>
#include <vector>
#include <map>

#include "collection_output.h"
#include "test_runner.h"
#include "profile.h"
#include "..\sort\sort.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define RUN_SORT_TEST(test_func, sort_func, coll) \
    TestRunner::RunTest(test_func, STR(sort_func), sort_func, coll)

#ifdef _DEBUG
size_t size = 1'000;
#else
size_t size = 10'000;
#endif // _DEBUG

template<class Sort>
void testSort(Sort sort, std::vector<int> v) {
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort(v.begin(), v.end());
    ASSERT_EQUAL(v, expected);
}

void testCombSort(std::vector<int> v) {
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::comb(v.begin(), v.end());
    ASSERT_EQUAL(v, expected);
}

void testAll() {
    using RandomIt = std::vector<int>::iterator;
    using Sort = void (*)(RandomIt, RandomIt);

    std::vector<int> v(size);
    std::generate(v.begin(), v.end(), std::rand);

    RUN_SORT_TEST(testSort<Sort>, sort::bubble<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::insertion<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::shell<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::selection<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::heap<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::stooge<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::gnome<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::merge<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::intro<RandomIt>, v);
    RUN_SORT_TEST(testSort<Sort>, sort::quick<RandomIt>, v);
    RUN_TEST(testCombSort, v);
}

template<class UnitOfTime = std::chrono::milliseconds, class Sort, class Collection>
void logSortDuration(const std::string& logName, Sort sort, Collection coll) {
    LOG_DURATION(logName, UnitOfTime);
    sort(coll.begin(), coll.end());
}

int main() {
    testAll();
}