// ASU Spring 2022 CSE310 HW#3
// Your Name: Stephen Austria
// ASU ID: 1220159551
// ASU Email address: saustria@asu.edu
// Description: This is the header file, and there are multiple heap functions.
// All of the functions in here will keep using the parameters of MaxHeap				  
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Student will have a unique id
struct Student
{
	int id;
	string firstName, lastName;
	double gpa;
};

//class MaxHeap represents a max heap that contains Student objects. The underline data structure
//is a one dimensional array of Student.
class MaxHeap
{
private:
	struct Student* stuArr;	//an array of Student
	int capacity, size;

public:
	MaxHeap(int capacity);
	~MaxHeap();

	Student* getStuArr();
	int getSize();
	int getCapacity();
	int isFound(int stuId);
	bool heapIncreaseID(int index, Student oneStudentwithNewID);
	bool heapInsert(int id, string firstName, string lastName, double gpa);
	void heapify(int index);
	Student getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacityA)
{
	//the size is initialized
	int size = 0;

	//The stuArr is initialized and the memory was dynamically allocated
	stuArr = new Student[capacityA];
	capacity = capacityA;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	//studentNum is initialized
	int studentNum = 0;
	int a = 0;

	//studentNum will be incremented when an element is deleted
	while (a < size) {
		studentNum++;
		a++;
	}

	//the loop will delete each element
	while (a < size) {
		size--;

		// elements will be shifted to the left one space
		for (int b = a; b < size; b++) {
			stuArr[b] = stuArr[b + 1];
		}
		a++;
	}

	cout << "\nThe number of deleted Students is: " << studentNum << endl;
}

//Finish all the remaining functions according to the project's description

Student* MaxHeap::getStuArr() //accessor stuArr
{
	return stuArr;
}

int MaxHeap::getSize() //accessor size
{
	return size;
}

int MaxHeap::getCapacity() //accessor capacity
{
	return capacity;
}

int MaxHeap::isFound(int stuId)
{
	int f = -1;
	int a = 0;
	if (size == 0) {
		return -1; //return -1 if heap is empty
	}
	else {
		while (a < size) { //loop that will find the matching id
			if (stuArr[a].id == stuId) {
				f = a; //return the matching id
				break;
			}
			a++;
		}
	}
	return f;
}

bool MaxHeap::heapIncreaseID(int index, Student oneStudentwithNewID)
{
	if (index <= size) { // if index and heap are by each other
		stuArr[index] = oneStudentwithNewID; //new student

		while (parent(index) > -1) { //MaxHeap prop
			heapify(parent(index));

			index = parent(index);
		}
		return true;
	}
	else {
		return false;
	}
}

bool MaxHeap::heapInsert(int id, string firstName, string lastName, double gpa)
{
	int a = 0;
	if (isFound(id) == -1) {
		if (size == capacity) {
			
			//memory is reallocated into a temp
			Student* t = new Student[capacity * 2];
			
			//original is copied into temp
			while (a < capacity) {
				t[a] = stuArr[a];
				a++;
			}
			
			//capacity is doubled
			capacity = 2 * capacity;

			//original data deleted
			delete[] stuArr;

			//temp is stored into original
			stuArr = new Student[capacity];
			stuArr = t;
			cout << "\nReach the capacity limit, double the capacity now.\n";
			cout << "\nThe new capacity now is " << capacity << "\n\n";
		}
		//new student is created to the right of the last index
		stuArr[size].firstName = firstName;
		stuArr[size].lastName = lastName;
		
		stuArr[size].id = id;

		stuArr[size].gpa = gpa;

		//size is incremented
		size++;

		//MaxHeap prop
		int index = size - 1;
		while (parent(index) > -1) {
			heapify(parent(index));
			index = parent(index);
		}
		return true;
	}
	else {
		return false;
	}
}

Student MaxHeap::getHeapMax() {
	//accessor for the root of the heap
	return stuArr[0];
}

void MaxHeap::heapify(int index)
{
	
	int lChild = leftChild(index);
	int rChild = rightChild(index);
	int large;	
	
	//if left child is biggest, then set to largest 
	if (lChild <= size && stuArr[lChild].id > stuArr[index].id && stuArr[lChild].id > stuArr[rChild].id) {
		large = lChild;
	}
	//if right child is biggest, then set to largest
	else if (rChild <= size && stuArr[rChild].id > stuArr[index].id && stuArr[rChild].id > stuArr[lChild].id) {
		large = rChild;
	}
	//else parent is biggest, then set to largest
	else {
		large = index;
	}

	//parent and child swapped if parent is smaller
	if (large != index) {
		swap(stuArr[index], stuArr[large]);
		heapify(large);
	}
}


void MaxHeap::extractHeapMax()
{
	//the root is removed, the elements are moved one space to the left
	if (capacity != 0 || size != 0) {
		stuArr[0] = stuArr[size - 1];

		//decrement size
		size--;

		heapify(0);	

	}
	else {
		cout << "\nEmpty heap, can NOT extract max" << endl;
	}
}

int MaxHeap::leftChild(int parentIndex)
{
	//left child 
	int lChild = 2 * parentIndex + 1;
	return lChild;
}

int MaxHeap::rightChild(int parentIndex)
{
	//right child
	int rChild = 2 * parentIndex + 2;
	return rChild;
}

int MaxHeap::parent(int childIndex)
{
	//parent of the child
	int p = childIndex / 2;

	if (childIndex % 2 == 0) {
		p--;
	}
	return p;
}

void MaxHeap::printHeap()
{
	//heap is empty
	if (capacity == 0 || size == 0) {
		cout << "\nEmpty heap, no elements" << endl;
		
	}
	else {
		//prints out the heap capacity
		cout << "\nHeap capacity = " << capacity << endl;

		//prints out the heap size 
		cout << "\nHeap size = " << size << "\n\n";
		for (int i = 0; i < size; i++) {
			cout << left;
			cout << setw(8) << stuArr[i].id
				<< setw(12) << stuArr[i].firstName
				<< setw(12) << stuArr[i].lastName
				<< setw(8) << fixed << setprecision(2) << stuArr[i].gpa << endl;
		}

	}
}
