#ifndef ACTION_H
#define ACTION_H

#include "User.h"

// Abstract Action class
class Action {
public:
    virtual void execute(User* user) = 0; // Pure virtual function
    virtual ~Action() = default;
};

class LoginAction : public Action {
public:
    void execute(User* user) override {
        std::cout << "Logging in user: " << user->getUserID() << std::endl;
    }
};

class AccessPasswordAction : public Action {
public:
    void execute(User* user) override {
        std::cout << "Accessing passwords for user: " << user->getUserID() << std::endl;
    }
};

#endif // ACTION_H
