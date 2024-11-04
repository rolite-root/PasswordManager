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
#include <sstream>

const std::string PASSWORD_FILE = "passwords.csv";

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
    Admin admin("admin", hashPassword("admin"));
    StandardUser standardUser("user", hashPassword("user"));
    std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string>>> passwordStorage;
    loadPasswordsFromFile(passwordStorage);

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
                savePasswordsToFile(passwordStorage); // Auto-save after adding
                std::cout << "Password saved.\n";

            } else if (choice == 3) {
                size_t index = 0; // Updated to `size_t` to match vector size type
                std::cout << "Select a password to modify:\n";
                for (const auto& entry : passwordStorage[admin.getUserID()]) {
                    std::cout << index++ << ". " << std::get<0>(entry) << " (Username: " << std::get<1>(entry) << ")\n";
                }
                std::cout << "Enter index to modify: ";
                std::cin >> index;

                if (index < passwordStorage[admin.getUserID()].size()) {  // Comparison is now safe
                    std::string newWebsite, newUsername, newPassword;
                    std::cout << "Enter new website: ";
                    std::cin >> newWebsite;
                    std::cout << "Enter new username: ";
                    std::cin >> newUsername;
                    std::cout << "Enter new password: ";
                    std::cin >> newPassword;
                    passwordStorage[admin.getUserID()][index] = std::make_tuple(newWebsite, newUsername, newPassword);
                    savePasswordsToFile(passwordStorage); // Auto-save after modification
                    std::cout << "Password modified and saved.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }

            } else if (choice == 4) {
                admin.displayPasswords(passwordStorage);
            } else if (choice == 5) {
                std::cout << "Admin logged out.\n";
                break;
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
    } else if (standardUser.authenticate(hashPassword(enteredPassword))) {
        std::cout << "Standard User logged in successfully.\n";
        standardUser.displayPasswords(passwordStorage);
    } else {
        std::cout << "Authentication failed.\n";
    }

    return 0;
}