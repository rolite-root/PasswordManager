#ifndef UTILITY_H
#define UTILITY_H

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// Convert bytes to hex string (helper function)
std::string toHex(const unsigned char* bytes, size_t length) {
    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i];
    }
    return oss.str();
}

// Secure hashing function using SHA-256
std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);
    return toHex(hash, SHA256_DIGEST_LENGTH);
}

#endif // UTILITY_H
