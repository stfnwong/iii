/* TEST_ARITHMETIC 
 * Test arithmetical functions with Tryte objects
 *
 * Stefan Wong 2019
 */

#include <iostream> 
#include <iomanip>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "tryte.hpp"


class TestArithmetic : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown() {}

    public:
        std::vector<iii::Trit> a_trits = {
            iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
            iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
            iii::Trit('+'), iii::Trit('0'), iii::Trit('-')
        };

        std::vector<iii::Trit> b_trits = {
            iii::Trit('+'), iii::Trit('+'), iii::Trit('+'), 
            iii::Trit('0'), iii::Trit('0'), iii::Trit('0'), 
            iii::Trit('-'), iii::Trit('-'), iii::Trit('-')
        };
};


TEST_F(TestArithmetic, test_expr)
{
    // Create a new tryte
    iii::Tryte tryte_a, tryte_b, tryte_c;
    iii::Trit result, expected_result;

    ASSERT_EQ(0, tryte_a.toInt());
    ASSERT_EQ(0, tryte_b.toInt());
    ASSERT_EQ(0, tryte_c.toInt());

    tryte_a = 64;
    tryte_b = 3;

    tryte_c = 64 + 3;
    ASSERT_EQ(64 + 3, tryte_c.toInt());
    result = (tryte_c == (tryte_a + tryte_b));
    expected_result = iii::TR_TRUE;
    ASSERT_EQ(expected_result, result);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
