/*@Author
StudentName: Berkay Kılınç
StudentId: 150210024
Date: 29.10.2023
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h> 

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




int findIndex(Employee *employees, int id, int &numberofEmp){

    for (int i = 0; i<numberofEmp;i++)
    {
        if ( employees[i].get_id() == id)
        {
            return i;
        }
    }
    return -1;
    
}



void readFileandSetArray(Employee *employees,string argv)
{
    ifstream infile(argv);

    int id, salary, department;
    string line;
    int i = 0;
    char d;
    if (infile.is_open())
    {
        getline(infile, line);
        while (infile >> id >> d >> salary >> d >> department && d == ';')
        {
            employees[i].set_id(id);
            employees[i].set_salary(salary);
            employees[i].set_department(department);
            i++;
        };
    }
    else
    {
        cerr << "file can not found!!";
    }
    infile.close();
}

void addEmployee(Employee *employees, int &numberofEmp, int salary, int department,int& end)
{
    numberofEmp++;

    Employee *temp = new Employee[numberofEmp];
    for (int i = 0; i < numberofEmp - 1; i++)
    {
        temp[i] = employees[i];
    }
    temp[numberofEmp - 1].set_id(end+1);
    temp[numberofEmp - 1].set_department(department);
    temp[numberofEmp - 1].set_salary(salary);
    for (int i = 0; i < numberofEmp; i++)
    {
        employees[i]=temp[i];
    }
    end++;
    
}

void updateEmployee(Employee *employees, int &numberofEmp, int id,int salary, int department){
    int indexofEl = findIndex(employees, id, numberofEmp);
    if(indexofEl==-1){
        cout<<"ERROR: An invalid ID to update";
    }
    else{
    employees[indexofEl].set_salary(salary);
    employees[indexofEl].set_department(department);
    }
};
void deleteEmployee(Employee *employees,int &numberofEmp, int id,int end){
    int indexofEl = findIndex(employees, id, numberofEmp);
    if (id>end)
    {
        cout<<"ERROR: There is no Employee";
        
    }else if (indexofEl==-1)
    {
        cout<<"ERROR: An invalid ID to delete";
    }
    
    else{
   for (int i = indexofEl; i < numberofEmp; i++)
    {
        employees[i] = employees[i+1];
    }
        numberofEmp--;
    }
}

void writeArraytoNewFile(Employee *employees, int numberofEmp){
    ofstream file;
    file.open("array_solution.csv");

    file << "Employee_ID;Salary;Department"<< "\n";
    for (int i = 0; i < numberofEmp; i++)
    {
        file << employees[i].get_id()<<";"<< employees[i].get_salary()<<";" << employees[i].get_department()<< "\n";
    }
    
    file.close();
}
int main(int argc, char** argv)
{
    //clock_t start = clock();

    int numberofEmp = 500000;
    string line, line_info;
    string type, req_id, new_sal, new_dep;
    int end=500000;

    Employee *employees = new Employee[numberofEmp];
    readFileandSetArray(employees,argv[1]);
    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            addEmployee(employees, numberofEmp, stoi(new_sal), stoi(new_dep),end);
        }
        else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            updateEmployee(employees, numberofEmp, stoi(req_id), stoi(new_sal), stoi(new_dep));    
        }
        else if (type == "DELETE"){
            getline(line_info, req_id);
            deleteEmployee(employees,numberofEmp,stoi(req_id),end);
        }
    }
    writeArraytoNewFile(employees,numberofEmp);
    delete[] employees;
    //clock_t end_of_time = clock();
    //cout<<(double) ( end_of_time - start) * 1000 / CLOCKS_PER_SEC ;
    //803.271 ms
    return 0;
}