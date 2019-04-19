/*
 * TRIT
 * A ternary unit
 *
 * Stefan Wong 2019
 */

#include "trit.hpp"

namespace iii 
{

const char* tritval_str = "U-0+";

// --- constructors ---- //
Trit::Trit()
{
    this->value = iii::TR_UNK;
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
