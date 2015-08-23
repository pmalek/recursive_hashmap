#include "gmock/gmock.h"
#include "HashMap.h"

using namespace testing;

TEST(HashMapTests, HashMap_Correctly_Inserts_And_Withdraws_Elements)
{
    HashMap<int, int> hm;
    hm.put(1, 1);
    int value;
    EXPECT_TRUE(hm.get(1, value));
    EXPECT_EQ(1, value);
    EXPECT_FALSE(hm.get(2, value));
}

TEST(HashMapTests, HashMap_Correctly_Removes_Elements)
{
    HashMap<int, int> hm;
    hm.put(1, 1);
    int value;
    EXPECT_TRUE(hm.get(1, value));
    EXPECT_EQ(1, value);
    hm.remove(1);
    EXPECT_FALSE(hm.get(1, value));
}
