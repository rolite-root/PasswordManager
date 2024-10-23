#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <openssl/sha.h>

class User {
protected:
    std::string userID;
    std::string encryptedPassword;

public:
    User(const std::string& userID, const std::string& encPassword) : userID(userID), encryptedPassword(encPassword) {}

    virtual void accessManager() = 0; // Pure virtual function for polymorphism

    std::string getUserID() const { return userID; }

    bool authenticate(const std::string& enteredPassword) const {
        return (encryptedPassword == enteredPassword);
    }

    virtual ~User() = default;
};

#endif // USER_H
