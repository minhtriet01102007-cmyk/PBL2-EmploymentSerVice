#include <string>
#include <fstream>
#include <vector>
#include "EmployeeRepository.h"


EmployeeRepository::EmployeeRepository(std::string fileName){
    this->fileName = fileName;
}
std::vector<Employee> EmployeeRepository::getAll(){
    std::vector<Employee> employees;
    std::ifstream file(fileName);
    if (!file.is_open()){
        return employees;
    }
    std::string NV_ID, fullName, dateOfBirth, gender;
    std::string phone, address, PHG_ID, ngayVaoLam, status;
    while (std::getline(file, NV_ID)){
        if (!std::getline(file, fullName) ||
            !std::getline(file, dateOfBirth) ||
            !std::getline(file, gender) ||
            !std::getline(file, phone) ||
            !std::getline(file, address) ||
            !std::getline(file, PHG_ID) ||
            !std::getline(file, ngayVaoLam) ||
            !std::getline(file, status)){
            break;
        }
        employees.push_back(Employee(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status));
    }
    file.close();
    return employees;
}
bool EmployeeRepository::saveAll(const std::vector<Employee>& employees){
    std::ofstream file(fileName);
    if (!file.is_open()){
        return false;
    }
    for (const Employee& employee : employees){
        file << employee.getNV_ID() << std::endl;
        file << employee.getFullName() << std::endl;
        file << employee.getDateOfBirth() << std::endl;
        file << employee.getGender() << std::endl;
        file << employee.getPhone() << std::endl;
        file << employee.getAddress() << std::endl;
        file << employee.getPHG_ID() << std::endl;
        file << employee.getNgayVaoLam() << std::endl;
        file << employee.getStatus() << std::endl;
    }
    file.close();
    return true;
}
bool EmployeeRepository::add(const Employee& employee){
    std::vector<Employee> employees = getAll();
    for (const Employee& item : employees){
        if (item.getNV_ID() == employee.getNV_ID()){
            return false;
        }
    }
    employees.push_back(employee);
    return saveAll(employees);
}
bool EmployeeRepository::update(const Employee& employee){
    std::vector<Employee> employees = getAll();
    bool found = false;
    for (Employee& item : employees){
        if (item.getNV_ID() == employee.getNV_ID()){
            item = employee;
            found = true;
            break;
        }
    }
    if (!found){
        return false;
    }
    return saveAll(employees);
}
bool EmployeeRepository::remove(std::string NV_ID){
    std::vector<Employee> employees = getAll();
    bool found = false;

    for (int i = 0; i < employees.size(); i++){
        if (employees[i].getNV_ID() == NV_ID){
            employees.erase(employees.begin() + i);
            found = true;
            break;
        }
    }
    if (!found){
        return false;
    }
    return saveAll(employees);
}
bool EmployeeRepository::findByID(std::string NV_ID, Employee& employee){
    std::vector<Employee> employees = getAll();
    for (const Employee& item : employees){
        if (item.getNV_ID() == NV_ID) {
            employee = item;
            return true;
        }
    }
    return false;
}