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

struct Tryte
{
    Trit trits[9];
    Trit carry;

    public:
        Tryte();
        Tryte(const Tryte& that);

        // logic operators

        // arithmetic operators
        
        // other operators 
        const Trit& operator[](const int i) const;
        Trit& operator[](const int i);

        int toInt(void);
        int nonaryhex(void);
        std::string toString(void);
};


}       // namespace iii

#endif /*__TRYTE_HPP*/
