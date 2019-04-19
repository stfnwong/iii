/*
 * TRIT
 * A ternary unit
 * This implements balanced ternary logic
 *
 * Stefan Wong 2019
 */

#ifndef __TRIT_HPP
#define __TRIT_HPP

#include <string>

namespace iii
{

typedef enum {TR_INVALID = -2, TR_FALSE=-1, TR_UNK = 0, TR_TRUE = 1} TritVal;

struct Trit
{
    TritVal value;

    public:
        Trit();
        Trit(const char c);
        Trit(const TritVal& t);
        Trit(const Trit& that);
        ~Trit() {} 

        // arithmetic operators
        Trit operator&(const Trit& t) const;
        Trit operator|(const Trit& t) const;

        // equality operators
        bool operator==(const Trit& t) const;
        
        // assignment operators
        //Trit& operator=(const int val);
        Trit& operator=(const TritVal& t);
        Trit& operator=(const Trit& t);


        // stringify
        std::string toString(void);
};

}   // namespace iii

#endif /*__TRIT_HPP*/
