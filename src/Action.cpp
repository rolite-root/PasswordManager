#include "S:\\Projects\\PasswordManager\\include\\Action.h"
#include <iostream>

void LoginAction::execute(User* user) {
    std::cout << "User " << user->getUserID() << " is logging in...\n";
}

void AccessPasswordAction::execute(User* user) {
    user->accessManager();
}
