#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(std::string id, std::string code) : User(id, code) {}

    void accessManager() override {
        std::cout << "Admin " << userID << " managing the system.\n";
    }

    void grantAccess(User& user) {
        if (user.isThreeWeeksInactive()) {
            std::cout << "Cannot grant access. User " << user.getUserID() << " has been inactive for 3 weeks.\n";
        } else {
            std::cout << "Access granted to user " << user.getUserID() << ".\n";
        }
    }
};

#endif
