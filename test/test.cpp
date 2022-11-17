#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

#include "profile.h"
#include "collection_output.h"
#include "test_runner.h"
#include "..\sort\sort.h"

template<class Collection>
void fillRandom(Collection& v) {
    for (auto& e : v)
        e = rand() % 10'000;
}

void selectionsort_1(int* l, int* r) {
    for (int* i = l; i < r; i++) {
        int minz = *i, *ind = i;
        for (int* j = i + 1; j < r; j++) {
            if (*j < minz) minz = *j, ind = j;
        }
        std::iter_swap(i, ind);
    }
}

void selectionsort_2(int* l, int* r) {
    for (int* i = l; i < r; i++) {
        int* min = i;
        for (int* j = i + 1; j < r; j++) {
            if (*j < *min) min = j;
        }
        std::iter_swap(i, min);
    }
}

#ifdef _DEBUG
size_t size = 10'000;
#else
size_t size = 100'000;
#endif // _DEBUG



void test_std_sort() {
    std::vector<int> v(size);
    fillRandom(v);
    std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    std::sort(v.begin(), v.end());
    ASSERT_EQUAL(v, expected);
}

// verify
void test_bubble() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::bubble(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

// verify
void test_gnome() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::gnome(v);
    ASSERT_EQUAL(v, expected);
}

// verify
void test_heap() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::heap(v);
    //heapsort(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

// verify
void test_merge() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::merge(v);
    ASSERT_EQUAL(v, expected);
}

// verify
void test_insertion() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::insertion(v);
    ASSERT_EQUAL(v, expected);
}

// verify
void test_comb() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::comb(v);
    ASSERT_EQUAL(v, expected);
}

// TRUBLES
void test_selection_1() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    //sort::selection(v);
    //sort::selection(&v.front(), &v.back() + 1);
    selectionsort_1(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

void test_selection_2() {
    std::vector<int> v(size);
    fillRandom(v);
    //std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    //sort::selection(v);
    //sort::selection(&v.front(), &v.back() + 1);
    selectionsort_2(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

void test_quick() {
    std::vector<int> v(size);
    fillRandom(v);
    std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::quick(v);
    //sort::quicksort(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

void test_intro() {
    std::vector<int> v(size);
    fillRandom(v);
    std::sort(v.rbegin(), v.rbegin() + v.size() / 2);
    std::vector<int> expected(v);
    std::sort(expected.begin(), expected.end());
    sort::intro(v);
    //sort::quicksort(&v.front(), &v.back() + 1);
    ASSERT_EQUAL(v, expected);
}

int main() {
    srand(time(nullptr));
    std::vector<int> v(size);
    fillRandom(v);
    {
        std::vector<int> v1(v);
        LOG_DURATION("selectionsort_1");
        selectionsort_1(&v1.front(), &v1.back() + 1);
    }
    {
        std::vector<int> v2(v);
        LOG_DURATION("selectionsort_2");
        selectionsort_2(&v2.front(), &v2.back() + 1);
    }
    {
        std::vector<int> v3(v);
        LOG_DURATION("sort::selection");
        sort::selection(&v3.front(), &v3.back() + 1);
    }
    //{
    //    LOG_DURATION("heap");
    //    RUN_TEST(test_heap);
    //}
    //{
    //    LOG_DURATION("merge");
    //    RUN_TEST(test_merge);
    //}
    ////{
    ////    LOG_DURATION("insertion");
    ////    RUN_TEST(test_insertion);
    ////}
    /*{
        LOG_DURATION("selection 1");
        RUN_TEST(test_selection_1);
    }
    {
        LOG_DURATION("selection 2");
        RUN_TEST(test_selection_2);
    }*/
    ////{
    ////    LOG_DURATION("bubble");
    ////    RUN_TEST(test_bubble);
    ////}
    //{
    //    LOG_DURATION("comb");
    //    RUN_TEST(test_comb);
    //}
    //{
    //    LOG_DURATION("std::sort");
    //    RUN_TEST(test_std_sort);
    //}
    //{
    //    LOG_DURATION("quick");
    //    RUN_TEST(test_quick);
    //}
    //{
    //    LOG_DURATION("intro");
    //    RUN_TEST(test_intro);
    //}
}