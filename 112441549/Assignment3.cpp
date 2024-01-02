//********************************************************************************
// ASU Spring 2022 CSE310 HW#3
// Name: Stephen Austria
// ASU ID: 1220159551
// ASU Email Address: saustria@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include <iostream>
#include <string>

//include the header file here
#include "MaxHeap.h" 

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	string firstName, lastName;
	int id, newID;
	int capacity, index = -1;   //1D array capacity and index
	double gpa;
	bool success = false;

	Student oneStudent;

	//a variable used to represent a MaxHeap object
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
		case 'C':	//create empty Heap with the initial capacity
			cout << "\nPlease enter the heap capacity: ";
			cin >> capacity; //user input of the heap capacity
			heap1 = new MaxHeap(capacity);
			cin.ignore(20, '\n');	//flush the buffer for above capacity entered
			break;

			//delete the heap, call the destructor explicitly. Re-initialize heap1
			//with default capacity 5
		case 'D':
			cout << "\nDelete the heap" << endl;

			heap1->~MaxHeap();
			heap1 = new MaxHeap(5);
			break;

		case 'E':	//Extract the root, remove it from the heap
			if (heap1 != NULL) {
				cout << "\nBefore extract heap max operation:" << endl; //original 
				heap1->printHeap();

				heap1->extractHeapMax();

				cout << "\nAfter extract heap max operation:" << endl; //new
				heap1->printHeap();
				
			}
			else {
				cout << "\nEmpty heap, can NOT extract max" << endl;
			}
			break;

		case 'F':	//Find a Student
			cout << "\nEnter the student ID you want to search: ";
			cin >> id;
			cin.ignore(20, '\n');	//flush the buffer

			if (heap1->isFound(id) != -1) {
				cout << "\nStudent with id: " << id << " is found" << endl;
			}
			else {
				cout << "\nStudent with id: " << id << " is NOT found" << endl;
			}

			break;

		case 'I':	//Insert a Student
			cout << "\nEnter the student first name: ";
			cin >> firstName;

			cout << "\nEnter the student last name: ";
			cin >> lastName;

			cout << "\nEnter the student id: ";
			cin >> id;
			cout << "\nEnter the student gpa: ";
			cin >> gpa;
			cin.ignore(20, '\n');	//flush the buffer

			success = heap1->heapInsert(id, firstName, lastName, gpa);

			if (success != true) {
				cout << "\nDuplicated Student. Not added\n";
				cout << "\nStudent \"" << firstName << " " << lastName << "\" is NOT added\n";
				
			}
			else {
				cout << "\nStudent \"" << firstName << " " << lastName << "\" is added\n";
			}
			break;

		case 'K':	//increase the ID
			cout << "\nEnter the old student id you want to increase: ";
			cin >> id;
			cout << "\nEnter the new id: ";
			cin >> newID;
			cin.ignore(20, '\n');	//flush the buffer
			if (newID <= id) { //prints out error if new id is less than or equal to id 

				cout << "\nIncrease ID error: new id is smaller than current id" << endl;
			}
			else if (heap1->isFound(id) == -1) { //if the old id does not exist

				cout << "\nThe old ID you try to increase does not exist" << endl;

			}
			else if (heap1->isFound(newID) != -1) { //exisisting id
				cout << "\nThe new ID you entered already exist, increase ID operation failed" << endl;
			}
			else {
				index = heap1->isFound(id);

				cout << "\nBefore increase ID operation:" << endl; //array is displayed before the increase
				heap1->printHeap();

				Student* stuArr = new Student[heap1->getCapacity()]; //get the id of the index
				stuArr = heap1->getStuArr();

				oneStudent = stuArr[index];

				oneStudent.id = newID; //new id

				heap1->heapIncreaseID(index, oneStudent);

				cout << "\nStudent with old id: " << id << " is increased to new id: " << newID << endl;
				cout << "\nAfter increase id operation: " << endl;
				heap1->printHeap();
			}

			break;

		case 'M':	//get the maximum node info.
			if (heap1->getSize() == 0 || heap1 == NULL) {
				
				cout << "\nEmpty heap, can NOT get max node" << endl;
				
			}
			else {
				oneStudent = heap1->getHeapMax();

				cout << "\nThe maximum heap node is:" << endl;
				cout << left;
				cout << setw(8) << oneStudent.id
					<< setw(12) << oneStudent.firstName
					<< setw(12) << oneStudent.lastName
					<< setw(8) << fixed << setprecision(2) << oneStudent.gpa << endl;
			}

			break;

		case 'P':	//Print heap contents
			if (heap1 != NULL) {
				heap1->printHeap();
				
			}
			else {
				cout << "\nEmpty heap, no elements" << endl;
			}
			break;

		case 'S':	//HeapSort
			cout << "\nHeap sort. Students will be sorted in increasing order of their IDs" << endl;
			heapSort(heap1);

			heap1 = new MaxHeap(5);
			break;

		case 'Q':	//Quit
			delete heap1;

			break;

		case '?':	//Display Menu
			printMenu();
			break;

		default:
			cout << "Unknown action\n";
			break;
		}
	} while (input1 != 'Q');
	return 0;
}

//************************************************************
//The function displays the menu
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a student by ID\n";
	cout << "I\t\tInsert a student\n";
	cout << "K\t\tIncrease the ID\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}

//***************************************************************************
//Given a max heap, this function sorts all elements in increasing order of
//their IDs. Note: we explicitly separate the HeapSort algorithm with
//its underline MaxHeap data structure. You can put the sorted elements inside
//another array, then print them out.
void heapSort(MaxHeap* oneMaxHeap)
{
	//temp array
	Student* stuArr = new Student[oneMaxHeap->getCapacity()];
	int s = oneMaxHeap->getSize();
	stuArr = oneMaxHeap->getStuArr();

	int a = 0;
	int index = 0;

	//print out format is given as below
	
	//temp array is repositioned
	while (a < s) {
		for (int b = a + 1; b < s; b++) {
			if (stuArr[b].id < stuArr[a].id) {
				swap(stuArr[a], stuArr[b]);
			}
		}
		a++;
	}

	//temp array is printed
	for (index = 0; index < s; index++) {
		cout << left << setw(8) << stuArr[index].id
			<< setw(12) << stuArr[index].firstName
			<< setw(12) << stuArr[index].lastName
			<< setw(8) << fixed << setprecision(2) << stuArr[index].gpa << endl;
	}

	//elements will be moved to the left once
	while (a < oneMaxHeap->getSize()) {
		for (int b = a; b < oneMaxHeap->getSize(); b++) {
			oneMaxHeap[b] = oneMaxHeap[b + 1];
		}
		a++;
	}
}