#include "crypto.h"

SignatureAlgorithm::SignatureAlgorithm() {}

const BIGNUM* SignatureAlgorithm::generatePrivateKey(std::string SignatureAlgorithmName) {
    EC_KEY *ec_key;
    const BIGNUM* private_key;

    if (SignatureAlgorithmName == "ECDSA_secp256k1") {
        ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
        if (EC_KEY_generate_key(ec_key)) {
            private_key = EC_KEY_get0_private_key(ec_key);
            return private_key;
        } else {
            return nullptr;
        }
    } else if (SignatureAlgorithmName == "ECDSA_P256") {
        ec_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        if (EC_KEY_generate_key(ec_key)) {
            private_key = EC_KEY_get0_private_key(ec_key);
            return private_key;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

SignatureAlgorithm::~SignatureAlgorithm() {}
