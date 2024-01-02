// ASU CSE310 Assignment #5 Spring 2022
// Name of Author: Stephen Austria
// ASU ID: 1220159551
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Student
//   object's hash value.
//
//   My hash function will find the index by taking every char in the key,
//   dividing by the size (m), multiplying by 2, and then using mod m,
//   then these are added and modulo again.
//
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//
//   My hash functioned worked well and the performance ratio was less than 3 for every test case
//   Test Case 1: Performance Ratio = 1.67, Longest size = 5
//   Test Case 2: Performance Ratio = 1.59, Longest size = 5
//   Test Case 3: Performance Ratio = 1.54, Longest size = 7
//   Test Case 4: Performance Ratio = 1.85, Longest size = 12
//
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
//
//   How I would reduce the number of collisions if I changed my hash function would be
//   to add more operations so that collisions might be more seprated, so it will minimize
//   the amount if collisions
********************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include "Hash.h"

using namespace std;

//This function used to get a Student key which is the combination of firstName, lastName and id
void getKey(string oneLine, string& firstName, string& lastName, int& id);

int main()
{
    int size = 0;
    int numOfCommand = 0;
    string firstName, lastName;
    int id;
    double gpa;

    //declare any other necessary variables here
    //----
    string oneLine; //to scan in one line for each student insert
    string firstToken;
    string command;
    string delimiter = ",";


    cout << "Enter the size of the hash table: ";
    cin >> size;
    cin.ignore(20, '\n');

    //Instantiate the hash table with the relevant number of slots
    Hash* myHashTable = new Hash(size);

    do {
        //use this do..while loop to repreatly get one line Student info. and extract tokens
        //create one Student object and insert it inside the hashTable until seeing the message
        //"InsertionEnd" to terminate
        getline(cin, oneLine);

        //if "InsertionEnd" is typed into the console then it will break
        if (oneLine.compare("InsertionEnd") == 0) {
            break;
        }

        //first name
        firstName = oneLine.substr(0, oneLine.find(delimiter));
        oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

        //last name 
        lastName = oneLine.substr(0, oneLine.find(delimiter));
        oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

        //id
        id = stoi(oneLine.substr(0, oneLine.find(delimiter)));
        oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());


        //gpa
        gpa = stod(oneLine.substr(0, oneLine.find(delimiter)));
        oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

        //will call hashInsert function to insert the student into the right linked list 
        myHashTable->hashInsert(firstName, lastName, id, gpa);


    } while (true);

    //cout << "\nEnter number of commands: ";   //***need to comment out in submitting
    cin >> numOfCommand;
    cin.ignore(20, '\n');

    //for loop will execute every command until number of commands limit is reached
    for (int i = 0; i < numOfCommand; i++)
    {
        //get one line command, extract the first token, if only one token
        cin >> firstToken;

        //will display the hashTable
        if (firstToken.compare("hashDisplay") == 0)
        {
            myHashTable->hashDisplay(); //takes the hashDisplay function to display the table
        }
        //will show the load factor and performance ratio
        else if (firstToken.compare("hashLoadFactor") == 0)
        {
            myHashTable->hashLoadFactor(); //takes the hashLoadFactor function and will display it
        }
        else  //more than one tokens, check the command name, extract the remaining tokens
        {
            string delimiter = ",";
            int pos = firstToken.find(delimiter);
            string command = firstToken.substr(0, firstToken.find(delimiter));
            int length = delimiter.length();

            if (command.compare("hashSearch") == 0) {
                //erase the command 
                firstToken.erase(0, firstToken.find(delimiter) + length);

                //first name 
                firstName = firstToken.substr(0, firstToken.find(delimiter));
                firstToken.erase(0, firstToken.find(delimiter) + length);

                //last name
                lastName = firstToken.substr(0, firstToken.find(delimiter));
                firstToken.erase(0, firstToken.find(delimiter) + length);

                //id
                id = stoi(firstToken.substr(0, firstToken.find(delimiter)));
                firstToken.erase(0, firstToken.find(delimiter) + length);

                //will search for the students in each spot by using the hashSearch function
                myHashTable->hashSearch(firstName, lastName, id);
            }
            else  if (command.compare("hashDelete") == 0) {

                //erases the command 
                firstToken.erase(0, pos + length);

                //first name 
                pos = firstToken.find(delimiter);
                string token = firstToken.substr(0, pos);
                firstName = token;
                firstToken.erase(0, pos + length);

                //last name 
                pos = firstToken.find(delimiter);
                token = firstToken.substr(0, pos);
                lastName = token;
                firstToken.erase(0, pos + length);

                //id
                pos = firstToken.find(delimiter);
                token = firstToken.substr(0, pos);
                id = stoi(token);
                firstToken.erase(0, pos + length);

                //will delete the student in the right spot by using the hashDelete function
                myHashTable->hashDelete(firstName, lastName, id);
            }

            else {
                cout << "Invalid command" << endl;
            }
        }

    } //end for loop
    return 0;
}

//****************************************************************************************
//Given one line, this function extracts the firstName, lastName, id info. of a Student
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string& firstName, string& lastName, int& id)
{
    string delimiter = ",";
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    string command = token;
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    firstName = token;
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    lastName = token;
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    id = stoi(token);
    oneLine.erase(0, pos + delimiter.length());
}
