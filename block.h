#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include <vector>
#include <string>

class Block {
public:
    int index;
    std::vector<Transaction> transactions;
    std::string timestamp;
    std::string previousHash;
    std::string hash;
    int nonce;

    Block(int index, const std::vector<Transaction>& txs, const std::string& prevHash);

    void mineBlock(int difficulty);
    std::string calculateHash() const;

private:
    std::string currentTime() const;
};

#endif