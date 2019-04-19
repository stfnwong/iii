/* TEST_TRIT 
 * Tests for trit object
 *
 * Stefan Wong 2019
 */

#include <iostream> 
#include <iomanip>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "trit.hpp"


class TestTrit : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(TestTrit, test_init)
{
    // Create a new trit
    iii::Trit test_trit;
    std::cout << "Trit value : " << test_trit.toString() << std::endl;
    ASSERT_EQ(iii::TR_UNK, test_trit.value);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

