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

TEST(test_list_push_front_and_push_back) {
    List<int> list;
    list.push_front(1);
    list.push_back(2);
    ASSERT_EQUAL(list.front(), 1); 
    ASSERT_EQUAL(list.back(), 2);
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

// Catchs double free memory error.
TEST(test_pop_front_and_pop_back) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.pop_front();
    list.pop_back();
    
    ASSERT_TRUE(list.empty());

    list.push_front(1);
    list.push_front(2); 
    list.pop_back();
    list.pop_front();
    
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

TEST(test_list_copy_ctor) {
    List<int> list1;
    list1.push_front(1);
    List<int> list2(list1);
    ASSERT_EQUAL(list2.front(), 1);
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

TEST(test_iterator_default_ctor) {
    List<int> list;
    list.push_back(1);
    List<int>::Iterator it1;
    ASSERT_TRUE(it1 == list.end()); // nullptr       
}

TEST(test_iterator_derefrence_operator) {
    List<int> list;
    list.push_back(1);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 1);     
}

TEST(test_iterator_prefix_increment_operator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(++*it, 2);        
}

TEST(test_iterator_equal_to_operator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list.end();
    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 == it3);    
}

TEST(test_iterator_not_equal_to_operator) {
    List<int> list;
    list.push_back(1);
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list.end();
    ASSERT_TRUE(it1 != it3);
    ASSERT_FALSE(it1 != it2);     
}

TEST(test_iterator_begin) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    
    ASSERT_EQUAL(*list.begin(), 1);

    list.pop_back();
    list.pop_back();
    ASSERT_TRUE(list.begin() == list.end()); // tests empty list 
}

TEST(test_iterator_end) {
    List<int> list;
    list.push_back(1);
    List<int>::Iterator it2; // nullptr 
    
    ASSERT_TRUE(list.end() == it2); 

    list.pop_back();
    ASSERT_TRUE(list.end() == it2);  // tests empty list
}
 
TEST(test_iterator_erase) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator it = list.begin();
    list.erase(++it); // erase 2nd element
    
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        ASSERT_NOT_EQUAL(*it, 2);
    }  

    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_iterator_erase_first_or_last) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list.erase(list.begin());
    list.erase(++list.begin()); // erases last element
    
    ASSERT_EQUAL(*list.begin(), 2);
    ASSERT_EQUAL(list.size(), 1);  
}

TEST(test_iterator_insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    List<int>::Iterator it = list.begin();
    list.insert(++it, 2); // insert 2nd element

    int num = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        ASSERT_EQUAL(*it, ++num);
    }

    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_iterator_insert_first_or_last) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);
    list.insert(list.begin(), 1);
    list.insert(list.end(), 4);

    int num = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        ASSERT_EQUAL(*it, ++num);
    }

    ASSERT_EQUAL(list.size(), 4); 
}


TEST_MAIN()
