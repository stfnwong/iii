/* TEST_TRYTE 
 * Tests for Tryte object
 *
 * Stefan Wong 2019
 */

#include <iostream> 
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "tryte.hpp"


class TestTryte : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown() {}
};


TEST_F(TestTryte, test_init)
{
    // Create a new tryte
    iii::Tryte test_tryte;
    std::cout << "Tryte value : " << test_tryte.toString() << std::endl;
    ASSERT_EQ(0, test_tryte.toInt());

    // test that when we set trits, the value changes correctly 
    test_tryte.setTrit(2, iii::TR_TRUE);
    ASSERT_EQ(9, test_tryte.toInt());

    // Test that we can set Tryte from an int
    iii::Tryte tryte_from_int(5);
    std::cout << "Tryte from int : " << tryte_from_int.toString() << std::endl;
    ASSERT_EQ(5, tryte_from_int.toInt());
}

TEST_F(TestTryte, test_to_int)
{
    iii::Tryte test_tryte;
    std::cout << "Tryte value : " << test_tryte.toString() << std::endl;
    ASSERT_EQ(0, test_tryte.toInt());

    // set each trit in turn and check int converted output
    // First we just shift a trit from LSB to MSB
    for(int t = 0; t < 9; ++t)
    {
        test_tryte.setTrit(t, iii::TR_TRUE);
        ASSERT_EQ(iii::pow3_lut[t], test_tryte.toInt());
        test_tryte.setTrit(t, iii::TR_UNK);
    }
}


// Logic operators 
TEST_F(TestTryte, test_eq)
{
    iii::Tryte a_tryte, b_tryte;;
    ASSERT_EQ(0, a_tryte.toInt());
    ASSERT_EQ(0, b_tryte.toInt());


}

TEST_F(TestTryte, test_neq)
{
    iii::Tryte a_tryte, b_tryte;;
    ASSERT_EQ(0, a_tryte.toInt());
    ASSERT_EQ(0, b_tryte.toInt());
}


// Arithmetic operators 





int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
