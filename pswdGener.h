//
// Created by recolic on 21/01/17.
//

#ifndef PSWDGEN_PSWDGENER_H
#define PSWDGEN_PSWDGENER_H

#include "picosha2.h"
#include "plusaes.hpp"
#include "stdafx.h"
using std::string;

class pswdGener
{
public:
    string operator()(const string &seed, const string &domain) const
    {
        //Enhash seed for encrypt.
        string hashed_seed;
        picosha2::hash256_hex_string(seed, hashed_seed);
        DEBUG_PRINT(hashed_seed.c_str());
        //AES encrypt by hashed_seed.
        string dataToEncrypt = string("RecolicEncrypt") + domain + "End";
        while(dataToEncrypt.size() % 16 != 0)
            dataToEncrypt += '0';
        std::shared_ptr<unsigned char> pEncrypedData(new unsigned char[dataToEncrypt.size()]{});
        plusaes::Error aes_error = plusaes::encrypt_ecb(reinterpret_cast<const unsigned char *>(dataToEncrypt.c_str()), dataToEncrypt.size(),
                                                        reinterpret_cast<const unsigned char *>(hashed_seed.c_str()), hashed_seed.size(),
                                                        pEncrypedData.get(), dataToEncrypt.size(), false);
        if(aes_error != plusaes::ERROR_OK)
        {
            switch(aes_error)
            {
                case plusaes::ERROR_INVALID_BUFFER_SIZE:
                    throw std::runtime_error("Invalid Buffersize");
                case plusaes::ERROR_INVALID_DATA_SIZE:
                    throw std::invalid_argument("Invalid dataSize");
                case plusaes::ERROR_INVALID_KEY_SIZE:
                    throw std::invalid_argument("Invalid keySize");
                default:
                    throw std::logic_error("At pswdGener.h, line 40, unknown error.");
            }
        }
        return string(reinterpret_cast<const char *>(pEncrypedData.get()));
    }
};


#endif //PSWDGEN_PSWDGENER_H
