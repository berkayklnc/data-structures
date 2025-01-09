/*@Author
StudentName: Berkay Kılınç
StudentId: 150210024
Date: 5.12.2023
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
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
class Node
{
private:
    Employee *data;
    Node *left;
    Node *right;
    friend class BinaryTree;

public:
    Node(Employee *employee)
    {
        this->data = employee;
        this->left = nullptr;
        this->right = nullptr;
    };
    ~Node()
    {
    }
    Employee *getData()
    {
        return this->data;
    }
    void setData(Employee *newEmployee)
    {
        this->data = newEmployee;
    }
    Node *getLeft()
    {
        return this->left;
    }
    void setLeft(Node *newEmployee)
    {
        this->left = newEmployee;
    }
    Node *getRight()
    {
        return this->right;
    }
    void setRight(Node *newEmployee)
    {
        this->right = newEmployee;
    }
};

class BinaryTree
{
private:
    Node *root;

public:
    BinaryTree()
    {
        root = nullptr;
    };

    void insert(Employee *employee)
    {
        Node *newEmployee = new Node(employee);
        if (root == nullptr)
        {
            root = newEmployee;
        }
        else
        {
            Node *child = root;
            bool found = false;
            while (!found)
            {

                if (child->getData()->get_id() > employee->get_id())
                {
                    if (child->getLeft() != nullptr)
                    {
                        child = child->getLeft();
                    }
                    else
                    {
                        child->setLeft(newEmployee);
                        found = true;
                    }
                }
                else
                {
                    if (child->getRight() != nullptr)
                    {
                        child = child->getRight();
                    }
                    else
                    {
                        child->setRight(newEmployee);
                        found = true;
                    }
                }
            }
        }
    };
    void remove(int id)
    {
        Node *parent = nullptr;
        Node *deletedNode = this->searchNode(id, parent);
        if (deletedNode == nullptr)
        {
            cout << "ERROR: An invalid ID to delete\n";
        }
        else
        {
            Node *replaceNodeParent = deletedNode;
            if (deletedNode->getLeft() == nullptr && deletedNode->getRight() == nullptr)
            {
                if (deletedNode != root)
                {
                    parent->getRight() == deletedNode ? parent->setRight(nullptr) : parent->setLeft(nullptr);
                }
                else
                {
                    root = nullptr;
                }
                delete deletedNode->getData();
                delete deletedNode;
            }
            else if (replaceNodeParent->getRight() != nullptr)
            {
                replaceNodeParent = replaceNodeParent->getRight();
                if (replaceNodeParent->getLeft() != nullptr)
                {
                    while (replaceNodeParent->getLeft()->getLeft() != nullptr)
                    {
                        replaceNodeParent = replaceNodeParent->getLeft();
                    }
                    Node *temp = replaceNodeParent->getLeft();
                    delete deletedNode->getData();
                    deletedNode->setData(temp->getData());

                    replaceNodeParent->setLeft(temp->getRight());
                    delete temp;
                }
                else
                {
                    delete deletedNode->getData();
                    deletedNode->setData(replaceNodeParent->getData());
                    deletedNode->setRight(replaceNodeParent->getRight());
                    delete replaceNodeParent;
                }
            }
            else if (deletedNode->getLeft() != nullptr)
            {
                replaceNodeParent = replaceNodeParent->getLeft();
                if (replaceNodeParent->getRight() != nullptr)
                {
                    while (replaceNodeParent->getRight()->getRight() != nullptr)
                    {
                        replaceNodeParent = replaceNodeParent->getRight();
                    }
                    Node *temp = replaceNodeParent->getRight();

                    delete deletedNode->getData();
                    deletedNode->setData(temp->getData());

                    replaceNodeParent->setRight(temp->getLeft());
                    delete temp;
                }
                else
                {
                    delete deletedNode->getData();
                    deletedNode->setData(replaceNodeParent->getData());
                    deletedNode->setLeft(replaceNodeParent->getLeft());
                    delete replaceNodeParent;
                }
            }
        }
    };
    void update(int id, int sal, int dep)
    {
        Employee *updateEmp = this->search(id);
        if (updateEmp != nullptr)
        {
            updateEmp->set_salary(sal);
            updateEmp->set_department(dep);
        }
        else
        {
            cout << "ERROR: An invalid ID to update\n";
        }
    }
    Employee *search(int id)
    {
        Node *child = root;
        Employee *employeeData = nullptr;
        int error = -1;
        if (child == nullptr)
        {
            return nullptr;
        }

        else
        {
            while (error == -1)
            {

                if (child->data->get_id() == id)
                {
                    error = 0;
                    employeeData = child->data;
                }
                else if (child->getLeft() == nullptr && child->getRight() == nullptr)
                {
                    error = 1;
                }

                else if (child->data->get_id() < id)
                {
                    if (child->getRight() != nullptr)
                    {
                        child = child->getRight();
                    }
                    else
                    {
                        error = 1;
                    }
                }
                else
                {
                    if (child->getLeft() != nullptr)
                    {
                        child = child->getLeft();
                    }
                    else
                    {
                        error = 1;
                    }
                }
            }
        }
        return employeeData;
    };
    int getHeight()
    {
        BinaryTree dup = *this;
        if (dup.root == nullptr)
        {
            return -1;
        }

        if (dup.root->getLeft() == nullptr && dup.root->getRight() == nullptr)
        {
            return 0;
        }
        Node *children[2];
        children[0] = dup.root->getLeft();
        children[1] = dup.root->getRight();
        int height = 0;
        for (int i = 0; i < 2; i++)
        {
            if (children[i] != nullptr)
            {
                dup.root = children[i];
                height = max(height, dup.getHeight());
            }
        }
        return height + 1;
    };
    void printToFile(ofstream &output_file)
    {
        BinaryTree dup = *this;
        if (dup.root == nullptr)
            return;
        Node *leftNode = dup.root->getLeft();
        Node *rightNode = dup.root->getRight();
        Node *temp = dup.root;
        // First recur on left subtree
        dup.root = leftNode;
        dup.printToFile(output_file);

        // Now deal with the node
        if (temp != nullptr)
        {
            output_file << temp->getData()->get_id() << ";"
                        << temp->getData()->get_salary() << ";"
                        << temp->getData()->get_department()
                        << "\n";
        }
        dup.root = rightNode;
        // Then recur on right subtree
        dup.printToFile(output_file);
    };
    void printToConsole()
    {
        BinaryTree dup = *this;
        if (dup.root != nullptr)
        {
            if (dup.root->getRight() == nullptr && dup.root->getLeft() == nullptr)
            {
                cout << dup.root->getData()->get_id() << ";"
                     << dup.root->getData()->get_salary() << ";"
                     << dup.root->getData()->get_department()
                     << "\n";
                return;
            }
            Node *temp = dup.root;
            Node *children[3];
            children[0] = temp->getLeft();
            children[1] = temp->getRight();
            children[2] = temp;
            for (int i = 0; i < 2; i++)
            {
                if (i == 0)
                {
                    cout << temp->getData()->get_id() << ";"
                         << temp->getData()->get_salary() << ";"
                         << temp->getData()->get_department()
                         << "\n";
                }
                if (children[i] != nullptr)
                {
                    dup.root = children[i];
                    dup.printToConsole();
                }
            }
        }
    };
    void deleteTree()
    {
        if (this->root == nullptr)
            return;
        BinaryTree leftTree;
        BinaryTree rightTree;
        leftTree.root = this->root->left;
        rightTree.root = this->root->right;
        leftTree.deleteTree();
        rightTree.deleteTree();

        delete this->root->data;
        delete this->root;
    };
    Node *searchNode(int id, Node *&parent)
    {
        Node *child = root;
        int error = -1;
        Node *employeeNode = nullptr;
        while (error == -1)
        {
            if (child->data->get_id() == id)
            {
                employeeNode = child;
                error = 0;
            }
            else if (child->getLeft() == nullptr && child->getRight() == nullptr)
            {
                error = 1;
            }

            else if (child->data->get_id() < id)
            {
                if (child->getRight() != nullptr)
                {
                    parent = child;
                    child = child->getRight();
                }
                else
                {
                    error = 1;
                }
            }
            else
            {
                if (child->getLeft() != nullptr)
                {
                    parent = child;
                    child = child->getLeft();
                }
                else
                {
                    error = 1;
                }
            }
        }
        return employeeNode;
    };
};
int readFileandSetTree(string argv, BinaryTree &BinaryTree, int &last_id)
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
            BinaryTree.insert(newEmployee);
            ++last_id;
        };
    }
    else
    {
        cout << "file can not found!";
        return 1;
    }
    infile.close();
    return last_id;
}
int main(int argc, char **argv)
{
    BinaryTree tree;
    int last_id = 0;
    string line, line_info;
    string type, req_id, new_sal, new_dep;
    last_id = readFileandSetTree(argv[1], tree, last_id);

    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);

            Employee *newEmployee = new Employee();
            newEmployee->set_id(++last_id);
            newEmployee->set_salary(stoi(new_sal));
            newEmployee->set_department(stoi(new_dep));
            tree.insert(newEmployee);
        }
        else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            tree.update(stoi(req_id), stoi(new_sal), stoi(new_dep));
        }
        else if (type == "DELETE")
        {
            getline(line_info, req_id);
            tree.remove(stoi(req_id));
        }
        else if (type == "PRINT\r" || type == "PRINT")
        {
            cout << "P"
                 << "\n";
            tree.printToConsole();
        }
        else if (type == "HEIGHT\r" || type == "HEIGHT")
        {
            cout << "H " << tree.getHeight() + 1 << "\n";
        }
    }

    ofstream file;
    file.open("output.csv");
    file << "Employee_ID;Salary;Department"
         << "\n";
    tree.printToFile(file);
    file.close();
    tree.deleteTree();
    return 0;
}