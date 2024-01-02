//************************************************************************
// ASU CSE310 Assignment #6 Spring 2022
// Author: Stephen Austria
// ASU ID: 1220159551
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Student
void getStudentKey(string oneLine, int& id, string& firstName, string& lastName);

//This function used to get all info. of a Student
void getStudentInfo(string oneLine, int& id, string& firstName, string& lastName, double& gpa);

int main()
{
    int id;
    string firstName, lastName;
    double gpa;
    string command, oneLine, token;
    string delimiter = ",";

    int pos = 0;

    //Create a RedBlackTree object
    RedBlackTree* myRBTree = new RedBlackTree();

    do
    {
        getline(cin, oneLine);
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        command = token;
        oneLine.erase(0, pos + delimiter.length());

        if (command.compare("quit") == 0)
        {
            cout << "\nCommand: quit" << endl;

            //call destructor
            delete myRBTree;
            break;
        }
        else if (command.compare("tree_preorder") == 0)
        {
            cout << "\nCommand: tree_preorder" << endl;

            //call the relevant function
            myRBTree->treePreorder();
        }
        else if (command.compare("tree_inorder") == 0)
        {
            cout << "\nCommand: tree_inorder" << endl;

            //call the relevant function
            myRBTree->treeInorder();
        }
        else if (command.compare("tree_postorder") == 0)
        {
            cout << "\nCommand: tree_postorder" << endl;

            //call the relevant function
            myRBTree->treePostorder();
        }
        else if (command.compare("tree_minimum") == 0)
        {
            cout << "\nCommand: tree_minimum" << endl;

            //call the relevant function
            myRBTree->treeMinimum();
        }
        else if (command.compare("tree_maximum") == 0)
        {
            cout << "\nCommand: tree_maximum" << endl;

            //call the relevant function
            myRBTree->treeMaximum();
        }
        else if (command.compare("tree_predecessor") == 0)
        {
            //get student key first
            getStudentKey(oneLine, id, firstName, lastName);
            cout << "\nCommand: tree_predecessor" << endl;

            //call the relevant function
            myRBTree->treePredecessor(id, firstName, lastName);
        }
        else if (command.compare("tree_successor") == 0)
        {
            //get student key first
            getStudentKey(oneLine, id, firstName, lastName);
            cout << "\nCommand: tree_successor" << endl;

            //call the relevant function
            myRBTree->treeSucessor(id, firstName, lastName);
        }
        else if (command.compare("tree_search") == 0)
        {
            //get student info. first
            getStudentKey(oneLine, id, firstName, lastName);
            cout << "\nCommand: tree_search" << endl;

            //call the relevant function
            myRBTree->treeSearch(id, firstName, lastName);
        }
        else if (command.compare("tree_insert") == 0)
        {
            //get Student info. first
            getStudentInfo(oneLine, id, firstName, lastName, gpa);
            cout << "\nCommand: tree_insert" << endl;
            cout << left;
            cout << setw(8) << id
                << setw(12) << firstName
                << setw(12) << lastName
                << setw(10) << fixed << setprecision(2) << gpa;

            //call the relevant function
            myRBTree->treeInsert(id, firstName, lastName, gpa);
        }
    } while (true);  //continue until 'quit'
    return 0;
}

//********************************************************************
//This function from one line, extracts the id, firstName and lastName
//information of a Student
void getStudentKey(string oneLine, int& id, string& firstName, string& lastName)
{
    string delimiter = ",";
    id = stoi(oneLine.substr(0, oneLine.find(delimiter)));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

    firstName = oneLine.substr(0, oneLine.find(delimiter));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

    lastName = oneLine.substr(0, oneLine.find(delimiter));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());
}

//**************************************************************
//This function from one line, get all Student info.
void getStudentInfo(string oneLine, int& id, string& firstName, string& lastName, double& gpa)
{

    string delimiter = ",";
    id = stoi(oneLine.substr(0, oneLine.find(delimiter)));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

    firstName = oneLine.substr(0, oneLine.find(delimiter));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

    lastName = oneLine.substr(0, oneLine.find(delimiter));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());

    gpa = stod(oneLine.substr(0, oneLine.find(delimiter)));
    oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());
}


