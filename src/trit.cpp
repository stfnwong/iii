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

const char* tritval_str = "U-0+";

// --- constructors ---- //
Trit::Trit()
{
    this->value = iii::TR_UNK;
}

Trit::Trit(const char c)
{
    if(c == '-')
        this->value = iii::TR_FALSE;
    else if(c == '0')
        this->value = iii::TR_UNK;
    else if(c == '+')
        this->value = iii::TR_TRUE;
    else
        this->value = iii::TR_INVALID;
}

Trit::Trit(const TritVal& t)
{
    this->value = t;
}

Trit::Trit(const Trit& that)
{
    this->value = that.value;
}

// arithmetic operators

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

// equality operators 
bool Trit::operator==(const Trit& t) const
{
    if(this->value == t.value)
        return true;
    return false;
}

// assignment operators 
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


std::string Trit::toString(void) 
{
   std::string s(1, tritval_str[this->value+2]);
   return s;
}

} // namespace iii
