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

TEST_F(TestTrit, test_init)
{
    // Create a new trit
    iii::Trit test_trit;
    std::cout << "Trit value : " << test_trit.toString() << std::endl;
    ASSERT_EQ(iii::TR_UNK, test_trit.value);

    // test init from symbol
    iii::Trit trit_false('-');
    ASSERT_EQ(iii::TR_FALSE, trit_false.value);
    iii::Trit trit_unk('0');
    ASSERT_EQ(iii::TR_UNK, trit_unk.value);
    iii::Trit trit_true('+');
    ASSERT_EQ(iii::TR_TRUE, trit_true.value);

    // test init from integer
    iii::Trit trit_from_int(1);
    ASSERT_EQ(iii::TR_TRUE, trit_from_int.value);
}

// Equlity operators
TEST_F(TestTrit, test_eq)
{
    iii::Trit a_trit('+');
    iii::Trit b_trit('-');
    bool y;

    y = (a_trit == b_trit);
    ASSERT_EQ(false, y);
}

TEST_F(TestTrit, test_neq)
{
    iii::Trit a_trit('+');
    iii::Trit b_trit('-');
    bool y;

    y = (a_trit != b_trit);
    ASSERT_EQ(true, y);
}

// Logic operators 
TEST_F(TestTrit, test_and)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('-'), iii::Trit('-'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "AND operator test" << std::endl;
    std::cout << "A | B | Y = A & B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] & this->b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_or)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('+'), iii::Trit('+'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('0'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "OR  operator test" << std::endl;
    std::cout << "A | B | Y = A | B" << std::endl;
    for(unsigned int t = 0; t < a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] | this->b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

//TEST_F(TestTrit, test_inline_or)
//{
//
//}

TEST_F(TestTrit, test_xor)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('-'), iii::Trit('0'), iii::Trit('+'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('0'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "OR  operator test" << std::endl;
    std::cout << "A | B | Y = A ^ B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] ^ this->b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_not)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('-'), iii::Trit('0'), iii::Trit('+'), 
        iii::Trit('-'), iii::Trit('0'), iii::Trit('+'), 
        iii::Trit('-'), iii::Trit('0'), iii::Trit('+')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "NOT  operator test" << std::endl;
    std::cout << "A | Y = !A " << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = !this->a_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_cons)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('0'), iii::Trit('0'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('0'), 
        iii::Trit('0'), iii::Trit('0'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "CONS  operator test" << std::endl;
    std::cout << "A | B | Y = A (cons) B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t].cons(this->b_trits[t]);
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

// Arithmetic operators
TEST_F(TestTrit, test_add)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('-'), iii::Trit('+'), iii::Trit('0'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('-'), iii::Trit('+')
    };
    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "+  operator test" << std::endl;
    std::cout << "A | B | Y = A + B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] + this->b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_add_int)
{
    std::vector<int> b_ints = { 1,  1,  1,
                                0,  0,  0,
                               -1, -1, -1
    };
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('-'), iii::Trit('+'), iii::Trit('0'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('-'), iii::Trit('+')
    };
    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "+  operator test" << std::endl;
    std::cout << "A | B | Y = A + B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] + b_ints[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << iii::Trit(b_ints[t]).toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}


TEST_F(TestTrit, test_sub)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('0'), iii::Trit('-'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('+'), iii::Trit('0')
    };
    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "-  operator test" << std::endl;
    std::cout << "A | B | Y = A - B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] - this->b_trits[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}

TEST_F(TestTrit, test_sub_int)
{
    std::vector<int> b_ints = { 1,  1,  1,
                                0,  0,  0,
                               -1, -1, -1
    };
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('0'), iii::Trit('-'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('+'), iii::Trit('0')
    };
    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "-  operator test" << std::endl;
    std::cout << "A | B | Y = A - B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t] - b_ints[t];
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << iii::Trit(b_ints[t]).toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}


TEST_F(TestTrit, test_accept)
{
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('+'), iii::Trit('+'), iii::Trit('0'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('0'), iii::Trit('-'), iii::Trit('-')
    };

    std::vector<iii::Trit> output_y_trits;

    iii::Trit y_trit;
    std::cout << "ACCEPT  operator test" << std::endl;
    std::cout << "A | B | Y = A (accept) B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t].accept(this->b_trits[t]);
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}


TEST_F(TestTrit, test_comp)
{    
    std::vector<iii::Trit> expected_y_trits = {
        iii::Trit('0'), iii::Trit('-'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('0'), iii::Trit('-'), 
        iii::Trit('+'), iii::Trit('+'), iii::Trit('0')
    };

    iii::Trit y_trit;
    std::cout << "COMP  operator test" << std::endl;
    std::cout << "A | B | Y = A (comp) B" << std::endl;
    for(unsigned int t = 0; t < this->a_trits.size(); ++t)
    {
        y_trit = this->a_trits[t].comp(this->b_trits[t]);
        ASSERT_EQ(expected_y_trits[t], y_trit);
        std::cout << this->a_trits[t].toString() << " | " 
                  << this->b_trits[t].toString() << " | " 
                  << y_trit.toString() << std::endl;
    }
    std::cout << std::endl;
}


// comparison operators 
TEST_F(TestTrit, test_lt)
{
    iii::Trit trit_minus('-');
    iii::Trit trit_plus('+');
    iii::Trit trit_zero('0');

    ASSERT_EQ(true, trit_minus < trit_plus);
    ASSERT_EQ(false, trit_plus < trit_minus);
    ASSERT_EQ(true, trit_zero < trit_plus);
    ASSERT_EQ(false, trit_zero < trit_minus);
}

TEST_F(TestTrit, test_gt)
{
    iii::Trit trit_minus('-');
    iii::Trit trit_plus('+');
    iii::Trit trit_zero('0');

    ASSERT_EQ(true, trit_plus > trit_minus);
    ASSERT_EQ(false, trit_minus > trit_minus);
}

TEST_F(TestTrit, test_lte)
{
    iii::Trit trit_minus('-');
    iii::Trit trit_plus('+');
    iii::Trit trit_zero('0');

    ASSERT_EQ(true, trit_minus <= trit_plus);
    ASSERT_EQ(false, trit_minus >= trit_plus);
    ASSERT_EQ(true, trit_minus <= trit_zero);
    ASSERT_EQ(false, trit_zero <= trit_minus);
}



// Integer conversion
TEST_F(TestTrit, test_to_int)
{
    iii::Trit test_trit;
    ASSERT_EQ(iii::TR_UNK, test_trit.value);
    ASSERT_EQ(0, test_trit.toInt());
    test_trit = iii::TR_TRUE;
    ASSERT_EQ(1, test_trit.toInt());
    test_trit = iii::TR_FALSE;
    ASSERT_EQ(-1, test_trit.toInt());
}

TEST_F(TestTrit, test_from_int)
{
    iii::Trit test_trit;
    ASSERT_EQ(0, test_trit.toInt());

    int rhs = 0;
    test_trit = rhs;
    ASSERT_EQ(iii::TR_UNK, test_trit.value);
    ASSERT_EQ(0, test_trit.toInt());

    rhs = 1;
    test_trit = rhs;
    ASSERT_EQ(iii::TR_TRUE, test_trit.value);
    ASSERT_EQ(1, test_trit.toInt());

    // values > 1 illegal, and will be converted to 0
    for(int rhs = 2; rhs < 10; ++rhs)
    {
        test_trit = rhs;
        ASSERT_EQ(iii::TR_UNK, test_trit.value);
        ASSERT_EQ(0, test_trit.toInt());
    }
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
