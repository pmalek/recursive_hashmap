#include "gmock/gmock.h"
#include "HashNode.h"

using namespace testing;

TEST(HashNodeTests, HashNodeIntInt_Constructs_With_Correct_Key_And_Value)
{
    HashNode<int, int> hn(1, 1);
    EXPECT_EQ(1, hn.getKey());
    EXPECT_EQ(1, hn.getValue());
}

TEST(HashNodeTests, Newly_Constructed_HashNode_Has_nullptr_As_Next_Node)
{
    HashNode<int, int> hn(1, 1);
    EXPECT_EQ(nullptr, hn.getNext());
}

TEST(HashNodeTests, SetValue_Correctly_Sets_Value)
{
    HashNode<int, int> hn(1, 1);
    hn.setValue(10);
    EXPECT_EQ(10, hn.getValue());
}

TEST(HashNodeTests, SetNext_Correctly_Sets_Next_Node)
{
    HashNode<int, int> hn1(1, 1);
    HashNode<int, int> hn2(2, 2);
    hn1.setNext(&hn2);
    EXPECT_EQ(hn2, *hn1.getNext());
}
