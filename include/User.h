#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

class User {
protected:
    std::string userID;
    std::string encryptedCode;
    time_t lastActivity;

public:
    // Constructor
    User(std::string id, std::string code) 
        : userID(id), encryptedCode(code), lastActivity(std::time(0)) {}
    
    // Public getter for userID
    std::string getUserID() const {
        return userID;
    }

    // Pure virtual function to be overridden by derived classes
    virtual void accessManager() = 0;

    // Function to update last activity timestamp
    void updateLastActivity() {
        lastActivity = std::time(0);
    }

    // Check if 3 weeks have passed without activity
    bool isThreeWeeksInactive() {
        return std::difftime(std::time(0), lastActivity) >= 3 * 7 * 24 * 60 * 60;  // 3 weeks in seconds
    }

    // Virtual destructor
    virtual ~User() {}
};

#endif
