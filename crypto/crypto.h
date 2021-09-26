#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <string>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>

class HashAlgorithm {
    HashAlgorithm();
    std::string sha2_256(const std::string& message);
    std::string sha2_384(const std::string& message);
    std::string sha3_256(const std::string& message);
    std::string sha3_384(const std::string& message);
    ~HashAlgorithm();
};

class SignatureAlgorithm {
    public:
        SignatureAlgorithm();
        const BIGNUM* generatePrivateKey(const std::string SignatureAlgorithmName);
        ~SignatureAlgorithm();
};

#endif