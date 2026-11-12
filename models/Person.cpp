#include "Person.h"
Person::Person(){
    this->fullName = "";
    this->dateOfBirth = "";
    this->gender = "";
    this->phone = "";
    this->address = "";
}
Person::Person(const string& fullName, const string& dateOfBirth, const string& gender, const string& phone, const string& address){
    this->fullName = fullName;
    this->dateOfBirth = dateOfBirth;
    this->gender = gender;
    this->phone = phone;
    this->address = address;
}
Person::~Person(){
}
string Person::getFullName() const{
    return this->fullName;
}
string Person::getDateOfBirth() const{
    return this->dateOfBirth;
}
string Person::getGender() const{
    return this->gender;
}
string Person::getPhone() const{
    return this->phone;
}
string Person::getAddress() const{
    return this->address;
}
void Person::setFullName(const string& fullName){
    this->fullName = fullName;
}
void Person::setDateOfBirth(const string& dateOfBirth){
    this->dateOfBirth = dateOfBirth;
}
void Person::setGender(const string& gender){
    this->gender = gender;
}
void Person::setPhone(const string& phone){
    this->phone = phone;
}
void Person::setAddress(const string& address){
    this->address = address;
}