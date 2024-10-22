#ifndef ACTION_H
#define ACTION_H

#include "User.h"

class Action {
public:
    virtual void execute(User *user) = 0;  // Pure virtual function
};

class LoginAction : public Action {
public:
    void execute(User *user) override;
};

class AccessPasswordAction : public Action {
public:
    void execute(User *user) override;
};

#endif
