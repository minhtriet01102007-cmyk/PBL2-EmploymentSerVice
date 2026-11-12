#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account{
    private:
        string pass;
        string role;
        string NV_ID;
        bool isLocked;
    public:
        Account();
        Account(const string& pass, const string& role, const string& NV_ID, bool isLocked);
        ~Account();

        string getPass() const;
        string getRole() const;
        string getNV_ID() const;
        bool getIsLocked() const;

        void setPass(const string& pass);
        void setRole(const string& role);
        void setNV_ID(const string& NV_ID);
        void setIsLocked(bool isLocked);
};
