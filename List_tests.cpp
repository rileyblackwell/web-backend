#include "List.h"
#include "unit_test_framework.h"

using namespace std;


TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_empty) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());    
}

TEST(test_list_size) {
    List<int> empty_list;
    ASSERT_EQUAL(empty_list.size(), 0);
}

TEST(test_list_front) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_list_back) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(list.back(), 1);    
}

TEST(test_list_push_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(list.front(), 3);
}

TEST(test_list_push_back) {
    List<int> list;
    list.push_back(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(list.back(), 1);
}


TEST_MAIN()
