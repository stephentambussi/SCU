/*  
*   Stephen Tambussi
*   COEN379
*   HW6: problem 16.3-5 (from textbook)
*   2/23/23
*
*   This is an implementation of a queue using two stacks
*/
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

stack<int> s1; //enqueue stack
stack<int> s2; //dequeue stack

/* Prints the real queue DS to compare with the stack implementation */
void show_real_queue(queue<int> aq)
{
    queue<int> q = aq;
    cout << "Real Queue DS:\t" << "front ->  ";
    while(!q.empty())
    {
        cout << q.front() << "  ";
        q.pop();
    }
    cout << "<- back" << '\n';
    return;
}

/* Prints the stack queue to compare with the real queue DS */
void show_stack_queue(void)
{
    stack<int> tmp = s1;
    string output;
    cout << "Stack Queue:\t" << "front ->  ";
    while(!tmp.empty())
    {
        output += "  ";
        output += to_string(tmp.top());
        tmp.pop();
    }
    reverse(output.begin(), output.end());
    cout << output;
    cout << "<- back" << '\n';
    return;
}

/* Enqueue operation using stacks */
void enqueue(int value)
{
    s1.push(value);
    return;
}

/* Dequeue operation using stacks */
int dequeue(void)
{
    //every element from s1 needs to be popped and pushed onto s2 before popping top element of s2
    if(s2.empty()) 
    {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }
    //Finally pop the top of s2
    int ret_value = s2.top();
    s2.pop();
    return ret_value;
}

int main(int argc, char **argv)
{
    queue<int> realq;

    /* Testing enqueue */
    
    //First populate real queue with values
    realq.push(1);
    realq.push(2);
    realq.push(3);
    realq.push(4);
    realq.push(5);

    //Then populate stack queue with values
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    //Compare the real queue with the stack queue at this point
    show_real_queue(realq);
    show_stack_queue();

    /* Testing dequeue */
    cout << '\n';
    cout << "         \tReal Queue Front\t" << "Stack Queue Front" << endl;
    
    //dequeue 1
    cout << "dequeue()\t\t" << realq.front() << "\t\t\t" << dequeue() << endl;
    realq.pop();

    //dequeue 2
    cout << "dequeue()\t\t" << realq.front() << "\t\t\t" << dequeue() << endl;
    realq.pop();

    //dequeue 3
    cout << "dequeue()\t\t" << realq.front() << "\t\t\t" << dequeue() << endl;
    realq.pop();

    //dequeue 4
    cout << "dequeue()\t\t" << realq.front() << "\t\t\t" << dequeue() << endl;
    realq.pop();

    //dequeue 5
    cout << "dequeue()\t\t" << realq.front() << "\t\t\t" << dequeue() << endl;
    realq.pop();

    return 0;
}