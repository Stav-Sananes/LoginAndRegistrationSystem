#pragma once
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    User(const std::string& user, const std::string& pass);
    bool registerUser();
    bool loginUser(); 
};

#endif
