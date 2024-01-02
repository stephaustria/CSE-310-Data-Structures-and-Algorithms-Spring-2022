// ASU CSE310 Assignment #5 (Spring 2022)
// Name of Author: Stephen Austria
// ASU ID: 1220159551
// Description: A simple linked list that implements a list of Student objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

class LinkedList
{
private:
    struct Student* head;
    int size;      //a variable represents number of Students inside the list
public:
    LinkedList();
    ~LinkedList();
    Student* getHead();
    int getSize();
    bool searchStudent(int stuID);
    bool insertStudent(string firstName, string lastName, int id, double gpa);
    bool deleteStudent(int stuID);
    void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    head = NULL; //head set to null
    size = 0;   //size set to 0
}

//Destructor
LinkedList::~LinkedList()
{
    Student* t = head;

    while (t != NULL) {
        Student* next = t->next;
        delete t;
        t = next;
    }
    head = NULL;
}

Student* LinkedList::getHead()
{
    return head;    //returns the top of list
}

//Return number of Students inside the Linked list
int LinkedList::getSize()
{
    return size;    //returns the size of the list
}

//This function does a linear search on the Student list with the given student ID
//it returns true if the corresponding student is found, otherwise it returns false.
bool LinkedList::searchStudent(int stuID)
{
    Student* t = head;

    while (t != NULL) {
        if (t->id == stuID) {
            return true;
        }
        t = t->next;
    }
    return false;
}

//Insert the parameter Student at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertStudent(string firstName, string lastName, int id, double gpa)
{
    bool truth;
    Student* t = new Student;

    truth = searchStudent(id);

    if (truth == true) {
        return false;
    }
    else {
        t->firstName = firstName;
        t->lastName = lastName;
        t->id = id;
        t->gpa = gpa;
        t->next = head;
        head = t;

        size++;
        return true;
    }
}

//Delete the Student with the given student ID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteStudent(int stuID)
{
    Student* prev = NULL;
    Student* t = head;

    if (t == NULL) {
        return false;
    }
    else {
        if (t->id == stuID) {
            head = head->next;
            delete t;

            size = size - 1;

            return true;
        }
        else {
            while (t != NULL) {
                if (t->id == stuID) {
                    prev->next = t->next;
                    delete t;

                    size = size - 1;

                    return true;
                }

                prev = t;
                t = t->next;
            }
            return false;
        }
    }
}


//This function displays the content of the linked list.
void LinkedList::displayList()
{
    struct Student* temp = head;
    if (head == NULL)
    {
        return;
    }
    else
    {
        while (temp != NULL)
        {
            cout << left << setw(12) << temp->firstName
                << left << setw(12) << temp->lastName
                << right << setw(8) << temp->id
                << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
            temp = temp->next;
        }
    }
}
