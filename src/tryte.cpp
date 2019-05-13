/*
 * TRYTE
 * Tryte implementation
 *
 * Stefan Wong 2019
 */

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>
#include "tryte.hpp"

namespace iii
{



// ctors 
Tryte::Tryte()
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = iii::TR_UNK;
    this->carry = iii::TR_UNK;
}

Tryte::Tryte(const int v)
{
    if(v != 0)
        this->fromInt(v);
    else
    {
        for(int i = 0; i < 9; ++i)
            this->trits[i] = iii::TR_UNK;
        this->carry = iii::TR_UNK;
    }
}

// copy ctor
Tryte::Tryte(const Tryte& that)
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = that.trits[t];
    this->carry = that.carry;
}

// dtor
Tryte::~Tryte() {} 


// assignment operators 
Tryte& Tryte::operator=(const int v)
{
    this->fromInt(v);
    return *this;
}

Tryte& Tryte::operator=(const Tryte& t)
{
    for(int i = 0; i < 9; ++i)
        this->trits[i] = t[i];
    this->carry = t.getCarry();
    return *this;
}


/*
 * logic operators
 */
Trit Tryte::operator==(const Tryte& t) const
{
    for(int i = 0; i < 9; ++i)
    {
        if(this->trits[i] != t[i])
            return Trit(iii::TR_FALSE);
    }
    return Trit(iii::TR_TRUE);
}

Trit Tryte::operator!=(const Tryte& t) const
{
    for(int i = 0; i < 9; ++i)
    {
        if(this->trits[i] != t[i])
            return Trit(iii::TR_TRUE);
    }
    return Trit(iii::TR_FALSE);
}

Tryte Tryte::operator&(const Tryte& t) const
{
    Tryte tr;
    for(int i = 0; i < 9; ++i)
        tr.setTrit(i, this->trits[i] & t[i]);

    return tr;
}

Tryte Tryte::operator|(const Tryte& t) const
{
    Tryte tr;
    for(int i = 0; i < 9; ++i)
        tr.setTrit(i, this->trits[i] | t[i]);

    return tr;
}

Tryte Tryte::operator^(const Tryte& t) const
{
    Tryte tr;
    for(int i = 0; i < 9; ++i)
        tr.setTrit(i, this->trits[i] ^ t[i]);

    return tr;
}

Tryte Tryte::operator~(void) const
{
    Tryte tr;
    for(int i = 0; i < 9; ++i)
        tr.setTrit(i, !this->trits[i]);

    return tr;
}


Trit Tryte::comp(const Tryte& t)
{
    for(auto i = 9; i > 0; --i)
    {
        if((this->trits[i] != iii::TR_UNK) || (t[i] != iii::TR_UNK))
        {
            return this->trits[i].comp(t[i]);
        }
    }

    return Trit('0');
}

/*
 * Boolean comparison operators
 */
bool Tryte::operator<(const Tryte& t) 
{
    for(auto i = 9; i > 0; --i)
    {
        if((this->trits[i] != iii::TR_UNK) || (t[i] != iii::TR_UNK))
            return (this->trits[i] < t[i]);
    }

    return false;
}

bool Tryte::operator<=(const Tryte& t) const
{
    for(auto i = 9; i > 0; --i)
    {
        if((this->trits[i] != iii::TR_UNK) || (t[i] != iii::TR_UNK))
            return (this->trits[i] <= t[i]);
    }

    return false;
}

bool Tryte::operator>(const Tryte& t) const
{
    for(auto i = 9; i > 0; --i)
    {
        if((this->trits[i] != iii::TR_UNK) || (t[i] != iii::TR_UNK))
            return (this->trits[i] > t[i]);
    }

    return false;
}

bool Tryte::operator>=(const Tryte& t) const
{
    for(auto i = 9; i > 0; --i)
    {
        if((this->trits[i] != iii::TR_UNK) || (t[i] != iii::TR_UNK))
            return (this->trits[i] >= t[i]);
    }

    return false;
}




/*
 * arithmetic operators
 */
