/*
 * TRYTE
 * Tryte implementation. 
 *
 * Stefan Wong 2019
 */

#ifndef __TRYTE_HPP
#define __TRYTE_HPP

#include <string>
#include "trit.hpp"

namespace iii
{

// powers of 3               0  1  2  3   4   5    6    7     8 
static int pow3_lut[]     = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};
// powers of 3               8     7     6    5    4   3   2  1  0
static int inv_pow3_lut[] = {6561, 2187, 729, 243, 81, 27, 9, 3, 1};


class Tryte
{
    // TODO : it would be simpler to implement this as big-endian, 
    // so that index 0 of this array would become the LSB, and index 8
    // would become the MSB. In HDL, we can do 9 downto 0 or [8:0] for
    // words to create little-endian trytes, but I don't know that its 
    // worth the hassle of emulation that here.
    Trit trits[9];
    Trit carry;

    public:
        Tryte();
        Tryte(const int v);
        Tryte(const Tryte& that);
        ~Tryte();

        // conversions to standard types 

        // assignment operators
        Tryte& operator=(const int v);
        Tryte& operator=(const Tryte& t);

        // logic operators
        Trit operator==(const Tryte& t) const;
        Trit operator!=(const Tryte& t) const;
        Tryte operator&(const Tryte& t) const;
        Tryte operator|(const Tryte& t) const;
        Tryte operator^(const Tryte& t) const;
        Tryte operator~(void) const;

        // arithmetic operators
        Tryte operator+(const Tryte& t) const;
        Tryte operator-(const Tryte& t) const;

        // other operators 
        const Trit& operator[](const int i) const;
        Trit& operator[](const int i);

        // getters 
        Trit getCarry(void) const;
        Trit getTrit(const int trit) const;

        // setters 
        void setTrit(const int trit, const Trit& t);
        

        // debug methods - remove
        void printTrits(void);

        // type conversion
        void fromInt(const int v);
        int toInt(void);
        int nonaryhex(void);
        std::string toString(void);
};


}       // namespace iii

#endif /*__TRYTE_HPP*/
