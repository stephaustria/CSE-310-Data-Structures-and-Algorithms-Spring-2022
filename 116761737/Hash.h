// ASU CSE310 Assignment #5 Spring 2022
// Name of Author: Stephen Austria
// ASU ID: 1220159551
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Hash
{
private:
    LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
    int m;                     //slots number of the hash table
    int num;                //tracks the number of students added to the hashtable
public:
    Hash(int size);
    ~Hash();
    bool hashSearch(string firstName, string lastName, int id);
    bool hashInsert(string firstName, string lastName, int id, double gpa);
    bool hashDelete(string firstName, string lastName, int id);
    int hashLoadFactor();
    void hashDisplay();
    int hashFunction(string key);
};

//constructor
Hash::Hash(int size)
{
    hashTable = new LinkedList[size]; //hashTable initialized to a one dimensional array of size
    m = size; //m is set to size
    num = 0; //number of students 
}

//Destructor
Hash::~Hash()
{
    int a = 0;
    while (a < m) { //deletes linked list from each spot
        hashTable[a].~LinkedList();
        a++;
    }
    delete[] hashTable; //deletes hashTable
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashSearch(string firstName, string lastName, int id)
{
    bool found = false;

    int a = 0;
    while (a < m) { //loop will go through spot and search for linked list
        if (hashTable[a].searchStudent(id)) {
            found = true;
            break;
        }
        a++;
    }

    //prints student info if student found
    if (found == true) {
        cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is found inside the hash table." << endl;
    }
    //prints student info if student not found
    else {
        cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is NOT found inside the hash table." << endl;
    }
    return found;
}

//hashInsert inserts a Student with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string firstName, string lastName, int id, double gpa)
{
    string id_string = to_string(id); // id into string
    int iHash = hashFunction(firstName + lastName + id_string); //index hash to find correct spot for student
    bool iResult;
    iResult = hashTable[iHash].insertStudent(firstName, lastName, id, gpa);

    //adding student with the info
    if (iResult == true) {
        num++;
        return true;
    }
    else {
        return false;
    }
}

//hashDelete deletes a Student with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashDelete(string firstName, string lastName, int id)
{
    string id_string = to_string(id); //int into string 
    int iHash = hashFunction(firstName + lastName + id_string); //index hash to find correct spot for student
    bool iResult = hashTable[iHash].deleteStudent(id);

    //delete student if they are in the list 
    if (iResult == true) {
        num--;
        cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is deleted from hash table." << endl;
        return true;
    }
    else {
        cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is NOT deleted from hash table." << endl;
        return false;
    }
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
    double idealLoadfactor; //ideal load factor
    double actualLoadfactor; //actual load factor
    double pRatio; //performance ratio
    int a = 1;

    idealLoadfactor = num / (double)m; //ideal load factor = number of students in data set / hash table size

    int biggest = hashTable[0].getSize(); //biggest linked list intialized in the first spot

    //loop finds the biggest linked list
    while (a < m) {
        if (hashTable[a].getSize() >= biggest) {
            biggest = hashTable[a].getSize();
        }
        a++;
    }

    actualLoadfactor = biggest; //size of the biggest linked list is the actual load factor
    pRatio = actualLoadfactor / idealLoadfactor; //performance ratio = actual load factor / ideal load factor 

    cout << "\nThe ideal load factor is: " << setprecision(2) << fixed << idealLoadfactor << endl;
    cout << "My hash table real load factor is: " << setprecision(2) << fixed << actualLoadfactor << endl;
    cout << "My hash table performance ratio is: " << setprecision(2) << fixed << pRatio << endl;

    return actualLoadfactor;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    int a = 0;

    //every spot in the hashtable is printed
    while (a < m) {
        cout << "\nHashTable[" << a << "]";

        //will print "empty" if the a spot is empty
        if (hashTable[a].getSize() == 0) {
            cout << " is empty";
        }
        //print the size of the hash table 
        cout << ", size = " << hashTable[a].getSize() << endl;
        hashTable[a].displayList();
        a++;
    }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
    int sKey = 0;
    int c = 0;
    int a = 0;

    //loop will find index by taking each char in the key
    while (a < key.length()) {
        c = int(key[a]);

        c /= m;

        c *= 2;

        c %= m;

        sKey += c;

        a++;
    }
    return sKey % m;
}
