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

class EmployeeNode
{
private:
    Employee value;
    EmployeeNode *next;
    friend class EmployeeList;

public:
    void setValue(int id, int salary, int department_id)
    {
        this->value.set_id(id);
        this->value.set_salary(salary);
        this->value.set_department(department_id);
    }
};

class EmployeeList
{
private:
    EmployeeNode *head;
    EmployeeNode *tail;

public:
    EmployeeList()
    {
        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }
    void addEmployee(int salary, int department_id, int &last_id)
    {
        EmployeeNode *newEmployee = new EmployeeNode;
        newEmployee->value.set_id(++last_id);
        newEmployee->value.set_salary(salary);
        newEmployee->value.set_department(department_id);
        newEmployee->next=nullptr;
        if (head == nullptr)
        {
            head = newEmployee;
            tail = newEmployee;
        }
        else
        {
            tail->next = newEmployee;
            tail = newEmployee;

        }
    }
    void updateEmployee(int id, int salary, int department_id)
    {
        bool validID = false;
        EmployeeNode *temp = head;
        while (temp != nullptr)
        {
             if (temp==nullptr)
                    {
                        cout<<"ERROR: There is no Employee";
                        break;
                    }
            if (temp->value.get_id() == id)
            {
                temp->value.set_salary(salary);
                temp->value.set_department(department_id);
                validID = true;
                break;
            }
            temp = temp->next;
        }
        if (!validID)
        {
            cout<<"ERROR: An invalid ID to update";
        }
    }
    void deleteEmployee(int id, int last_id)
    {
        //for size check
       if (head == nullptr)
        {
            cout<<"ERROR: There is no Employee";
        }
        
        else
        {
            EmployeeNode *temp = head;
            //for check of the head node
            if (temp->value.get_id() == id)
            {
                head = temp->next;
                delete temp;
            }
            else
            {
                while (temp != nullptr)
                {
                    //if any employee does not have this id, this id must be invalid
                    //i did it for reduce the big o notation and take all process in one loop
                    if (temp->next==nullptr)
                    {
                        cout << "ERROR: An invalid ID to delete";
                        break;
                    }
                    //i do all process from previous node for same reason
                    if (temp->next->value.get_id() == id)
                    {
                        if (tail == temp->next)
                        {
                            delete temp->next;
                            temp->next = nullptr;
                            tail = temp;
                            break;
                        }
                        else
                        {
                            EmployeeNode *deleter = temp->next;
                            temp->next = temp->next->next;
                            delete deleter;
                        }
                        break;
                    }
                
                    temp = temp->next;
                }
            }
        }
        
    }

    void deleteList()
    {

        EmployeeNode *temp = head;
        while (!isEmpty())
        {
            head = temp->next;
            delete temp;
            temp = head;
        }
        head = nullptr;
        tail = nullptr;
    }

    void writeListtoNewFile(int last_id)
    {
        ofstream file;
        file.open("linked_list_solution.csv");
        file << "Employee_ID;Salary;Department"<< "\n";
        EmployeeNode *temp = head;
        while (temp != nullptr)
        {
            file << temp->value.get_id() << ";" << temp->value.get_salary() << ";" << temp->value.get_department() << "\n";
            temp = temp->next;
        }
        file.close();
        deleteList();
    }
};

int readFileandSetArray(string argv, EmployeeList &employeeList)
{
    int last_id = 0;
    ifstream infile(argv);
    int id, salary, department;
    string line;
    char d;
    if (infile.is_open())
    {
        getline(infile, line);
        while (infile >> id >> d >> salary >> d >> department && d == ';')
        {
            employeeList.addEmployee(salary, department, last_id);
        };
    }
    else
    {
        cout << "file can not found!!";
        return 1;
    }
    infile.close();
    return last_id;
}

int main(int argc, char **argv)
{
    //clock_t start = clock();
    int last_id = 0;
    string line, line_info;
    string type, req_id, new_sal, new_dep;
    EmployeeList employeeList;
    last_id = readFileandSetArray(argv[1], employeeList);

    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            employeeList.addEmployee(stoi(new_sal), stoi(new_dep), last_id);
        }
        else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            employeeList.updateEmployee(stoi(req_id), stoi(new_sal), stoi(new_dep));
        }
        else if (type == "DELETE")
        {
            getline(line_info, req_id);
            employeeList.deleteEmployee(stoi(req_id), last_id);
        }
    }
    employeeList.writeListtoNewFile(last_id);

    //clock_t end_of_time = clock();
    //cout<<(double) ( end_of_time - start) * 1000 / CLOCKS_PER_SEC ;
    // 929.224 ms
    return 0;
}