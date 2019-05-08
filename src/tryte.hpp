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

        // TODO: in-place logic operators?

        // comparison operators
        Trit operator>(const Tryte& t) const;
        Trit operator>=(const Tryte& t) const;
        Trit operator<(const Tryte& t) const;
        Trit operator<=(const Tryte& t) const;

        // arithmetic operators
        Tryte operator+(const Tryte& t); 
        //Tryte operator+(const int v);
        Tryte operator-(const Tryte& t);

        // other operators 
        const Trit& operator[](const int i) const;
        Trit& operator[](const int i);

        // getters 
        Trit getCarry(void) const;
        Trit getTrit(const int trit) const;
        bool eqZero(void) const;

        // setters 
        void setTrit(const int trit, const Trit& t);
        void allClear(void);
        void allSet(void);
        void invert(void);
        
        void printTrits(void);

        // type conversion
        void fromInt(const int v);
        int toInt(void);
        int nonaryhex(void);
        std::string toString(void);
};


}       // namespace iii

#endif /*__TRYTE_HPP*/
