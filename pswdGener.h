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
    string operator()(const string &seed, const string &domain, bool stronger = false, size_t length = 0) const
    {
        //Enhash seed for encrypt.
        string hashed_seed, hashed_domain;
        picosha2::hash256_hex_string(seed, hashed_seed);
        picosha2::hash256_hex_string(domain, hashed_domain);
        //AES encrypt by hashed_seed.
        string dataToEncrypt = string("RecolicEncrypt") + hashed_domain + "End";
        while(dataToEncrypt.size() % 16 != 0)
            dataToEncrypt += 'n';
        std::shared_ptr<unsigned char> pEncrypedData(new unsigned char[dataToEncrypt.size()]{});
        plusaes::Error aes_error = plusaes::encrypt_ecb(reinterpret_cast<const unsigned char *>(dataToEncrypt.c_str()), dataToEncrypt.size(),
                                                        reinterpret_cast<const unsigned char *>(hashed_seed.c_str()), 32,
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
        //Encode encrypted string and let it visiable.
        if(stronger)
        {
            char dic[] = "ASDF=GHJ*K_L+#Q!WE=RTY_Uuu426357IOP.Z=XC*VB.:;][[]asqwtynbTNYCO5E00@#NM96_3@-vv#85V27.410+aiqw_.ertyuUUU#opsd=f@ghjklzxm@nb.vcvV";
            string toReturn;
            for(size_t cter = 0; cter < dataToEncrypt.size(); ++cter)
            {
                toReturn += dic[(pEncrypedData.get()[cter]) % 128];
            }
            return length > 0 ? toReturn.substr(0, length) : toReturn;
        }
        else
        {
            char dic[] = "ASDFGHJKLQW61TYUkOPZXCVBNM9638527410aiqwertyuopsdfghjk9zxmnbvcvV";
            string toReturn;
            for (size_t cter = 0; cter < dataToEncrypt.size(); ++cter) {
                toReturn += dic[(pEncrypedData.get()[cter]) % 64];
            }
            return length > 0 ? toReturn.substr(0, length) : toReturn;
        }
    }
};


#endif //PSWDGEN_PSWDGENER_H
