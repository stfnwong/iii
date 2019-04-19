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

    iii::Trit trit_false('-');
    ASSERT_EQ(iii::TR_FALSE, trit_false.value);
    iii::Trit trit_unk('0');
    ASSERT_EQ(iii::TR_UNK, trit_unk.value);
    iii::Trit trit_true('+');
    ASSERT_EQ(iii::TR_TRUE, trit_true.value);
}

// Logic operators 
TEST_F(TestTrit, test_and)
{
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

    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('-'), iii::Trit('-'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "AND operator test" << std::endl;
    std::cout << "A | B | Y = A & B" << std::endl;
    for(unsigned int t = 0; t < a_trits.size(); ++t)
    {
        y_trit = a_trits[t] & b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << a_trits[t].toString() << " | " 
                  << b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_or)
{
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

    // TODO : update 
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('-'), iii::Trit('-'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "OR  operator test" << std::endl;
    std::cout << "A | B | Y = A | B" << std::endl;
    for(unsigned int t = 0; t < a_trits.size(); ++t)
    {
        y_trit = a_trits[t] & b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << a_trits[t].toString() << " | " 
                  << b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

