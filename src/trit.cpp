/*
 * TRIT
 * A ternary unit
 *
 * Stefan Wong 2019
 */

#include <iostream>
#include "trit.hpp"

namespace iii 
{

/*
 * For all the below comparison LUTs, the arrangement assumes 
 *           B
 *       -   0   +
 *    +------------
 *   -|  i0, i1, i2,
 * A 0|  i3, i4, i5,
 *   +|  i6, i7, i8
 * 
 * That is, the LUT is flattened version of the above array, and 
 * elements are accessed using 
 *
 * Y = 3A + B
 */

const char* tritval_str = "E-0+";
TritVal trit_add_lut[]  = {TR_TRUE,  TR_FALSE, TR_UNK, 
                           TR_FALSE, TR_UNK,   TR_TRUE,
                           TR_UNK,   TR_TRUE,  TR_FALSE
};

TritVal trit_sub_lut[]  = {TR_UNK,   TR_FALSE, TR_FALSE, 
                           TR_TRUE,  TR_UNK,   TR_FALSE,
                           TR_TRUE,  TR_TRUE,  TR_UNK
};
 
TritVal trit_comp_lut[] = {TR_UNK  , TR_FALSE, TR_FALSE,
                           TR_TRUE , TR_UNK,   TR_FALSE,
                           TR_TRUE , TR_TRUE , TR_UNK
};


TritVal trit_comp_zero_lut[] = {TR_FALSE, TR_FALSE, TR_TRUE,
                                TR_FALSE, TR_UNK,   TR_TRUE,
                                TR_FALSE, TR_TRUE,  TR_TRUE
};

// --- constructors ---- //
Trit::Trit()
{
    this->value = iii::TR_UNK;
}

Trit::Trit(const char c)
{
    switch(c)
    {
        case '-':
            this->value = iii::TR_FALSE;
            break;
        case '0':
            this->value = iii::TR_UNK;
            break;
        case '+':
            this->value = iii::TR_TRUE;
            break;
        default:
            this->value = iii::TR_UNK;
            break;
    }
}

Trit::Trit(const int i)
{
    switch(i)
    {
        case iii::TR_FALSE:
            this->value = iii::TR_FALSE;
            break;
        case iii::TR_UNK:
            this->value = iii::TR_UNK;
            break;
        case iii::TR_TRUE:
            this->value = iii::TR_TRUE;
            break;
        default:
            this->value = iii::TR_UNK;
    }
}

Trit::Trit(const TritVal& t)
{
    this->value = t;
}

Trit::Trit(const Trit& that)
{
    this->value = that.value;
}

/*
 * logic operators
 */

/* 
 * AND (Min)
 * Truth table :
 * A | B | Y = A & B
 * + | + | +
 * 0 | + | 0
 * - | + | -
 * + | 0 | 0
 * 0 | 0 | 0
 * - | 0 | -
 * + | - | -
 * 0 | - | -
 * - | - | -
 *
 */
Trit Trit::operator&(const Trit& t) const
{
    if(this->value == iii::TR_TRUE && t.value == iii::TR_TRUE)
        return Trit(iii::TR_TRUE);
    if(this->value == iii::TR_FALSE || t.value == iii::TR_FALSE)
        return Trit(iii::TR_FALSE);
    return Trit(iii::TR_UNK);
}

/* 
 * OR (Max)
 * Truth table :
 * A | B | Y = A | B
 * + | + | +
 * 0 | + | +
 * - | + | +
 * + | 0 | +
 * 0 | 0 | 0
 * - | 0 | 0
 * + | - | +
 * 0 | - | 0
 * - | - | -
 *
 */
Trit Trit::operator|(const Trit& t) const
{
    if(this->value == iii::TR_TRUE || t.value == iii::TR_TRUE)
        return Trit(iii::TR_TRUE);
    if(this->value == iii::TR_UNK || t.value == iii::TR_UNK)
        return Trit(iii::TR_UNK);
    return Trit(iii::TR_FALSE);
}

//Trit& Trit::operator|=(const Trit& t)
//{
//    this->value = (*this | t).value;
//    return *this;
//}

/* 
 * XOR 
 * Truth table :
 * A | B | Y = A ^ B
 * + | + | -
 * 0 | + | 0
 * - | + | +
 * + | 0 | 0
 * 0 | 0 | 0
 * - | 0 | 0
 * + | - | +
 * 0 | - | 0
 * - | - | -
 *
 */
Trit Trit::operator^(const Trit& t) const
{
    if(this->value == iii::TR_UNK || t.value == iii::TR_UNK)
        return Trit(iii::TR_UNK);
    if(this->value == t.value)
        return Trit(iii::TR_FALSE);
    return Trit(iii::TR_TRUE);
}

/* 
 * NOT 
 * Truth table :
 * A | Y = !A
 * + | -
 * 0 | 0
 * - | +
 *
 */
Trit Trit::operator!(void) const
{
    switch(this->value)
    {
        case iii::TR_FALSE:
            return Trit(iii::TR_TRUE);
        case iii::TR_UNK:
            return Trit(iii::TR_UNK);
        case iii::TR_TRUE:
            return Trit(iii::TR_FALSE);
        default:
            return Trit(iii::TR_UNK);
    }
}


/* 
 * arithmetic operators 
 */
Trit Trit::operator+(const Trit& t) const
{
    return Trit(trit_add_lut[3 * (this->toInt()+1) + (t.toInt()+1)]);
}

Trit Trit::operator+(const int v) const
{
    switch(v)
    {
        case iii::TR_FALSE:
            return Trit(trit_add_lut[3 * (this->toInt() + 1)]);
            break;
        case iii::TR_UNK:
            return Trit(trit_add_lut[3 * (this->toInt() + 1) + 1]);
            break;
        case iii::TR_TRUE:
            return Trit(trit_add_lut[3 * (this->toInt() + 1) + 2]);
            break;
        default:        // this is technically an error...
            return Trit(this->value);
            break;
    }
}

Trit Trit::operator-(const Trit& t) const
{
    return Trit(trit_sub_lut[3 * (this->toInt()+1) + (t.toInt()+1)]);
}

Trit Trit::operator-(const int v) const
{
    switch(v)
    {
        case iii::TR_FALSE:
            return Trit(trit_sub_lut[3 * (this->toInt() + 1)]);
            break;
        case iii::TR_UNK:
            return Trit(trit_sub_lut[3 * (this->toInt() + 1) + 1]);
            break;
        case iii::TR_TRUE:
            return Trit(trit_sub_lut[3 * (this->toInt() + 1) + 2]);
            break;
        default:        // this is technically an error...
            return Trit(this->value);
            break;
    }
}

/*
 * equality operators
 */
bool Trit::operator==(const Trit& t) const
{
    if(this->value == t.value)
        return true;
    return false;
}

bool Trit::operator!=(const Trit& t) const
{
    if(this->value == t.value)
        return false;
    return true;
}


/*
 * comparison operators
 */
bool Trit::operator>(const Trit& t) const
{
    return (trit_comp_lut[3 * (this->toInt() + 1) + (t.toInt() + 1)] == iii::TR_TRUE) ? true : false;
}

bool Trit::operator<(const Trit& t) const
{
    return (trit_comp_lut[3 * (this->toInt() + 1) + (t.toInt() + 1)] == iii::TR_FALSE) ? true : false;
}

bool Trit::operator>=(const Trit& t) const
{
    if((trit_comp_lut[3 * (this->toInt()+1) + (t.toInt()+1)] == iii::TR_TRUE) ||
        trit_comp_lut[3 * (this->toInt()+1) + (t.toInt()+1)] == iii::TR_UNK)
        return true;
    return false;
}

bool Trit::operator<=(const Trit& t) const
{
    if((trit_comp_lut[3 * (this->toInt()+1) + (t.toInt()+1)] == iii::TR_FALSE) ||
        trit_comp_lut[3 * (this->toInt()+1) + (t.toInt()+1)] == iii::TR_UNK)
        return true;
    return false;
}

/*
 * asssignment operators
 */
Trit& Trit::operator=(const TritVal& t)
{
    this->value = t;
    return *this;
}

Trit& Trit::operator=(const Trit& t)
{
    this->value = t.value;
    return *this;
}

Trit& Trit::operator=(const int v)
{
    switch(v)
    {
        case -1:
            this->value = iii::TR_FALSE;
            break;
        case 0:
            this->value = iii::TR_UNK;
            break;
        case 1:
            this->value = iii::TR_TRUE;
            break;
        default:
            this->value = iii::TR_UNK;
            break;
    }
    return *this;
}

// consensus
/* 
 * CONS 
 * Truth table :
 * A | B | Y = A (cons) B
 * + | + | +
 * 0 | + | 0
 * - | + | 0
 * + | 0 | 0
 * 0 | 0 | 0
 * - | 0 | 0
 * + | - | 0
 * 0 | - | 0
 * - | - | -
 *
 */
Trit Trit::cons(const Trit& t)
{
    if(this->value == iii::TR_TRUE && t.value == iii::TR_TRUE)
        return Trit(iii::TR_TRUE);
    if(this->value == iii::TR_FALSE && t.value == iii::TR_FALSE)
        return Trit(iii::TR_FALSE);

    return Trit(iii::TR_UNK);
}

// any/accept 
/* 
 * ANY 
 * Truth table :
 * A | B | Y = A (any) B
 * + | + | +
 * 0 | + | +
 * - | + | 0
 * + | 0 | +
 * 0 | 0 | 0
 * - | 0 | -
 * + | - | 0
 * 0 | - | -
 * - | - | -
 *
 */
Trit Trit::accept(const Trit& t)
{
    if((this->value == iii::TR_TRUE && t.value == iii::TR_FALSE) ||
       (this->value == iii::TR_FALSE && t.value == iii::TR_TRUE))
        return Trit(iii::TR_UNK);
    if(this->value == iii::TR_TRUE || t.value == iii::TR_TRUE)
        return Trit(iii::TR_TRUE);
    if(this->value == iii::TR_FALSE || t.value == iii::TR_FALSE)
        return Trit(iii::TR_FALSE);
    
    return Trit(iii::TR_UNK);
}

Trit Trit::comp(const Trit& t)
{
    return Trit(trit_comp_lut[3 * (this->toInt() + 1) + (t.toInt() + 1)]);
}

Trit Trit::compZero(const Trit& t)
{
    return Trit(trit_comp_zero_lut[3 * (this->toInt() + 1) + (t.toInt() + 1)]);
}

// intify
int Trit::toInt(void) const
{
    return (int) this->value;
}

// stringify
std::string Trit::toString(void) 
{
   std::string s(1, tritval_str[this->value+2]);
   return s;
}

} // namespace iii
