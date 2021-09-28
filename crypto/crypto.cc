#include "crypto.h"

/** SignatureAlgorithm **/

SignatureAlgorithm::SignatureAlgorithm() {}

const BIGNUM* SignatureAlgorithm::generatePrivateKey(const std::string signature_algorithm) {
    EC_KEY *ec_key;
    const BIGNUM* private_key;

    if (signature_algorithm == "ECDSA_secp256k1") {
        ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
        if (EC_KEY_generate_key(ec_key)) {
            private_key = EC_KEY_get0_private_key(ec_key);
            return private_key;
        } else {
            return nullptr;
        }
    } else if (signature_algorithm == "ECDSA_P256") {
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


/** HashAlgorithm **/

HashAlgorithm::HashAlgorithm() {}

std::string HashAlgorithm::sha2_256(const std::string& message) {
    uint32_t digest_length = SHA256_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha256();

    return compute_hash(algorithm, digest_length, message);
}

std::string HashAlgorithm::sha2_384(const std::string& message) {
    uint32_t digest_length = SHA384_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha384();

    return compute_hash(algorithm, digest_length, message);
}

std::string HashAlgorithm::sha3_256(const std::string& message) {
    uint32_t digest_length = SHA256_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_256();

    return compute_hash(algorithm, digest_length, message);
}

std::string HashAlgorithm::sha3_384(const std::string& message) {
    uint32_t digest_length = SHA384_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_384();

    return compute_hash(algorithm, digest_length, message);
}

std::string HashAlgorithm::compute_hash(const EVP_MD* algorithm, uint32_t digest_length, const std::string& message) {
    uint8_t* digest = static_cast <uint8_t*>(OPENSSL_malloc(digest_length));
    EVP_MD_CTX* context = EVP_MD_CTX_new();

    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, message.c_str(), message.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);

    std::string hash = string_from_raw_bytes(std::vector<uint8_t>(digest, digest + digest_length));
    OPENSSL_free(digest);

    return hash;
}

std::string HashAlgorithm::string_from_raw_bytes(const std::vector<uint8_t>& bytes) {
    std::ostringstream stream;
    for (uint8_t b : bytes) {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<uint16_t>(b);
    }
    return stream.str();
}
