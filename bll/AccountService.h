#pragma once
#include "../dal/AccountRepository.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class AccountService{
    private:
        AccountRepository accountRepository;
    public:
        AccountService();
        bool login(const string& NV_ID, const string& pass, Account& loginAccount, string& message);
        bool changePassword(string NV_ID, string oldPass, string newPass, string& message);
        bool createAccount(string NV_ID, string role);
        bool lockAccount(string NV_ID, string& message);
        bool unlockAccount(string NV_ID, string& message);
        vector<Account> getAllAccounts();
};
