#include "List.h"
#include "unit_test_framework.h"

using namespace std;


TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_empty) {
    List<int> list;
    ASSERT_TRUE(list.empty()); 

    list.push_front(1);
    list.pop_front();
    ASSERT_TRUE(list.empty());

    list.push_back(1);
    list.pop_back();
    ASSERT_TRUE(list.empty());    
}

TEST(test_list_size) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);

    list.push_front(1);
    list.push_front(1);
    ASSERT_EQUAL(list.size(), 2);

    list.pop_front();
    ASSERT_EQUAL(list.size(), 1);

    list.pop_front();
    ASSERT_EQUAL(list.size(), 0);
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

TEST(test_pop_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    list.pop_front();
    ASSERT_EQUAL(list.front(), 2); 

    list.pop_front();
    ASSERT_EQUAL(list.front(), 1);

    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(test_pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list.pop_back();
    ASSERT_EQUAL(list.back(), 2); 

    list.pop_back();
    ASSERT_EQUAL(list.back(), 1);

    list.pop_back();
    ASSERT_TRUE(list.empty());    
}

TEST(test_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.clear();
    ASSERT_TRUE(list.empty());    
}

TEST(test_assignment_operator) {
    List<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    List<int> list2;
    list2.push_front(1);

    list2 = list1;
    ASSERT_EQUAL(list2.front(), 2);
    ASSERT_EQUAL(list2.size(), 2);
}

 


TEST_MAIN()
