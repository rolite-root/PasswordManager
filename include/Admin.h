#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>
#include <map>
#include <vector>

class Admin : public User {
public:
    Admin(const std::string& userID, const std::string& encPassword) : User(userID, encPassword) {}

    // Add password with username and website link
    void addPassword(std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage,
                     const std::string& website, const std::string& username, const std::string& password) {
        passwordStorage[this->getUserID()].emplace_back(website, username, password);
        std::cout << "Password added for Admin.\n";
    }

    // Delete last added password
    void deletePassword(std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage) {
        if (!passwordStorage[this->getUserID()].empty()) {
            passwordStorage[this->getUserID()].pop_back();
            std::cout << "Password deleted for Admin.\n";
        } else {
            std::cout << "No passwords to delete.\n";
        }
    }

    // Modify last added password
    void modifyPassword(std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage, const std::string& newPassword) {
        if (!passwordStorage[this->getUserID()].empty()) {
            std::get<2>(passwordStorage[this->getUserID()].back()) = newPassword;
            std::cout << "Password modified for Admin.\n";
        } else {
            std::cout << "No passwords to modify.\n";
        }
    }

    // Display decrypted passwords
    void displayPasswords(const std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage) const {
        if (passwordStorage.find(this->getUserID()) != passwordStorage.end()) {
            std::cout << "Admin's stored passwords:\n";
            for (const auto& entry : passwordStorage.at(this->getUserID())) {
                std::cout << "Website: " << std::get<0>(entry) << "\nUsername: " << std::get<1>(entry)
                          << "\nPassword: " << std::get<2>(entry) << "\n\n";
            }
        } else {
            std::cout << "No passwords stored for Admin.\n";
        }
    }

    void accessManager() override {
        std::cout << "Admin-specific access management.\n";
    }
};

#endif // ADMIN_H
