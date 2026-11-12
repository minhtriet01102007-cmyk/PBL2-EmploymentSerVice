#include "Account.h"
Account::Account(){
    this->pass = "";
    this->role = "";
    this->NV_ID = "";
    this->isLocked = false;
}
Account::Account(const string& pass, const string& role, const string& NV_ID, bool isLocked){
    this->pass = pass;
    this->role = role;
    this->NV_ID = NV_ID;
    this->isLocked = isLocked;
}
Account::~Account(){
}
string Account::getPass() const{
    return this->pass;
}
string Account::getRole() const{
    return this->role;
}
string Account::getNV_ID() const{
    return this->NV_ID;
}
bool Account::getIsLocked() const{
    return this->isLocked;
}
void Account::setPass(const string& pass){
    this->pass = pass;
}
void Account::setRole(const string& role){
    this->role = role;
}
void Account::setNV_ID(const string& NV_ID){
    this->NV_ID = NV_ID;
}
void Account::setIsLocked(bool isLocked){
    this->isLocked = isLocked;
}
