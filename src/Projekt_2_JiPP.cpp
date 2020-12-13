#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

class Employee {
public:
    void setId(string id)
    {
        this->id = id;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setSurname(string surname)
    {
        this->surname = surname;
    }
    void setPosition(string position)
    {
        this->position = position;
    }
    void setDepartmentId(string id)
    {
        departmentId = id;
    }
    string getId()
    {
        return id;
    }
    string getDepartmentId()
    {
        return departmentId;
    }
    string toString()
    {
        return "(Pracownik) ID:" + id + ", Pozycja:" + position + ", Dzial:" + departmentId + ", Imie:" + name + ", Nazwisko:" + surname;
    }

private:
    string id;
    string name;
    string surname;
    string departmentId;
    string position;
};

class HRMS {
public:
    void add(Employee employee, string departmentId, double salary)
    {
        ostringstream ss;
        ss << employees.size();
        employee.setId(ss.str());
        employee.setDepartmentId(departmentId);

        employees.push_back(employee);
        departments[employee.getDepartmentId()].push_back(employee.getId());
        salaries[employee.getId()] = salary;
    }
    void printDepartment(string deparmentId)
    {
        for (int i = 0; i < departments[deparmentId].size(); i++)
            for (int j = 0; j < employees.size(); j++)
                if (employees.at(j).getId() == departments[deparmentId].at(i))
                    cout << employees.at(j).toString() << endl;
    }
    void changeSalary(string employeeId, double salary)
    {
        salaries[employeeId] = salary;
    }
    void printSalaries()
    {
        for (int i = 0; i < employees.size(); i++)
            cout << employees.at(i).toString() << ", " << salaries[employees.at(i).getId()] << " PLN" << endl;
    }
    void printSalariesSorted()
    {
        desc(salaries);
    }

private:
	template <class a, class b>
    void desc(const map<a, b>& map)
    {
        using vt = const typename map<a, b>::value_type*;
        vector<vt> vec(map.size());
        size_t i = 0;
        for (const auto& keyval : map) vec[i++] = &keyval;
        sort(begin(vec), end(vec), [](vt _lhs, vt _rhs) { return _lhs->second > _rhs->second; });
        for (const auto& el : vec) cout << employees.at((stoi(el->first))).toString() << ", " << el->second << " PLN" << endl;
    }
    
    vector<Employee> employees;
    map<string, vector<string> > departments;
    map<string, double> salaries;
};

int main(int argc, char** argv)
{
    HRMS hrms;

    Employee empl;
    empl.setName("Jan");
    empl.setSurname("Kowalski");
    empl.setPosition("Technik");
    empl.setDepartmentId("1");
    
    hrms.add(empl, "Departament1", 2300);
    hrms.add(empl, "Departament1", 1600);
    hrms.add(empl, "Departament1", 2500);
    hrms.add(empl, "Departament2", 1900);
    hrms.add(empl, "Departament2", 2200);
    hrms.add(empl, "Departament2", 1100);
    hrms.add(empl, "Departament3", 3100);
    hrms.add(empl, "Departament3", 2500);
    hrms.add(empl, "Departament3", 1800);
    hrms.add(empl, "Departament3", 600);
    
    cout << endl << "Metoda printDepartment():" << endl << endl;
    hrms.printDepartment("Departament2"); 
       
    cout << endl << "Metoda printSalaries():" << endl << endl;
    cout<<"Zarobki pracownikow wszystkich dzialow"<<endl;
    hrms.printSalaries();
    
    cout << endl << "Metoda printSalariesSorted():" << endl << endl;
    cout << endl << "Wynagrodzenia pracownikow wraz z informacjami o nich, w kolejnosci malejacego wynagrodzenia:" << endl << endl;
    
    hrms.printSalariesSorted();
    cout << endl << "Wywoalana metoda changeSalary() [...] dla niektorych pracownikow" << endl << endl;
    
    hrms.changeSalary("0",1500);
    hrms.changeSalary("1",1760);
    hrms.changeSalary("2",3300);
    hrms.changeSalary("3",3150);
    
    cout << endl << "Zmiana wynagrodzenia nastapila dla pracownika o ID = 0,1,2,3:" << endl << endl;
    
    hrms.printSalaries();
    
    return 0;
}
