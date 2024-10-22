#ifndef STANDARDUSER_H
#define STANDARDUSER_H

#include "User.h"
#include <iostream>

class StandardUser : public User {
public:
    // Constructor
    StandardUser(std::string id, std::string code) : User(id, code) {}

    // Override accessManager from User
    void accessManager() override {
        std::cout << "Standard User accessing password manager...\n";
    }
};

#endif
