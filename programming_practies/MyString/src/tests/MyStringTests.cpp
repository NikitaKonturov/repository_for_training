#include <stdexcept>
#include <gtest/gtest.h>
#include "../funcs/myString.hpp"


TEST(testCaseConstructors, testDefultConstructor)
{
    myString str;
    EXPECT_EQ(str.getSize(), 0);
}

TEST(testCaseConstructors, testSizeConstructor)
{
    myString str(5);
    EXPECT_EQ(5, str.getSize());
    EXPECT_THROW(myString errStr(-5), std::invalid_argument);
}

TEST(testCaseConstructors, testCopyConstructor)
{
    myString str1 = "Hello";
    myString str2(str1);
    ASSERT_EQ(str1.getSize(), str2.getSize());
    for (size_t i = 0; i < str1.getSize(); ++i) {
        EXPECT_EQ(str1[i], str2[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
