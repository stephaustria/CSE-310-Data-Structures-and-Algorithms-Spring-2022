// ASU CSE310 Spring 2022 Assignment #1
// Name: Stephen Austria
// ASU ID: 1220159551
// ASU Email address: saustria@asu.edu
// Description:

#include <iostream>
#include <iomanip>          //used to control the format of the output
#include <string>

using namespace std;

//Student represents a student information
struct Student
{
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

//class LinkedList will contains a linked list of Students. This is class definition
class LinkedList
{
private:
    struct Student* head;

public:
    LinkedList();
    ~LinkedList();
    bool findStudent(int studentId);
    bool addStudent(string firstName, string lastName, int studentId, double gpa);
    bool removeById(int studentId);
    bool removeByName(string firstName, string lastName);
    bool changeStudentName(int studentId, string newFullName);
    bool updateStudentGpa(int studentId, double newGpa);
    void printStudentListByLastName(string oneLastName);
    void printStudentList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    Student* cur, * temp;
    cur = head;
    temp = head;

    int StudentCount = 0;

    while (cur != NULL) {
        cur = cur->next;
        delete temp;
        temp = cur;
        StudentCount++;
    }
    cout << "The number of deleted student is: " << StudentCount <<"\n";
}

//A function to identify if the parameterized Student is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findStudent(int studentId)
{
    Student* temp = head;

    while (temp != NULL) {
        if (temp->id == studentId)
            return true;
            temp = temp->next;
        
    }
    return false;
}

//This function creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Students by their names, i.e.
//first by last name, then by first name. Note: each Student has a unique id, but
//may have the same first and last name with another Student. In case two Students have same names
//they should be inserted according to the increasing order of their IDs.
//Return true if it is successfully inserted and false in case of failures.
bool LinkedList::addStudent(string firstName, string lastName, int studentId, double gpa)
{

    if (findStudent(studentId)) {
        cout << "Duplicated Student. Not added\n";
        return false;
    }

    Student* newS = new Student();
    newS->firstName = firstName;
    newS->lastName = lastName;
    newS->id = studentId;
    newS->gpa = gpa;

    Student* temp = head, * c = temp;

    if (head == NULL) {
        head = newS;
        return true;
    }

    while (temp != NULL) {
        if (newS->lastName.compare(temp->lastName) < 0) {
            if (head == temp) {
                head = newS;
                newS->next = temp;
            }
            else {
                c->next = newS;
                newS->next = temp;

            }
            return true;
        }
        else if (newS->lastName.compare(temp->lastName) == 0) {
            if (newS->firstName.compare(temp->firstName) < 0) {
                if (head == temp) {
                    head = newS;
                    newS->next = temp;
                }
                else {
                    c->next = newS;
                    newS->next = temp;
                }
                return true;
            }
            else if (newS->firstName.compare(temp->firstName) == 0) {
                if (newS->id < temp->id) {
                    if (head == temp) {
                        head = newS;
                        newS->next = temp;
                    }
                    else {
                        c->next = newS;
                        newS->next = temp;
                    }

                    return true;

                }
            }
        }

        c = temp;
        temp = temp->next;

    }
    c->next = newS;
    return true;

    
}

//Removes the specified student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int studentId)
{
    Student* temp = head;
    Student* c = NULL;

    if (temp == NULL)
        return false;
    if (temp->id == studentId) {
        head = temp->next;
        return true;
    }
    c = temp->next;

    while (c != NULL && c->id != studentId) {
        temp = temp->next;
        c = c->next;
    }

    if (c == NULL)
        return false;
    if (c->id == studentId) {
        temp->next = c->next;
        return true;
    }
    else
        return false;
}

//Removes the given Student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Students with
//the same first and last name should be removed from the list.
bool LinkedList::removeByName(string firstName, string lastName)
{
    Student* temp = head, * c = temp;
    bool r = false;

    while (temp != NULL) {
        if (temp->lastName.compare(lastName) == 0 && temp->firstName.compare(firstName) == 0) {
            if (temp == head) {
                head = temp->next;
                delete temp;
                temp = head;
            }
            else {
                c->next = temp->next;
                delete temp;
                temp = c->next;
            }
            r = true;
            continue;
        }
        c = temp;
        temp = temp->next;
    }
    if (!r)
        cout << "No such student name found.\n";
    return r;

}

//Modifies the data of the given Student. Return true if it modifies successfully and
//false otherwise. Note: after changing a Student name, the linked list must still be
//in correct alphabetical order.
bool LinkedList::changeStudentName(int studentId, string newFullName)
{
    Student* temp = head;
    string n[2];
    int a = 0;
    int b = 0;

    if (!findStudent(studentId))
        return false;

    while (a < newFullName.length()) {
        if (newFullName[a] == ' ') {
            b++;
            continue;
        }

        n[b] += newFullName[a];
        a++;
    }

    while (temp->id != studentId)
        temp = temp->next;

    double gpa = temp->gpa;

    if (!removeById(studentId))
        return false;

    if (!addStudent(n[0], n[1], studentId, gpa))
        return false;
    return true;

}

bool LinkedList::updateStudentGpa(int studentId, double newGpa)
{
    Student* temp = head;

    if (!findStudent(studentId)) {
        cout << "Student is NOT inside the list, cannot change the gpa.\n";
        return false;
    }

    while (temp->id != studentId)
        temp = temp->next;
    temp->gpa = newGpa;

    return true;

    
}

//Prints all students in the list with the same last name.
void LinkedList::printStudentListByLastName(string oneLastName)
{
    if (head == NULL)
    {
        cout << "The list is empty\n";
        return;
    }

    Student* temp = head;
    bool a = false;

    while (temp != NULL) {
        if (temp->lastName.compare(oneLastName) == 0) {
            cout << left << setw(12) << temp->firstName << left << setw(12) << temp->lastName << right << setw(8) << temp->id << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
            a = true;
        }

        temp = temp->next;
    }
    if (!a)
        cout << "No students with the specified last name found.\n";

}

//Prints all students in the linked list starting from the head node.
void LinkedList::printStudentList()
{
    if (head == NULL)
    {
        cout << "The list is empty\n";
        return;
    }

    Student* temp = head;

    while (temp != NULL) {
        cout << left << setw(12) << temp->firstName
            << left << setw(12) << temp->lastName
            << right << setw(8) << temp->id
            << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
        temp = temp->next;
        
    }
}
