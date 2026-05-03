#include <iostream>
#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string disease;
    int priority;
    string doctor;
    string status;

    Patient *next;
};

string doctors[] = {"ali", "ahmed", "abdullah"};
int doctorCount = 3;

Patient *head = NULL;
 //  ! insertion at last 
void addPatient(int id, string name, int age, string disease, int priority)
{

    Patient *newNode = new Patient();
    newNode->id = id;
    newNode->name = name;
    newNode->age = age;
    newNode->disease = disease;
    newNode->priority = priority;
    newNode->status = "Waiting";

    if (disease == "heart")
    {
        newNode->doctor = doctors[0];
    }
    else if (disease == "Bbone")
        newNode->doctor = doctors[2];
    else
        newNode->doctor = doctors[1];

    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Patient *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayPatients()
{
    Patient *temp = head;
    if (temp == NULL)
    {
        cout << "No patient" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout  << temp->id << " " << temp->name
              << " " << temp->disease
              << " " << temp->doctor
              << " " << temp->status << endl;

        temp = temp->next;
    }
}

Patient *findPatient(int id)
{
    Patient *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deletePatient(int id)
{
    if (head == NULL)
        return;

    if (head->id == id)
    {
        Patient *temp = head;
        head = head->next;
        delete temp;
        cout << "Patient deleted." << endl;
        return;
    }

    Patient *curr = head;
    Patient *prev = NULL;

    while (curr != NULL && curr->id != id)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    prev->next = curr->next;
    delete curr;

  
}

struct QNode
{
    int patientId;
    QNode *next;
};

QNode *front = NULL;
QNode *rear = NULL;

void enqueue(int id)
{

    QNode *newNode = new QNode;
    newNode->patientId = id;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

   
}

void dequeue()
{
    if (front == NULL)
    {
        cout << "Queue empty." << endl;
        return;
    }

    QNode *temp = front;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    cout << "Patient ID " << temp->patientId << " sent for treatment." << endl;
    delete temp;
}

void showQueue()
{
    QNode *temp = front;
    cout << "temp: " << temp << endl;
    if (temp == NULL)
    {
        cout << "No waiting patients." << endl;
        return;
    }

    cout << "Waiting Queue: ";
    while (temp != NULL)
    {
        cout << temp->patientId << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

struct SNode
{
    string action;
    SNode *next;
};

SNode *top = NULL;

void push(string action)
{
    SNode *newNode = new SNode();
    newNode->action = action;
    newNode->next = top;
    top = newNode;
}

void pop()
{
    if (!top)
    {
        cout << "No actions to undo." << endl;
        return;
    }

    SNode *temp = top;
    cout << "Undo: " << temp->action << endl;
    top = top->next;
    delete temp;
}


int main()
{
    int choice;

    while (true)
    {
        cout << "\n HOSPITAL SYSTEM " << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patients" << endl;
        cout << " Add to Queue" << endl;
        cout << "4. Treat Patient (Dequeue)" << endl;
        cout << " Show Queue" << endl;
        cout << ". Delete Patient" << endl;
        cout << ". Undo Last Action" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, age, priority;
            string name, disease;

            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Disease (heart/bone/other): ";
            cin >> disease;
            cout << "Priority (1 emergency / 2 normal): ";
            cin >> priority;

            addPatient(id, name, age, disease, priority);
            push("Added patient");
        }
        else if (choice == 2)
        {
            displayPatients();
        }
        else if (choice == 3)
        {
            int id;
            cout << "Enter Patient ID to queue: ";
            cin >> id;
            enqueue(id);
        }
        else if (choice == 4)
        {
            dequeue();
            push("Treated patient");
        }
        else if (choice == 5)
        {
            showQueue();
        }
        else if (choice == 6)
        {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            deletePatient(id);
            push("Deleted patient");
        }
        else if (choice == 7)
        {
            pop();
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            cout << "enter correct ." << endl;
        }
    }

    return 0;
}
