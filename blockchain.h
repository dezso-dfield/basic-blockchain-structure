#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>
#include <map>
#include <string>

class Blockchain {
private:
    int difficulty = 3;

public:
    std::vector<Block> chain;
    std::map<std::string, double> balances;

    Blockchain();

    void addBlock(const std::vector<Transaction>& transactions);
    bool isChainValid() const;
    void printChain() const;
};

#endif