#include "EmployeeService.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

EmployeeService::EmployeeService(){}

string EmployeeService::getCurrentDate(){
    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << put_time(localTime, "%d/%m/%Y");

    return ss.str();
}
bool EmployeeService::validateEmployee(const Employee& employee, string& message){
    if (employee.getFullName().empty()){
        message = "Ho ten khong duoc de trong!";
        return false;
    }
    if (employee.getPHG_ID().length() != 3){
        message = "Ma phong ban phai co 3 ky tu!";
        return false;
    }
    for (char c : employee.getPHG_ID()){
        if (!isdigit(c)){
            message = "Ma phong ban phai la chu so!";
            return false;
        }
    }
    if (employee.getGender() != "Nam" && employee.getGender() != "Nu"){
        message = "Gioi tinh phai la Nam hoac Nu!";
        return false;
    }
    if (employee.getPhone().empty()){
        message = "So dien thoai khong duoc de trong!";
        return false;
    }
    return true;
}
string EmployeeService::generateEmployeeID(string PHG_ID, string gender){
    vector<Employee> employees = employeeRepository.getAll();
    string genderCode = (gender == "Nam") ? "01" : "02";
    int maxNumber = 10;

    for (const Employee& employee : employees){
        string id = employee.getNV_ID();
        if (id.length() == 10 && id.substr(0, 5) == PHG_ID + genderCode){
            try{
                int number = stoi(id.substr(5));
                if (number > maxNumber){
                    maxNumber = number;
                }
            } 
            catch (...){
                continue;
            }
        }
    }
    int nextNumber = maxNumber + 1;
    stringstream ss;
    ss << PHG_ID << genderCode << setw(5) << setfill('0') << nextNumber;
    return ss.str();
}
vector<Employee> EmployeeService::getAllEmployees(){
    return employeeRepository.getAll();
}
bool EmployeeService::addEmployee(Employee& employee, string& message){
    if (!validateEmployee(employee, message)){
        return false;
    }
    employee.setNV_ID(generateEmployeeID(employee.getPHG_ID(), employee.getGender()));
    if (employee.getNgayVaoLam().empty()){
        employee.setNgayVaoLam(getCurrentDate());
    }
    if (employee.getStatus().empty()){
        employee.setStatus("Dang lam");
    }
    Account account(employee.getNV_ID(), "employee", employee.getNV_ID(), false);
    if (!accountRepository.add(account)){
        message = "Khong the tao tai khoan nhan vien!";
        return false;
    }
    if (!employeeRepository.add(employee)){
        accountRepository.remove(employee.getNV_ID());
        message = "Khong the them nhan vien!";
        return false;
    }
    message = "Them nhan vien va tao tai khoan thanh cong!";
    return true;
}
bool EmployeeService::updateEmployee(const Employee& employee, string& message){
    Employee oldEmployee;
    if (!employeeRepository.findByID(employee.getNV_ID(), oldEmployee)){
        message = "Khong tim thay nhan vien!";
        return false;
    }
    if (oldEmployee.getStatus() == "Da nghi viec"){
        message = "Nhan vien da nghi viec, khong the cap nhat!";
        return false;
    }
    if (!validateEmployee(employee, message)){
        return false;
    }
    if (!employeeRepository.update(employee)){
        message = "Cap nhat that bai!";
        return false;
    }
    message = "Cap nhat nhan vien thanh cong!";
    return true;
}
bool EmployeeService::deleteEmployee(
    string NV_ID, string& message){

    Employee employee;

    if (!employeeRepository.findByID(NV_ID, employee)){
        message = "Khong tim thay nhan vien!";
        return false;
    }
    if (!employeeRepository.remove(NV_ID)){
        message = "Xoa nhan vien that bai!";
        return false;
    }

    accountRepository.remove(NV_ID);

    message = "Xoa nhan vien thanh cong!";
    return true;
}
bool EmployeeService::findByID(string NV_ID, Employee& employee){
    return employeeRepository.findByID(NV_ID, employee);
}
vector<Employee> EmployeeService::searchByName(string name){
    vector<Employee> employees = getAllEmployees();
    vector<Employee> result;

    for (const Employee& employee : employees){
        if (employee.getFullName().find(name) != string::npos){
            result.push_back(employee);
        }
    }
    return result;
}
vector<Employee> EmployeeService::sortByID(){
    vector<Employee> employees = getAllEmployees();

    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b){
            return a.getNV_ID() < b.getNV_ID();
        });
    return employees;
}
vector<Employee> EmployeeService::sortByName(){
    vector<Employee> employees = getAllEmployees();

    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b){
            return a.getFullName() < b.getFullName();
        });
    return employees;
}
vector<Employee> EmployeeService::sortByDepartment(){
    vector<Employee> employees = getAllEmployees();

    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b){
            return a.getPHG_ID() < b.getPHG_ID();
        });
    return employees;
}
vector<Employee> EmployeeService::filterByDepartment(string PHG_ID){
    vector<Employee> employees = getAllEmployees();
    vector<Employee> result;

    for (const Employee& employee : employees){
        if (employee.getPHG_ID() == PHG_ID){
            result.push_back(employee);
        }
    }
    return result;
}
bool EmployeeService::confirmResignation(string NV_ID, string& message){
    Employee employee;
    if (!employeeRepository.findByID(NV_ID, employee)){
        message = "Khong tim thay nhan vien!";
        return false;
    }
    if (employee.getStatus() == "Da nghi viec"){
        message = "Nhan vien da nghi viec truoc do!";
        return false;
    }
    employee.setStatus("Da nghi viec");

    if (!employeeRepository.update(employee)){
        message = "Xac nhan nghi viec that bai!";
        return false;
    }

    Account account;

    if (accountRepository.findByID(NV_ID, account)){
        account.setIsLocked(true);
        accountRepository.update(account);
    }

    message = "Da xac nhan nhan vien nghi viec va khoa tai khoan!";
    return true;
}