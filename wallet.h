#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <openssl/ec.h>
#include <openssl/pem.h>

class Wallet {
private:
    EC_KEY* key;

public:
    Wallet();
    ~Wallet();

    std::string getPublicKey() const;
    std::string sign(const std::string& message) const;
    static bool verify(const std::string& pubKey, const std::string& message, const std::string& signature);
};

#endif