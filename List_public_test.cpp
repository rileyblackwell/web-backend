#include "List.h"
#include "unit_test_framework.h"

using namespace std;


TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST_MAIN()
