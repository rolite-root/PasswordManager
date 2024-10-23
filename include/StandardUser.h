#ifndef STANDARD_USER_H
#define STANDARD_USER_H

#include "User.h"
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include "Utility.h" // Include the Utility.h file for hashPassword

class StandardUser : public User {
public:
    StandardUser(const std::string& userID, const std::string& encPassword) : User(userID, encPassword) {}

    // Display encrypted passwords (as hashed values)
    void displayPasswords(const std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage) const {
        if (passwordStorage.find(this->getUserID()) != passwordStorage.end()) {
            std::cout << "Standard User's stored passwords (encrypted):\n";
            for (const auto& entry : passwordStorage.at(this->getUserID())) {
                std::cout << "Website: " << std::get<0>(entry) << "\nUsername: " << std::get<1>(entry)
                          << "\nPassword (encrypted): " << hashPassword(std::get<2>(entry)) << "\n\n";
            }
        } else {
            std::cout << "No passwords stored for Standard User.\n";
        }
    }

    void accessManager() override {
        std::cout << "Standard user-specific access management.\n";
    }
};

#endif // STANDARD_USER_H