Tryte Tryte::operator+(const Tryte& t) 
{
    Tryte tr;
    Trit si;
    Trit ca(0);
    Trit cb(0);
    Trit ci(0);

    for(int i = 0; i < 9; ++i)
    {
        si = (this->trits[i] + t.trits[i]) + ci;
        ca = this->trits[i].cons(t.trits[i]);
        cb = (this->trits[i] + t.trits[i]).cons(ci);
        ci = ca.accept(cb);
        tr.trits[i] = si;
    }

    return tr;
}

Tryte Tryte::operator-(const Tryte& t) 
{
    Tryte tr;
    Trit si;
    Trit ca(0);
    Trit cb(0);
    Trit ci(0);
    
    for(int i = 0; i < 9; ++i)
    {
        si = (this->trits[i] + !t.trits[i]) + ci;
        ca = this->trits[i].cons(!t.trits[i]);
        cb = (this->trits[i] + !t.trits[i]).cons(ci);
        ci = ca.accept(cb);
        tr.trits[i] = si;
    }

    return tr;
}

// other operators
const Trit& Tryte::operator[](const int i) const
{
    return this->trits[i];
}

Trit& Tryte::operator[](const int i)
{
    return this->trits[i];
}

// getters 
Trit Tryte::getCarry(void) const
{
    return this->carry;
}

Trit Tryte::getTrit(const int trit) const
{
    return this->trits[trit];
}

bool Tryte::eqZero(void) const
{
    for(int i = 0; i < 9; ++i)
    {
        if(this->trits[i] != iii::TR_UNK)
            return false;
    }

    return true;
}




// setters  
void Tryte::setTrit(const int trit, const Trit& t)
{
    this->trits[trit] = t;
}

void Tryte::allClear(void)
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = iii::TR_FALSE;
}

void Tryte::allSet(void)
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = iii::TR_TRUE;
}

void Tryte::invert(void)
{
    for(int t = 0; t < 9; t++)
        this->trits[t] = !this->trits[t];
}


void Tryte::printTrits(void)
{
    for(int i = 0; i < 9; ++i)
        std::cout << "|" << std::setw(2) << i;
    std::cout << std::endl;
    for(int i = 0; i < 9; ++i)
        std::cout << " " << std::setw(2) << this->trits[i].toInt();
    std::cout << std::endl;
}

// type conversions
// this only works for unsigned numbers, but one of the 
// supposed advantages of ternary logic is that handling signs is less
// complicated than with binary logics
void Tryte::fromInt(const int v)
{
    // init all trits to false
    for(int i = 0; i < 9; ++i)
        this->trits[i] = iii::TR_UNK;

    // deal with carry
    if(v > (iii::pow3_lut[8] / 2))
        this->carry = iii::TR_TRUE;
    else if(v < (-iii::pow3_lut[8] / 2))
        this->carry = iii::TR_FALSE;
    else
        this->carry = iii::TR_UNK;

    int value = std::abs(v);
    int tidx = 0;
    int cur_t = 0;

    // perform unsigned conversion
    while(value > 0)
    {
        cur_t = value % 3;
        // work out the current lowest digit
        switch(cur_t)
        {
            case 0:
                this->trits[tidx] = iii::Trit(iii::TR_UNK);
                break;
            case 1:
                this->trits[tidx] = iii::Trit(iii::TR_TRUE);
                value -= 1;
                break;
            case 2:
                this->trits[tidx] = iii::Trit(iii::TR_FALSE);
                value += 1;
        }
        value = value / 3;
        tidx++;
    }
    // if the original number was negative, then flip all the trits
    if(v < 0)
    {
        for(int i = 0; i < 9; ++i)
            this->trits[i] = !this->trits[i];
    }
}


int Tryte::toInt(void)
{
    int tryte_val = 0;
    for(int t = 0; t < 9; ++t)
        tryte_val += ((this->trits[t].toInt()) * iii::pow3_lut[t]);

    return tryte_val;
}

std::string Tryte::toString(void)
{
    std::stringstream s;
    s << std::hex << std::setw(5) << this->toInt();
    return s.str();
}

} // namespace iii
