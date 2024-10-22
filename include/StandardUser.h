#ifndef STANDARD_USER_H
#define STANDARD_USER_H

#include "User.h"
#include <iostream>

class StandardUser : public User {
public:
    StandardUser(const std::string& userID, const std::string& encPassword) : User(userID, encPassword) {}

    void accessManager() override {
        std::cout << "Standard user-specific access management." << std::endl;
    }
};

#endif // STANDARD_USER_H
