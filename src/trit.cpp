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
    //this->value = iii::TR_UNK;
    this->value = iii::TR_FALSE;
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
        this->value = iii::TR_FALSE;
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

// TODO : inline operator needs testing
Trit& Trit::operator&=(const Trit& t)
{
    this->value = (*this & t).value;
    return *this;
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

// TODO : inline operator needs testing
Trit& Trit::operator|=(const Trit& t)
{
    this->value = (*this | t).value;
    return *this;
}

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

// equality operators 
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

//Trit Trit::operator==(const Trit& t) const
//{
//    if(this->value == t.value)
//        return Trit(iii::TR_FALSE);
//    return Trit(iii::TR_TRUE);
//}
//
//Trit Trit::operator!=(const Trit& t) const
//{
//    if(this->value == t.value)
//        return Trit(iii::TR_FALSE);
//    return Trit(iii::TR_TRUE);
//}

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

Trit& Trit::operator=(const int v)
{
    switch(v)
    {
        case 0:
            this->value = iii::TR_FALSE;
            break;
        case 1:
            this->value = iii::TR_UNK;
            break;
        case 2:
            this->value = iii::TR_TRUE;
            break;
        default:
            this->value = iii::TR_FALSE;
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

// intify
int Trit::toInt(void) const
{
    return (int) this->value;
}

// stringify
std::string Trit::toString(void) 
{
   std::string s(1, tritval_str[this->value+1]);
   return s;
}

} // namespace iii
