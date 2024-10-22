#include "S:\\Projects\\PasswordManager\\include\\Admin.h"
#include "S:\\Projects\\PasswordManager\\include\\StandardUser.h"
#include "S:\\Projects\\PasswordManager\\include\\Action.h"
#include <iostream>
#include <memory>

int main() {
    Admin admin("Admin123", "encAdminCode");
    StandardUser standardUser("User456", "encUserCode");

    // Actions
    std::unique_ptr<LoginAction> login = std::make_unique<LoginAction>();
    std::unique_ptr<AccessPasswordAction> accessPasswords = std::make_unique<AccessPasswordAction>();

    // Execute actions for the Admin
    try {
        login->execute(&admin);
        accessPasswords->execute(&admin);
    } catch (const std::exception& e) {
        std::cerr << "Error executing action for Admin: " << e.what() << std::endl;
    }

    // Execute actions for the StandardUser
    try {
        login->execute(&standardUser);
        accessPasswords->execute(&standardUser);
    } catch (const std::exception& e) {
        std::cerr << "Error executing action for StandardUser: " << e.what() << std::endl;
    }

    return 0;
}
