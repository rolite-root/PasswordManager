#include "S:\\Projects\\PasswordManager\\include\\Admin.h"
#include "S:\\Projects\\PasswordManager\\include\\StandardUser.h"
#include "S:\\Projects\\PasswordManager\\include\\Action.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <openssl/sha.h> // For secure hashing (we can upgrade it by replacing this with AES or bcrypt for real-world security)

// Convert bytes to hex string (helper function)
std::string toHex(const unsigned char* bytes, size_t length) {
    std::string hexStr;
    for (size_t i = 0; i < length; ++i) {
        char buffer[3];
        sprintf(buffer, "%02x", bytes[i]);
        hexStr.append(buffer);
    }
    return hexStr;
}

// Secure hashing function using SHA-256
std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);
    return toHex(hash, SHA256_DIGEST_LENGTH);
}

int main() {
    Admin admin("Admin123", "encAdminCode");
    StandardUser standardUser("User456", "encUserCode");

    // Store passwords for each user
    std::map<std::string, std::vector<std::string>> passwordStorage; // Maps userID to a list of hashed passwords

    // Actions (polymorphic behavior)
    LoginAction* login = new LoginAction();
    AccessPasswordAction* accessPasswords = new AccessPasswordAction();

    // Execute actions for Admin
    login->execute(&admin);
    accessPasswords->execute(&admin);

    // Execute actions for Standard User
    login->execute(&standardUser);
    accessPasswords->execute(&standardUser);

    // Grant access to the standard user by admin (optional)
    admin.grantAccess(standardUser);

    // User input for password storage
    std::string password;
    std::cout << "Enter a password to store: ";
    std::cin >> password;

    // Securely hash the password before storage
    std::string hashedPassword = hashPassword(password);

    // Store password based on the user selection
    std::string currentUserID;
    std::cout << "Are you storing the password for the Admin or StandardUser? (Type 'admin' or 'user'): ";
    std::cin >> currentUserID;

    if (currentUserID == "admin") {
        passwordStorage[admin.getUserID()].push_back(hashedPassword);
    } else if (currentUserID == "user") {
        passwordStorage[standardUser.getUserID()].push_back(hashedPassword);
    } else {
        std::cerr << "Invalid user selection." << std::endl;
        return 1;
    }

    // Display stored encrypted passwords for the selected user
    std::cout << "\nStored encrypted (hashed) passwords for " << currentUserID << ":" << std::endl;
    for (const auto& storedPassword : passwordStorage[currentUserID == "admin" ? admin.getUserID() : standardUser.getUserID()]) {
        std::cout << storedPassword << std::endl;
    }

    // Clean up
    delete login;
    delete accessPasswords;

    return 0;
}
