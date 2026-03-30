#pragma once
#include <string>

class UserAuthentication {
public:
    virtual bool signup(const std::string& userName, int pwd) = 0;
    virtual bool login(const std::string& userName, int pwd) = 0;
    virtual void logout() = 0;
    virtual bool changePassword(int oldPwd, int newPwd) = 0;
};

