#include <gtest/gtest.h>
#include "String.h"

// Test for default constructor
TEST(StringTest, DefaultConstructor)
{
    String s;
    ASSERT_EQ(s.get(0), '\0');
}

// Test for constructor with C-string
TEST(StringTest, ConstructorWithCString)
{
    String s("hello");
    ASSERT_EQ(s.get(0), 'h');
}

// Test for copy constructor
TEST(StringTest, CopyConstructor)
{
    String s1("hello");
    String s2(s1);
    ASSERT_EQ(s1.get(0), s2.get(0));
}

// Test for set method and COW
TEST(StringTest, SetMethodAndCOW)
{
    String s1("hello");
    String s2(s1);
    s2.set(0, 'j');
    ASSERT_NE(s1.get(0), s2.get(0));
    ASSERT_EQ(s1.get(0), 'h');
    ASSERT_EQ(s2.get(0), 'j');
}

// Test for addition
TEST(StringTest, AdditionOperator)
{
    String s1("hello");
    String s2(" world");
    String s3 = s1 + s2;
    std::string expected = "hello world";
    for (size_t i = 0; i < expected.size(); ++i)
    {
        ASSERT_EQ(s3.get(i), expected[i]);
    }
}

// Test out-of-bound access in get()
TEST(StringTest, OutOfBoundsGet)
{
    String s("hello");
    ASSERT_EQ(s.get(-1), '\0');
    ASSERT_EQ(s.get(5), '\0'); // Za zakresem, jeśli "hello" ma 5 liter
}

// Test Basic COW
TEST(StringTest, CopyOnWriteBasic)
{
    String original("test");
    String copy = original;

    copy.set(0, 'T');

    ASSERT_EQ(original.get(0), 't');
    ASSERT_EQ(copy.get(0), 'T');
}

// Test self-assignment
TEST(StringTest, SelfAssignment)
{
    String s1("initial");
    s1 = s1;
    ASSERT_EQ(s1.get(0), 'i');
    ASSERT_EQ(s1.get(1), 'n');
    ASSERT_EQ(s1.get(2), 'i');
    ASSERT_EQ(s1.get(3), 't');
    ASSERT_EQ(s1.get(4), 'i');
    ASSERT_EQ(s1.get(5), 'a');
    ASSERT_EQ(s1.get(6), 'l');
}

GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}