#pragma once
#include "../models/Employee.h"
#include <vector>
#include <string>
using namespace std;

class EmployeeRepository{
    private:
        string fileName;
    public:
        EmployeeRepository(string fileName = "data/Employee.txt");
        vector<Employee> getAll();
        bool saveAll(const vector<Employee>& employees);
        bool add(const Employee& employee);
        bool update(const Employee& employee);
        bool remove(string NV_ID);
        bool findByID(string NV_ID, Employee& employee);
};
