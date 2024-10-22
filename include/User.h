#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
#include <iostream>
#include <openssl/evp.h> // OpenSSL for password encryption

class User {
protected:
    std::string userID;
    std::string encryptedCode;
    time_t lastActivity;

    // Encrypt the password using OpenSSL
    std::string encryptPassword(const std::string& password) {
        // Basic example using OpenSSL for password encryption (actual encryption should be more detailed)
        return "encrypted_" + password; // Simplified placeholder
    }

public:
    User(std::string id, std::string code)
        : userID(id), encryptedCode(encryptPassword(code)), lastActivity(std::time(0)) {}

    virtual void accessManager() = 0;  // Pure virtual function

    void updateLastActivity() {
        lastActivity = std::time(0);
    }

    bool isThreeWeeksInactive() {
        time_t now = std::time(0);
        double secondsInactive = difftime(now, lastActivity);
        return (secondsInactive >= 3 * 7 * 24 * 60 * 60);  // 3 weeks in seconds
    }

    std::string getUserID() const {
        return userID;
    }

    virtual ~User() {}
};

#endif
