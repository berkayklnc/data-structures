/*@Author
StudentName: Berkay Kılınç
StudentId: 150210024
Date: 5.12.2023
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
using namespace std;
class Employee
{
private:
    int id;
    int salary;
    int department;
    friend class Node;

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
int readFileandSetTree(string argv, map<int,Employee*> &map, int &last_id)
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
            Employee *newEmployee = new Employee();
            newEmployee->set_id(id);
            newEmployee->set_salary(salary);
            newEmployee->set_department(department);
            map[id]=newEmployee;
            ++last_id;
        };
    }
    else
    {
        cout << "file can not found!";
        return -1;
    }
    infile.close();
    return last_id;
}
void insertEmployee(map<int,Employee*> &map,int id, int salary,int department){
            Employee *newEmployee = new Employee();
            newEmployee->set_id(id);
            newEmployee->set_salary(salary);
            newEmployee->set_department(department);
            map[id]=newEmployee;
}

void printToFile(ofstream &output_file,map<int,Employee*>&Employeemap,int last_id){
    for (int i = 1; i <= last_id; i++)
    {
        if (Employeemap[i]!=nullptr)
        {
                       output_file << Employeemap[i]->get_id() << ";"
                        << Employeemap[i]->get_salary() << ";"
                        << Employeemap[i]->get_department()
                        << "\n";
        }
        
 
    }
    
}
void update(int id,int sal,int dep,map<int,Employee*> &map){
    Employee* emp=map[id];
    if (emp == nullptr)
    {
        cout << "ERROR: An invalid ID to update\n";
    }
    else{
    emp->set_salary(sal);
    emp->set_department(dep);

    }
    
}
void remove(int id,map<int,Employee*> &map){
    Employee* emp=map[id];
    if (emp == nullptr)
    {
       cout << "ERROR: An invalid ID to delete\n";
    }
    else{
    delete emp;
    map.erase(id);
    }
}
void deleteMap(map<int,Employee*> &map,int last_id){
    for (int i = 0; i <= last_id; i++)
    {
        if (map[i]!=nullptr)
        {
            delete map[i];
        }
    }
    
}
int main(int argc, char **argv){
    map<int,Employee*> employeeMap;
    int last_id = 0;
    string line, line_info;
    string type, req_id, new_sal, new_dep;
    last_id = readFileandSetTree(argv[1], employeeMap, last_id);

    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            insertEmployee(employeeMap,++last_id,stoi(new_sal),stoi(new_dep));
        }else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            update(stoi(req_id), stoi(new_sal), stoi(new_dep),employeeMap);
        }
        else if (type == "DELETE")
        {
            getline(line_info, req_id);
            remove(stoi(req_id),employeeMap);
        }
        
    }
    //cout<<employeeMap[employeeMap.size()-1];
    ofstream file;
    file.open("output.csv");
   file << "Employee_ID;Salary;Department"
         << "\n";
    printToFile(file,employeeMap,last_id);
    file.close();
    deleteMap(employeeMap,last_id);
    return 0;
}