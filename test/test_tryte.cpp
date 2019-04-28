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
    ASSERT_EQ(0, test_tryte.toInt());

    //// Test that we can set Tryte from an int
    iii::Tryte tryte_from_int_zero(0);
    ASSERT_EQ(0, tryte_from_int_zero.toInt());
    iii::Tryte tryte_from_int(15);
    ASSERT_EQ(15, tryte_from_int.toInt());
}


TEST_F(TestTryte, test_to_int)
{
    iii::Tryte test_tryte;
    std::cout << "Tryte value : " << test_tryte.toString() << std::endl;
    ASSERT_EQ(0, test_tryte.toInt());

    // set each trit in turn and check int converted output
    // First we just shift a trit from LSB to MSB
    for(int t = 0; t < 8; ++t)
    {
        test_tryte.setTrit(t, iii::TR_UNK);
        ASSERT_EQ(iii::pow3_lut[t], test_tryte.toInt());
        test_tryte.setTrit(t, iii::TR_FALSE);
    }
}


// Logic operators 
TEST_F(TestTryte, test_eq)
{
    iii::Tryte a_tryte, b_tryte;
    iii::Trit y_trit;

    b_tryte.setTrit(4, iii::TR_TRUE);
    y_trit = (a_tryte == b_tryte);
    ASSERT_EQ(iii::TR_FALSE, y_trit.value);
}

TEST_F(TestTryte, test_neq)
{
    iii::Tryte a_tryte, b_tryte;
    iii::Trit y_trit;

    b_tryte.setTrit(4, iii::TR_TRUE);
    y_trit = (a_tryte != b_tryte);
    ASSERT_EQ(iii::TR_TRUE, y_trit.value);
}

TEST_F(TestTryte, test_bitwise_and)
{
    iii::Tryte a_tryte, b_tryte, y_tryte;
    iii::Tryte expected_tryte;

    a_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(3, iii::TR_TRUE);

    expected_tryte.setTrit(1, iii::TR_TRUE);
    y_tryte = a_tryte & b_tryte;
    //ASSERT_EQ(expected_tryte, y_tryte);
}

TEST_F(TestTryte, test_bitwise_or)
{

}

TEST_F(TestTryte, test_bitwise_not)
{

}

// Arithmetic operators 





int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
