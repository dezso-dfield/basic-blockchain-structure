#include "block.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

Block::Block(int index, const std::vector<Transaction>& txs, const std::string& prevHash)
    : index(index), transactions(txs), previousHash(prevHash), nonce(0) {
    timestamp = currentTime();
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << nonce;
    for (const auto& tx : transactions) {
        ss << tx.toString();
    }
    return sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    std::cout << "⛏️ Block mined: " << hash << std::endl;
}

std::string Block::currentTime() const {
    time_t now = time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}