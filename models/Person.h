#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person{
    protected:
        string fullName;
        string dateOfBirth;
        string gender;
        string phone;
        string address;
    public:
        Person();
        Person(const string& fullName, const string& dateOfBirth, const string& gender, const string& phone, const string& address);
        virtual ~Person();

        string getFullName() const;
        string getDateOfBirth() const;
        string getGender() const;
        string getPhone() const;
        string getAddress() const;

        void setFullName(const string& fullName);
        void setDateOfBirth(const string& dateOfBirth);
        void setGender(const string& gender);
        void setPhone(const string& phone);
        void setAddress(const string& address);
};
