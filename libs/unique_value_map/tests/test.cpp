#include <gtest/gtest.h>

#include "UniqueValueMap.hpp"


TEST(UniqueValueMapTest, BasicTest) {
    const UniqueValueMap<int, int, 2> map(std::make_pair(1, 2), std::make_pair(3, 4));
    ASSERT_EQ(1, 2);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}