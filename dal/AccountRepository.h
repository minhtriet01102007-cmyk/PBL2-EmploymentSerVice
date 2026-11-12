#pragma once
#include "../models/Account.h"
#include <vector>
#include <string>
using namespace std;

class AccountRepository{
    private:
        string fileName;
    public:
        AccountRepository(string fileName = "data/Account.txt");
        vector<Account> getAll();
        bool saveAll(const vector<Account>& accounts);
        bool add(const Account& account);
        bool update(const Account& account);
        bool remove(string NV_ID);
        bool findByID(string NV_ID, Account& account);
};
