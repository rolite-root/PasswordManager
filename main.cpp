#include "S:\\Projects\\PasswordManager\\include\\Admin.h"
#include "S:\\Projects\\PasswordManager\\include\\StandardUser.h"
#include "S:\\Projects\\PasswordManager\\include\\Action.h"
#include "S:\\Projects\\PasswordManager\\include\\Utility.h" 
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>  

// File path to store passwords
const std::string PASSWORD_FILE = "passwords.csv";

// Helper function to save passwords to a file (CSV format)
void savePasswordsToFile(const std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage) {
    std::ofstream file(PASSWORD_FILE);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    for (const auto& user : passwordStorage) {
        for (const auto& entry : user.second) {
            file << user.first << "," << std::get<0>(entry) << "," << std::get<1>(entry) << "," << std::get<2>(entry) << "\n";
        }
    }

    file.close();
}

// Helper function to load passwords from a file (CSV format)
void loadPasswordsFromFile(std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>>& passwordStorage) {
    std::ifstream file(PASSWORD_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading, or file does not exist.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userID, website, username, password;

        std::getline(ss, userID, ',');
        std::getline(ss, website, ',');
        std::getline(ss, username, ',');
        std::getline(ss, password, ',');

        passwordStorage[userID].emplace_back(website, username, password);
    }

    file.close();
}

int main() {
    // Initial Setup
    Admin admin("admin", hashPassword("admin"));
    StandardUser standardUser("user", hashPassword("user"));

    // Store passwords for both Admin and Standard User
    std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>> passwordStorage;

    // Load stored passwords from file at the beginning
    loadPasswordsFromFile(passwordStorage);

    // Authentication Process
    std::string enteredPassword;
    std::cout << "Enter Admin or User Password to login: ";
    std::cin >> enteredPassword;

    if (admin.authenticate(hashPassword(enteredPassword))) {
        std::cout << "Admin logged in successfully.\n";
        int choice;
        while (true) {
            std::cout << "1. Add Password\n2. Delete Password\n3. Modify Password\n4. Display Passwords\n5. Logout\n";
            std::cin >> choice;

            if (choice == 1) {
                std::string website, username, password;
                std::cout << "Enter website: ";
                std::cin >> website;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                admin.addPassword(passwordStorage, website, username, password);
            } else if (choice == 2) {
                admin.deletePassword(passwordStorage);
            } else if (choice == 3) {
                std::string newPassword;
                std::cout << "Enter new password: ";
                std::cin >> newPassword;
                admin.modifyPassword(passwordStorage, newPassword);
            } else if (choice == 4) {
                admin.displayPasswords(passwordStorage);
            } else if (choice == 5) {
                // Save passwords to file before logging out
                savePasswordsToFile(passwordStorage);
                std::cout << "Passwords saved. Admin logged out.\n";
                break;
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
    } else if (standardUser.authenticate(hashPassword(enteredPassword))) {
        std::cout << "Standard User logged in successfully.\n";
        standardUser.displayPasswords(passwordStorage); // Display encrypted passwords for Standard User
    } else {
        std::cout << "Authentication failed.\n";
    }

    return 0;
}
