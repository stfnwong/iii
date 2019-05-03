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
    ASSERT_EQ(0, test_tryte.toInt());

    // set each trit in turn and check int converted output
    // First we just shift a trit from LSB to MSB
    for(int t = 0; t < 8; ++t)
    {
        test_tryte.setTrit(t, iii::TR_TRUE);
        ASSERT_EQ(iii::pow3_lut[t], test_tryte.toInt());
        test_tryte.setTrit(t, iii::TR_UNK);
    }
}

TEST_F(TestTryte, test_from_int)
{
    // ctor from int
    iii::Tryte test_tryte(15);
    ASSERT_EQ(15, test_tryte.toInt());

    // now test that we can assign from int on rhs
    test_tryte = 64;
    ASSERT_EQ(64, test_tryte.toInt());
    // NOTE : be careful here about the correct endianness of the expected values.
    // The [0] position trit is the least significant. Therefore we need to order
    // the values in the array in big-endian order so that the iteration proceeds 
    // correctly.
    std::vector<int> expected_trits = {1, 0, 1, -1, 1};

    for(unsigned int t = 0; t < expected_trits.size(); ++t)
        ASSERT_EQ(expected_trits[t], test_tryte[t].toInt());

    // Try an signed int
    iii::Tryte signed_tryte(-8);
    ASSERT_EQ(-8, signed_tryte.toInt());
    signed_tryte = -128;
    ASSERT_EQ(-128, signed_tryte.toInt());

    // Try a whole lot of ints
    iii::Tryte range_tryte;
    for(int n = 0; n < 500; ++n)
    {
        range_tryte = n;
        ASSERT_EQ(n, range_tryte.toInt());
    }

    // Try a whole lot of signed ints
    for(int n = 0; n > -500; --n)
    {
        range_tryte = n;
        ASSERT_EQ(n, range_tryte.toInt());
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
    iii::Trit trit_eq;

    a_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(3, iii::TR_TRUE);

    expected_tryte.setTrit(1, iii::TR_TRUE);
    y_tryte = a_tryte & b_tryte;

    trit_eq = (expected_tryte == y_tryte);
    ASSERT_EQ(iii::TR_TRUE, trit_eq.value);

    a_tryte.allClear();
    b_tryte.allClear();
    expected_tryte.allClear();

    a_tryte.setTrit(2, iii::TR_TRUE);
    b_tryte.setTrit(3, iii::TR_TRUE);

    y_tryte = a_tryte & b_tryte;
    trit_eq = (expected_tryte == y_tryte);
    ASSERT_EQ(iii::TR_TRUE, trit_eq.value);
}

TEST_F(TestTryte, test_bitwise_or)
{
    iii::Tryte a_tryte, b_tryte, y_tryte;
    iii::Tryte expected_tryte;
    iii::Trit trit_eq;

    a_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(1, iii::TR_TRUE);
    b_tryte.setTrit(3, iii::TR_TRUE);

    expected_tryte.setTrit(1, iii::TR_TRUE);
    expected_tryte.setTrit(3, iii::TR_TRUE);
    y_tryte = a_tryte | b_tryte;

    trit_eq = (expected_tryte == y_tryte);
    ASSERT_EQ(iii::TR_TRUE, trit_eq.value);

    a_tryte.allClear();
    b_tryte.allClear();
    expected_tryte.allClear();

    a_tryte.setTrit(2, iii::TR_TRUE);
    b_tryte.setTrit(3, iii::TR_TRUE);
    expected_tryte.setTrit(2, iii::TR_TRUE);
    expected_tryte.setTrit(3, iii::TR_TRUE);

    y_tryte = a_tryte | b_tryte;
    trit_eq = (expected_tryte == y_tryte);
    ASSERT_EQ(iii::TR_TRUE, trit_eq.value);
}

TEST_F(TestTryte, test_bitwise_not)
{
    iii::Tryte a_tryte, y_tryte;
    iii::Tryte expected_tryte;
    iii::Trit trit_eq;

    a_tryte.setTrit(0, iii::TR_TRUE);
    a_tryte.setTrit(1, iii::TR_TRUE);

    for(int t = 0; t < 9; ++t)
    {
        if(t < 2)
            expected_tryte.setTrit(t, iii::TR_FALSE);
        else
            expected_tryte.setTrit(t, iii::TR_UNK);
    }
    // perform not
    y_tryte = ~a_tryte;

    trit_eq = (expected_tryte == y_tryte);
    ASSERT_EQ(iii::TR_TRUE, trit_eq.value);
}

// Arithmetic operators 
TEST_F(TestTryte, test_add)
{
    iii::Tryte a_tryte, b_tryte, y_tryte;
    iii::Tryte expected_tryte;

    a_tryte = 1;
    b_tryte = 1;
    expected_tryte = 2;
    y_tryte = a_tryte + b_tryte;
    ASSERT_EQ(expected_tryte.toInt(), y_tryte.toInt());

    a_tryte = 8;
    b_tryte = 4;
    expected_tryte = (8 + 4);
    y_tryte = a_tryte + b_tryte;
    ASSERT_EQ(expected_tryte.toInt(), y_tryte.toInt());

    // Add lots of numbers, start with positive integers
    for(int n = 0; n < 500; ++n)
    {
        a_tryte = n;
        b_tryte = n;
        expected_tryte = n + n;
        std::cout << a_tryte.toInt() << " + " << b_tryte.toInt() << std::endl;
        y_tryte = a_tryte + b_tryte;
        ASSERT_EQ(expected_tryte.toInt(), y_tryte.toInt());
    }

    // Add lots of negative integers
    for(int n = 0; n > -500; --n)
    {
        a_tryte = n;
        b_tryte = n;
        expected_tryte = n + n;
        std::cout << a_tryte.toInt() << " + " << b_tryte.toInt() << std::endl;
        y_tryte = a_tryte + b_tryte;
        ASSERT_EQ(expected_tryte.toInt(), y_tryte.toInt());
    }

    //a_tryte = 64;
    //b_tryte = 64;
    //expected_tryte = 128;
    //y_tryte = a_tryte + b_tryte;
    //ASSERT_EQ(expected_tryte.toInt(), y_tryte.toInt());
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
