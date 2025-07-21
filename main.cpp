#include <iostream>
#include "blockchain.h"
#include "transaction.h"

int main() {
    Blockchain chain;

    std::vector<Transaction> block1 = {
        Transaction("Alice", "Bob", 50),
        Transaction("Bob", "Charlie", 25)
    };

    std::vector<Transaction> block2 = {
        Transaction("Charlie", "Dan", 10),
        Transaction("Bob", "Dan", 5)
    };

    chain.balances["Alice"] = 100;  // Genesis funding

    chain.addBlock(block1);
    chain.addBlock(block2);

    std::cout << "\n✅ Chain Valid? " << (chain.isChainValid() ? "Yes" : "No") << "\n";
    chain.printChain();

    return 0;
}