#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>

class Admin : public User {
public:
    Admin(const std::string& userID, const std::string& encPassword) : User(userID, encPassword) {}

    void grantAccess(User& user) {
        std::cout << "Admin " << this->getUserID() << " is granting access to user: " << user.getUserID() << std::endl;
    }

    void accessManager() override {
        std::cout << "Admin-specific access management." << std::endl;
    }
};

#endif // ADMIN_H
