#include "AccountRepository.h"
#include <fstream>

AccountRepository::AccountRepository(string fileName){
    this->fileName = fileName;
}
vector<Account> AccountRepository::getAll(){
    vector<Account> accounts;
    ifstream file(fileName);

    if (!file.is_open()){
        return accounts;
    }
    string pass, role, NV_ID, locked;
    while (getline(file, pass)){
        if (!getline(file, role) || !getline(file, NV_ID) || !getline(file, locked)){
            break;
        }
        bool isLocked = (locked == "1");
        accounts.push_back(Account(pass, role, NV_ID, isLocked));
    }
    file.close();
    return accounts;
}
bool AccountRepository::saveAll(const vector<Account>& accounts){
    ofstream file(fileName);
    if (!file.is_open()){
        return false;
    }
    for (const Account& account : accounts){
        file << account.getPass() << endl;
        file << account.getRole() << endl;
        file << account.getNV_ID() << endl;
        file << (account.getIsLocked() ? "1" : "0") << endl;
    }
    file.close();
    return true;
}
bool AccountRepository::add(const Account& account){
    vector<Account> accounts = getAll();
    for (const Account& item : accounts){
        if (item.getNV_ID() == account.getNV_ID()){
            return false;
        }
    }
    accounts.push_back(account);
    return saveAll(accounts);
}
bool AccountRepository::update(const Account& account){
    vector<Account> accounts = getAll();
    bool found = false;
    for (Account& item : accounts){
        if (item.getNV_ID() == account.getNV_ID()){
            item = account;
            found = true;
            break;
        }
    }
    if (!found){
        return false;
    }
    return saveAll(accounts);
}
bool AccountRepository::remove(string NV_ID){
    vector<Account> accounts = getAll();
    bool found = false;
    for (int i = 0; i < accounts.size(); i++){
        if (accounts[i].getNV_ID() == NV_ID) {
            accounts.erase(accounts.begin() + i);
            found = true;
            break;
        }
    }
    if (!found){
        return false;
    }
    return saveAll(accounts);
}
bool AccountRepository::findByID(string NV_ID, Account& account){
    vector<Account> accounts = getAll();
    for (const Account& item : accounts){
        if (item.getNV_ID() == NV_ID){
            account = item;
            return true;
        }
    }
    return false;
}