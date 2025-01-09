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

void addEmployee(string filename, int salary, int department,int &last_id)
{
    fstream fileObj(filename);
    string req_id;
    string line;
    for (int i = 0; getline(fileObj, line); i++){}

    fileObj.clear(fileObj.eofbit);
    fileObj.seekg(0, ios_base::end);


    fileObj << ++last_id << ";" << salary << ";" << department << "\n";
    fileObj.seekg(0, ios_base::beg);
}

void updateEmployee(string filename, int id, int salary, int department)
{
    ifstream fileObj(filename);
    string line, search_id;
    ofstream fileTemp("array_solution_temp.csv");
    bool isFound = false;
    getline(fileObj, line);
    // for setting headers
    fileTemp << line << "\n";
    for (int i = 0; getline(fileObj, line); i++)
    {
        istringstream iss(line);
        getline(iss, search_id, ';');
        if (stoi(search_id) == id)
        {
            fileTemp << stoi(search_id) << ";" << salary << ";" << department << "\n";
            isFound = true;
        }
        else
        {
            fileTemp << line << "\n";
        }
    }
    fileObj.close();
    fileTemp.close();
    if (!isFound)
    {
        cout << "no id found to update"<<"\n";
        remove("array_solution_temp.csv");
    }
    else
    {
        remove(filename.c_str());
        rename("array_solution_temp.csv", filename.c_str());
    }
}
void deleteEmployee(string filename, int id)
{
    bool isFound = false;
    ifstream fileObj(filename);
    string line, search_id;
    ofstream fileTemp("array_solution_temp.csv");

    getline(fileObj, line);
    // for setting headers
    fileTemp << line << "\n";
    for (int i = 0; getline(fileObj, line); i++)
    {
        istringstream iss(line);
        getline(iss, search_id, ';');
        if ((stoi(search_id) != id))
        {
            fileTemp << line << "\n";
        }
        else if (stoi(search_id) == id)
        {
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << "no id found to delete" << '\n';
        remove("array_solution_temp.csv");
    }
    else
    {
        fileObj.close();
        fileTemp.close();
        remove(filename.c_str());
        rename("array_solution_temp.csv", filename.c_str());
    }
}
int main(int argc, char** argv)
{
    //clock_t start = clock();

    string file_name = argv[1];
    string line, line_info;
    int last_id= 500000;
    string type, req_id, new_sal, new_dep;
    ifstream read(argv[2]);
    while (getline(read, line))
    {
        istringstream line_info(line);
        getline(line_info, type, ';');
        if (type == "ADD")
        {
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            addEmployee(file_name, stoi(new_sal), stoi(new_dep),last_id);
        }
        else if (type == "UPDATE")
        {
            getline(line_info, req_id, ';');
            getline(line_info, new_sal, ';');
            getline(line_info, new_dep);
            updateEmployee(file_name, stoi(req_id), stoi(new_sal), stoi(new_dep));
        }
        else if (type == "DELETE")
        {
            getline(line_info, req_id);
            deleteEmployee(file_name, stoi(req_id));
        }
    }
    //clock_t end = clock();
    //cout<<(double) ( end - start) * 1000 / CLOCKS_PER_SEC ;
    //1859.56 ms
    return 0;
}
