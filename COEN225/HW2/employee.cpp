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

/* Mem layout in gdb
    0x804b160 <buffer>:     0x00000000      0x00000000      0x00000000      0x00000000
    0x804b170:              0x00000000      0x00000000      0x00000000      0x00000000
    0x804b180 <j1>:         0x08048e68      0x6d616461      0x00000000      0x00000000
    0x804b190 <j1+16>:      0x00000000      0x00000000      0x00000000      0x00000000
    0x804b1a0 <j1+32>:      0x00000000      0x00393032      0x00000000      0x0000c350
    0x804b1b0:              0x00000000      0x00000000      0x00000000      0x00000000
    0x804b1c0 <d1>:         0x08048e78      0x65746570      0x00000072      0x00000000
    0x804b1d0 <d1+16>:      0x00000000      0x00000000      0x00000000      0x00000000  
    0x804b1e0 <d1+32>:      0x00000000      0x00313032      0x00000000      0x000249f0
    0x804b1f0:              0x00000000      0x00000000      0x00000000      0x00000000
    0x804b200 <vp1>:        0x08048e88      0x6e686f6a      0x00000000      0x00000000
    0x804b210 <vp1+16>:     0x00000000      0x00000000      0x00000000      0x00000000
    0x804b220 <vp1+32>:     0x00000000      0x00333231      0x00000000      0x0007a120

    Virtual object memory order
    [vptr][name    (32B)     ][id  (8B)  ][salary]
*/