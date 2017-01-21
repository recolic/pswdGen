//
// Created by recolic on 21/01/17.
//

#ifndef PSWDGEN_PSWDGENER_H
#define PSWDGEN_PSWDGENER_H

#include "picosha2.h"
#include "stdafx.h"
using std::string;

class pswdGener
{
public:
    string operator()(const string &seed, const string &domain) const
    {
        string hashed_seed;
        picosha2::hash256_hex_string(seed, hashed_seed);
        DEBUG_PRINT(hashed_seed.c_str());

    }
};


#endif //PSWDGEN_PSWDGENER_H
