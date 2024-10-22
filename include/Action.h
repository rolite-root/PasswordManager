#ifndef ACTION_H
#define ACTION_H

#include "User.h"

class Action {
public:
    virtual void execute(User* user) = 0;  // Pure virtual function
    virtual ~Action() {}
};

class LoginAction : public Action {
public:
    void execute(User* user) override {
        std::cout << "User " << user->getUserID() << " is logging in...\n";
        user->updateLastActivity();
    }
};

class AccessPasswordAction : public Action {
public:
    void execute(User* user) override {
        std::cout << "User " << user->getUserID() << " is accessing passwords.\n";
    }
};

#endif
