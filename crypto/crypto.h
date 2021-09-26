#include <iostream>
#include <string>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>

class HashAlgorithm {
    HashAlgorithm();
    std::string sha2_256(std::string& message);
    std::string sha2_384(std::string& message);
    std::string sha3_256(std::string& message);
    std::string sha3_384(std::string& message);
    ~HashAlgorithm();
};

class SignatureAlgorithm {
    public:
        SignatureAlgorithm();
        const BIGNUM* generatePrivateKey(std::string SignatureAlgorithmName);
        ~SignatureAlgorithm();
};