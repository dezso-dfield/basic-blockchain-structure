#include "transaction.h"
#include <sstream>
#include <iostream>

Transaction::Transaction(const std::string& from, const std::string& to, double amount)
    : from(from), to(to), amount(amount) {}

std::string Transaction::toString() const {
    std::stringstream ss;
    ss << from << "->" << to << ": " << amount;
    return ss.str();
}