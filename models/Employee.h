#pragma once
#include "Person.h"
#include <string>
using namespace std;

class Employee : public Person{
    private:
        string NV_ID;
        string PHG_ID; //ma phong ban
        string ngayVaoLam;
        string status; //trang thai
    public:
        Employee();
        Employee(const string& NV_ID, const string& fullName, const string& dateOfBirth, const string& gender, const string& phone, 
                 const string& address, const string& PHG_ID, const string& ngayVaoLam, const string& status);
        ~Employee() override;
        string getNV_ID() const;
        string getPHG_ID() const;
        string getNgayVaoLam() const;
        string getStatus() const;

        void setNV_ID(const string& NV_ID);
        void setPHG_ID(const string& PHG_ID);
        void setNgayVaoLam(const string& ngayVaoLam);
        void setStatus(const string& status);
};
