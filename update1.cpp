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
Patient *head = NULL;

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
    else if (disease == "Bone")
    {
        newNode->doctor = doctors[2];
    }
    else
    {
        newNode->doctor = doctors[1];
    }

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
        cout << "No patient." << endl;
        return;
    }
    while (temp != NULL)
    {
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Disease: " << temp->disease << endl;
        cout << "Doctor: " << temp->doctor << endl;
        cout << "Priority: " << temp->priority << endl;
        cout << "Status: " << temp->status << endl;
        cout << "------------------------" << endl;
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
    {
        cout << "No patients to delete." << endl;
        return;
    }

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
    {
        cout << "Patient not found." << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
    cout << "Patient deleted." << endl;
}

struct QNode
{
    int patientId;
    int priority;
    QNode *next;
};

QNode *front = NULL;
QNode *rear = NULL;

void enqueue(int id)
{
    Patient *p = findPatient(id);
    if (p == NULL)
    {
        cout << "Patient not found." << endl;
        return;
    }

    QNode *newNode = new QNode();
    newNode->patientId = id;
    newNode->priority = p->priority;
    newNode->next = NULL;

    if (front == NULL)
    {
        front = rear = newNode;
    }
    else if (newNode->priority < front->priority)
    {
        newNode->next = front;
        front = newNode;
    }
    else
    {
        QNode *temp = front;
        while (temp->next != NULL && temp->next->priority < newNode->priority)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next == NULL)
        {
            rear = newNode;
        }
    }
    cout << "Patient added to queue." << endl;
}




void dequeue()
{
    if (front == NULL)
    {
        cout << "Queue empty." << endl;
        return;
    }

    QNode *temp = front;
    Patient *p = findPatient(temp->patientId);
    if (p != NULL)
    {
        p->status = "Treated";
    }

    front = front->next;
    if (front == NULL)
    {
        rear = NULL;
    }

    cout << "Patient ID " << temp->patientId << " sent for treatment." << endl;
    delete temp;
}

void showQueue()
{
    QNode *temp = front;
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

// ================= STACK FOR UNDO =================

struct SNode
{
    string action;
    Patient data;
    SNode *next;
};

SNode *top = NULL;

void push(string action, Patient p)
{
    SNode *newNode = new SNode();
    newNode->action = action;
    newNode->data.id = p.id;
    newNode->data.name = p.name;
    newNode->data.age = p.age;
    newNode->data.disease = p.disease;
    newNode->data.priority = p.priority;
    newNode->data.doctor = p.doctor;
    newNode->data.status = p.status;
    newNode->data.next = NULL;
    newNode->next = top;
    top = newNode;
}

void pop()
{
    if (top == NULL)
    {
        cout << "No actions to undo." << endl;
        return;
    }

    SNode *temp = top;

    if (temp->action == "Added")
    {
        deletePatient(temp->data.id);
        cout << "Undo Add Successful." << endl;
    }
    else if (temp->action == "Deleted")
    {
        addPatient(temp->data.id, temp->data.name, temp->data.age, temp->data.disease, temp->data.priority);
        Patient *restored = findPatient(temp->data.id);
        if (restored != NULL)
        {
            restored->doctor = temp->data.doctor;
            restored->status = temp->data.status;
        }
        cout << "Undo Delete Successful." << endl;
    }

    top = top->next;
    delete temp;
}

// ================= MAIN =================

int main()
{
    int choice;

    while (true)
    {
        cout << "\n===== HOSPITAL SYSTEM =====" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patients" << endl;
        cout << "3. Add to Queue" << endl;
        cout << "4. Treat Patient" << endl;
        cout << "5. Show Queue" << endl;
        cout << "6. Delete Patient" << endl;
        cout << "7. Undo Last Action" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, age, priority;
            string name, disease;
            cout << "Enter ID: ";
            cin >> id;
            if (findPatient(id) != NULL)
            {
                cout << "Patient with this ID already exists!" << endl;
                continue;
            }
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Disease (heart/Bone/other): ";
            cin >> disease;
            cout << "Priority (1 emergency / 2 normal): ";
            cin >> priority;
            addPatient(id, name, age, disease, priority);
            Patient *p = findPatient(id);
            if (p != NULL)
            {
                push("Added", *p);
            }
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
            Patient *p = findPatient(id);
            if (p != NULL)
            {
                push("Deleted", *p);
                deletePatient(id);
            }
            else
            {
                cout << "Patient not found." << endl;
            }
        }
        else if (choice == 7)
        {
            pop();
        }
        else if (choice == 0)
        {
            cout << "Exiting System..." << endl;
            break;
        }
        else
        {
            cout << "Enter correct choice." << endl;
        }
    }

    return 0;
}
