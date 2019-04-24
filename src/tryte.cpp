/*
 * TRYTE
 * Tryte implementation
 *
 * Stefan Wong 2019
 */

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include "tryte.hpp"

namespace iii
{

// ctors 
Tryte::Tryte()
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = iii::TR_FALSE;
    this->carry = iii::TR_FALSE;
}

Tryte::Tryte(const int v)
{
    if(v == 0)
    {
        for(int i = 0; i < 9; ++i)
            this->trits[i] = iii::TR_FALSE;
        this->carry = iii::TR_FALSE;
    }
    else
    {
        this->fromInt(v);
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

}

Tryte& Tryte::operator=(const Tryte& t)
{
    for(int i = 0; i < 9; ++i)
        this->trits[i] = t[i];
    this->carry = t.getCarry();
    return *this;
}


// Logic operators 
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

// Arithmetic operators

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

// setters  
void Tryte::setTrit(const int trit, const Trit& t)
{
    this->trits[trit] = t;
}



// TODO: debug methods - remove these
void Tryte::printTrits(void)
{
    for(int i = 0; i < 9; ++i)
        std::cout << "|" << std::setw(1) << i << "|";
    std::cout << std::endl;
    for(int i = 0; i < 9; ++i)
        std::cout << " " << std::setw(1) << this->trits[i].toInt() << " ";
    std::cout << std::endl;
}

// type conversions
void Tryte::fromInt(const int v)
{
    // init all trits to false
    for(int i = 0; i < 9; ++i)
        this->trits[i] = iii::TR_FALSE;

    // deal with carry
    //if(v > (iii::pow3_lut[8] / 2))
    //    this->carry = iii::TR_TRUE;
    //else if(v < (-iii::pow3_lut[8] / 2))
    //    this->carry = iii::TR_UNK;
    //else
    //    this->carry = iii::TR_FALSE;

    //int value = v;
    //int tidx = 0;
    //int cur_t = 0;

    //while(value > 0)
    //{
    //    cur_t = value % 3;
    //    std::cout << "[" << __func__ << "] tidx : " << tidx<< " cur_t : " << cur_t << std::endl;
    //    switch(cur_t)
    //    {
    //        case 0:
    //            this->trits[tidx] = iii::Trit(iii::TR_FALSE);
    //            break;
    //        case 1:
    //            this->trits[tidx] = iii::Trit(iii::TR_UNK);
    //            break;
    //        case 2:
    //            this->trits[tidx] = iii::Trit(iii::TR_TRUE);
    //    }
    //    value = value / 3;
    //    tidx++;
    //}
    
    // debug - remove 
    //for(int i = 9; i > 0; --i)
    //    std::cout << this->trits[i].toString();
    //std::cout << std::endl;

}


int Tryte::toInt(void)
{
    int tryte_val = 0;

    this->printTrits();
    //for(int t = 9; t > 0; --t)
    for(int t = 0; t < 9; ++t)
    {
        //std::cout << "[" << t << "] " << "(" << iii::inv_pow3_lut[t] << ") " << this->trits[t].toInt() << " ";
        tryte_val += (this->trits[t].toInt()) * iii::inv_pow3_lut[t];
        //std::cout << tryte_val << std::endl;
    }
    return tryte_val;
}

int Tryte::nonaryhex(void)
{
    int shift_dist = 0;
    int rval = 0;
    for(int t = 9; t > 0; t-=2)
    {
        char tchar = (*this)[t+1].toInt() + (this)[t].toInt() * 3;
        switch(tchar)
        {
            case -4:
                rval += 0xd << (shift_dist * 8);
                break;
            case -3:
                rval += 0xc << (shift_dist * 8);
                break;
            case -2:
                rval += 0xb << (shift_dist * 8);
                break;
            case -1:
                rval += 0xa << (shift_dist * 8);
                break;
            case 0:
                rval += 0x0 << (shift_dist * 8);
                break;
            case 1:
                rval += 0x1 << (shift_dist * 8);
                break;
            case 2:
                rval += 0x2 << (shift_dist * 8);
                break;
            case 3:
                rval += 0x3 << (shift_dist * 8);
                break;
            case 4:
                rval += 0x4 << (shift_dist * 8);
                break;
        }
        shift_dist++;
    }

    return rval;
}

std::string Tryte::toString(void)
{
    std::stringstream s;
    //s << std::hex << std::setw(5) << this->nonaryhex();
    s << std::hex << std::setw(5) << this->toInt();
    return s.str();
}

} // namespace iii
