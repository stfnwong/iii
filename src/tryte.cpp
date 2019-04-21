/*
 * TRYTE
 * Tryte implementation
 *
 * Stefan Wong 2019
 */

#include <sstream>
#include <iomanip>
#include "tryte.hpp"

namespace iii
{

Tryte::Tryte()
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = iii::TR_UNK;
    this->carry = iii::TR_UNK;
}

Tryte::Tryte(const Tryte& that)
{
    for(int t = 0; t < 9; ++t)
        this->trits[t] = that.trits[t];
    this->carry = that.carry;
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

int Tryte::toInt(void)
{
    int tryte_val = 0;
    for(int t = 0; t < 9; ++t)
        tryte_val += this->trits[t].toInt();
    return tryte_val;
}

int Tryte::nonaryhex(void)
{
    int shift_dist = 0;
    int rval = 0;
    for(int t = 0; t < 9; t+=2)
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
    s << std::hex << std::setw(5) << this->nonaryhex();
    return s.str();
}

} // namespace iii
