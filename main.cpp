#include "S:\\Projects\\PasswordManager\\include\\Admin.h"
#include "S:\\Projects\\PasswordManager\\include\\StandardUser.h"
#include "S:\\Projects\\PasswordManager\\include\\Action.h"
#include <iostream>

int main() {
    Admin admin("Admin123", "encAdminCode");
    StandardUser standardUser("User456", "encUserCode");

    // Actions
    LoginAction* login = new LoginAction();
    AccessPasswordAction* accessPasswords = new AccessPasswordAction();

    // Execute actions for the Admin
    login->execute(&admin);
    accessPasswords->execute(&admin);

    // Execute actions for the StandardUser
    login->execute(&standardUser);
    accessPasswords->execute(&standardUser);

    // Grant access to the standard user by admin
    admin.grantAccess(standardUser);

    // Clean up dynamically allocated memory
    delete login;
    delete accessPasswords;

    return 0;
}
