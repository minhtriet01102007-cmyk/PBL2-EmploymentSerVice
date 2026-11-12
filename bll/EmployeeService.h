#pragma once
#include "../dal/EmployeeRepository.h"
#include "../dal/AccountRepository.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

class EmployeeService{
    private:
        EmployeeRepository employeeRepository;
        AccountRepository accountRepository;
        bool validateEmployee(const Employee& employee, string& message);
        string generateEmployeeID(string PHG_ID, string gender);
        string getCurrentDate();
    public:
        EmployeeService();
        vector<Employee> getAllEmployees();

        bool addEmployee(Employee& employee, string& message);
        bool updateEmployee(const Employee& employee, string& message);
        bool deleteEmployee(string NV_ID, string& message);

        bool findByID(string NV_ID, Employee& employee);
        vector<Employee> searchByName(string name);

        vector<Employee> sortByID();
        vector<Employee> sortByName();
        vector<Employee> sortByDepartment();

        vector<Employee> filterByDepartment(string PHG_ID);

        bool confirmResignation(string NV_ID, string& message);
};

