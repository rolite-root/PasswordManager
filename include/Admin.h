#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>

class Admin : public User {
public:
    // Constructor
    Admin(std::string id, std::string code) : User(id, code) {}

    // Override accessManager from User
    void accessManager() override {
        std::cout << "Admin accessing password manager...\n";
    }

    // Grant access to another user
    void grantAccess(User& user) {
        std::cout << "Access granted to user " << user.getUserID() << ".\n";
    }
};

#endif
