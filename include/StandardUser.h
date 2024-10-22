#ifndef STANDARDUSER_H
#define STANDARDUSER_H

#include "User.h"

class StandardUser : public User {
public:
    StandardUser(std::string id, std::string code) : User(id, code) {}

    void accessManager() override {
        std::cout << "Standard user " << userID << " managing personal data.\n";
    }
};

#endif
