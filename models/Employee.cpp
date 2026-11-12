#include "Employee.h"

Employee::Employee() : Person(){
    this->NV_ID = "";
    this->PHG_ID = "";
    this->ngayVaoLam = "";
    this->status = "Dang lam";
}
Employee::Employee(const string& NV_ID, const string& fullName, const string& dateOfBirth, const string& gender, const string& phone, 
    const string& address, const string& PHG_ID, const string& ngayVaoLam, const string& status) : Person(fullName, dateOfBirth, gender, phone, address){
    this->NV_ID = NV_ID;
    this->PHG_ID = PHG_ID;
    this->ngayVaoLam = ngayVaoLam;
    this->status = status;
}
Employee::~Employee(){
}
string Employee::getNV_ID() const{
    return this->NV_ID;
}
string Employee::getPHG_ID() const{
    return this->PHG_ID;
}
string Employee::getNgayVaoLam() const{
    return this->ngayVaoLam;
}
string Employee::getStatus() const{
    return this->status;
}
void Employee::setNV_ID(const string& NV_ID){
    this->NV_ID = NV_ID;
}
void Employee::setPHG_ID(const string& PHG_ID){
    this->PHG_ID = PHG_ID;
}
void Employee::setNgayVaoLam(const string& ngayVaoLam){
    this->ngayVaoLam = ngayVaoLam;
}
void Employee::setStatus(const string& status){
    this->status = status;
}