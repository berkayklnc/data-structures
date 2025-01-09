/*@Author
StudentName: Berkay Kılınç
StudentId: 150210024
Date: 03.11.2023
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <list>

using namespace std;
class Employee
{
private:
    int id;
    int salary;
    int department;

public:
    Employee();
    ~Employee();
    void set_salary(int);
    void set_id(int);
    void set_department(int);
    int get_id();
    int get_salary();
    int get_department();
};
Employee::Employee()
{
    this->id = 0;
    this->salary = 0;
    this->department = 0;
}

Employee::~Employee() {}

void Employee::set_salary(int sal)
{
    this->salary = sal;
}

void Employee::set_id(int id)
{
    this->id = id;
}

void Employee::set_department(int dep)
{
    this->department = dep;
}
int Employee::get_id()
{
    return this->id;
}
int Employee::get_salary()
{
    return this->salary;
}
int Employee::get_department()
{
    return this->department;
}

/*int findIndex(list<Employee> &employeeList, int id)
{
    for (int i = 0; i < (int)employeeList.size(); i++)
    {
        if (employeeList[i].get_id() == id)
        {
            return i;
        }
    }
    // Error gelecek.
    return -1;
}*/
void readFileandSetList(string argv, list<Employee> &employeeList, int &last_id)
{
    ifstream infile(argv);
    int id, salary, department;
    string line;
    char d;
    if (infile.is_open())
    {
        getline(infile, line);
        while (infile >> id >> d >> salary >> d >> department && d == ';')
        {
            Employee newEmployee;
            newEmployee.set_id(id);
            newEmployee.set_salary(salary);
            newEmployee.set_department(department);
            employeeList.push_back(newEmployee);
            ++last_id;
        };
    }
    else
    {
        cout << "file can not found!!";
    }
    infile.close();
}

void addEmployee(list<Employee> &employeeList, int salary, int department, int &last_id)
{
    Employee newEmployee;
    newEmployee.set_id(++last_id);
    newEmployee.set_salary(salary);
    newEmployee.set_department(department);
    employeeList.push_back(newEmployee);
}
void updateEmployee(list<Employee> &employeeList, int id, int salary, int department_id)
{
    bool found = false;
    list<Employee>::iterator iObject;
    for (iObject = employeeList.begin(); iObject != employeeList.end(); ++iObject)
    {
        Employee &emp(*iObject);
        if (emp.get_id() == id)
        {
            found = true;
            emp.set_salary(salary);
            emp.set_department(department_id);
            break;
        }
    }
    if (!found)
    {
        cout << "ERROR: An invalid ID to update";
    }
}
void deleteEmployee(list<Employee> &employeeList, int id)
{
        bool found = false;
        list<Employee>::iterator iObject;
        for (iObject = employeeList.begin(); iObject != employeeList.end(); ++iObject)
        {
            Employee &emp(*iObject);
            if (emp.get_id() == id)
            {
                found = true;
                employeeList.erase(iObject);
                break;
            }
        }
        if (!found)
        {
            cout << "ERROR: An invalid ID to delete";
        }
    
}
void writeListtoNewFile(list<Employee> employeeList)
{
    ofstream file;
    file.open("list_solution.csv");
    file << "Employee_ID;Salary;Department"
         << "\n";
        list<Employee>::iterator iObject;
        for (iObject = employeeList.begin(); iObject != employeeList.end(); ++iObject)
        {
            Employee &emp(*iObject);
        file << emp.get_id() << ";" << emp.get_salary() << ";" << emp.get_department() << "\n";

        }
    file.close();
}

int main(int argc, char **argv)
{
    //clock_t start = clock();
    int last_id = 0;
    string line, line_info;
    string type, req_id, new_sal, new_dep;
    list<Employee> employeeList;
    readFileandSetList(argv[1], employeeList, last_id);
    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            addEmployee(employeeList, stoi(new_sal), stoi(new_dep), last_id);
        }
        else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            updateEmployee(employeeList, stoi(req_id), stoi(new_sal), stoi(new_dep));
        }
        else if (type == "DELETE")
        {
            getline(line_info, req_id);
            deleteEmployee(employeeList, stoi(req_id));
        }
    }
     writeListtoNewFile(employeeList);

    employeeList.clear();
    //clock_t end_of_time = clock();
    //cout<<(double) ( end_of_time - start) * 1000 / CLOCKS_PER_SEC ;
    //2437.94
    return 0;
}