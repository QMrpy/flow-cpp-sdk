#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/ecdsa.h>

class HashAlgorithm {
    public:
        HashAlgorithm();
        std::string sha2_256(const std::string& message);
        std::string sha2_384(const std::string& message);
        std::string sha3_256(const std::string& message);
        std::string sha3_384(const std::string& message);
        std::string compute_hash(const EVP_MD* algorithm, uint32_t digest_length, const std::string& message);
        ~HashAlgorithm();

    private:
        std::string string_from_raw_bytes(const std::vector<uint8_t>& bytes);
};

class SignatureAlgorithm {
    public:
        SignatureAlgorithm();
        const BIGNUM* generatePrivateKey(const std::string signature_algorithm);
        ~SignatureAlgorithm();
};

#endif