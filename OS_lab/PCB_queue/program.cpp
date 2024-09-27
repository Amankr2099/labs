#include <iostream>
#include <string>

using namespace std;

struct PCB
{
    int id;
    string state;
    int time;
    PCB *next;

    PCB(int pid, string pstate, int ptime) : id(pid), state(pstate), time(ptime), next(nullptr) {}
} *front = nullptr, *rear = nullptr;

void enqueuePCB()
{
    int id;
    string state;
    int time;
    cout << "Enter id, state, time :" << endl;
    cin >> id >> state >> time;  
    PCB *newPCB = new PCB(id, state, time);

    if (rear == nullptr)
    {
        front = rear = newPCB;
    }
    else
    {
        rear->next = newPCB;
        rear = newPCB;
    }

    cout << "Enqueued PCB with ID: " << newPCB->id << endl;
}

void dequeuePCB()
{
    if (front == nullptr)
    {
        cout << "Queue is empty. Cannot dequeue." << endl;
        return;
    }

    PCB *temp = front;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }
    int deletedpCB = temp->id;
    cout << "Dequeued PCB with ID: " << deletedpCB << endl;
    delete temp;  
}

void display()
{
    if (front == nullptr)
    {
        cout << "Queue is empty." << endl;
        return;
    }
    PCB *temp = front;
    while (temp != nullptr)
    {
        cout << "PCB : " << temp->id << " ";
        temp = temp->next;
    }
    cout << endl; 
}

int main()
{
    char cont;
    int choice;

    do
    {
        cout << "Enter choices : " << endl;
        cout << "1 -> Create PCB" << endl;
        cout << "2 -> Remove PCB" << endl;
        cout << "3 -> Display Ready Queue" << endl;
        cin >> choice;
        if (choice == 1)
        {
            enqueuePCB();
        }
        else if (choice == 2)
        {
            dequeuePCB();
        }
        else if (choice == 3)
        {
            display();
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << "Continue (y/n)? ";
        cin >> cont;
    } while (cont == 'y');

    return 0;
}

