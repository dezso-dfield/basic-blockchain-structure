#include "blockchain.h"
#include <iostream>

Blockchain::Blockchain() {
    std::vector<Transaction> genesisTxs;
    chain.emplace_back(0, genesisTxs, "0");
    chain[0].mineBlock(difficulty);
}

void Blockchain::addBlock(const std::vector<Transaction>& transactions) {
    std::vector<Transaction> validTxs;

    for (const auto& tx : transactions) {
        if (tx.from != "MINER") {
            if (balances[tx.from] < tx.amount) {
                std::cout << "❌ Skipping invalid tx (insufficient funds): " << tx.toString() << "\n";
                continue;
            }
            balances[tx.from] -= tx.amount;
        }
        balances[tx.to] += tx.amount;
        validTxs.push_back(tx);
    }

    // Add mining reward
    Transaction reward("MINER", "miner_address", 50);
    balances["miner_address"] += 50;
    validTxs.push_back(reward);

    Block newBlock(chain.size(), validTxs, chain.back().hash);
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i];
        const Block& prev = chain[i - 1];

        if (current.hash != current.calculateHash())
            return false;

        if (current.previousHash != prev.hash)
            return false;
    }
    return true;
}

void Blockchain::printChain() const {
    for (const auto& block : chain) {
        std::cout << "\nBlock #" << block.index
                  << "\nHash: " << block.hash
                  << "\nPrevious: " << block.previousHash
                  << "\nTimestamp: " << block.timestamp
                  << "\nTransactions:\n";
        for (const auto& tx : block.transactions) {
            std::cout << "  " << tx.toString() << "\n";
        }
        std::cout << "Nonce: " << block.nonce << "\n";
    }

    std::cout << "\n💰 Balances:\n";
    for (const auto& [addr, bal] : balances) {
        std::cout << "  " << addr << ": " << bal << "\n";
    }
}