/*  
*   Stephen Tambussi
*   COEN225
*   HW2: problem 2
*   10/18/22
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;

class Employee 
{ 
    protected:
        char name[32];
        char id[8];
        int salary;
    public: 
        Employee(const char*name, const char*id, int salary) 
        {
            strcpy(this->name,name);
            strcpy(this->id,id);
            this->salary = salary;
        }
    virtual void pay() = 0;
    virtual void info() = 0;
};

class President : public Employee 
{ 
    using Employee::Employee;
    public:
        virtual void pay() 
        { 
            cout << name << ", " << salary << "+100,000 bonus will be deposited to the account" << endl;
        } 
        virtual void info() 
        { 
            cout << "Title:President " << name << endl;
        } 
};

class Director : public Employee 
{ 
    using Employee::Employee;
    public:
        virtual void pay() 
        { 
            cout << name << ", " << salary << "+10,000 bonus will be deposited to the account" << endl;
        } 
        virtual void info() 
        { 
            cout << "Title:Director " << name << endl;
        } 
};

class Janitor : public Employee 
{ 
    using Employee::Employee;
    public:
        virtual void pay() 
        { 
            cout << name << ", " << salary << "+0 bonus will be deposited to the account" << endl;
        } 
        virtual void info() 
        { 
            cout << "Title:Janitor " << name << endl;
        } 
};

void showpay(Employee *e)
{
  e->pay(); // e->vptr[0]()
}
void showinfo(Employee *e)
{
  e->info(); // e->vptr[1]()
}

char buffer[16];
Janitor j1("adam","209",50000);
Director d1("peter","201",150000);
President vp1("john","123",500000);

int main()
{
    puts("To view employee info, please enter your name:");
    (void) gets(buffer);
    showpay(&vp1);
    showpay(&d1);
    showpay(&j1);
    showinfo(&vp1);
    showinfo(&d1);
    showinfo(&j1);
}