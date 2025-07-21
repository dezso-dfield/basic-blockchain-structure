#include "wallet.h"
#include <openssl/ecdsa.h>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <iostream>

Wallet::Wallet() {
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(key);
}

Wallet::~Wallet() {
    EC_KEY_free(key);
}

std::string Wallet::getPublicKey() const {
    const EC_POINT* pubKeyPoint = EC_KEY_get0_public_key(key);
    EC_GROUP* group = EC_GROUP_new_by_curve_name(NID_secp256k1);

    char* hex = EC_POINT_point2hex(group, pubKeyPoint, POINT_CONVERSION_UNCOMPRESSED, NULL);
    std::string result(hex);
    OPENSSL_free(hex);
    EC_GROUP_free(group);
    return result;
}

std::string Wallet::sign(const std::string& message) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)message.c_str(), message.length(), hash);

    ECDSA_SIG* sig = ECDSA_do_sign(hash, SHA256_DIGEST_LENGTH, key);
    const BIGNUM* r;
    const BIGNUM* s;
    ECDSA_SIG_get0(sig, &r, &s);

    std::stringstream ss;
    ss << std::hex << r << s;

    ECDSA_SIG_free(sig);
    return ss.str();
}

bool Wallet::verify(const std::string& pubKeyHex, const std::string& message, const std::string& signature) {
    // Full implementation coming later — placeholder
    return true;
}