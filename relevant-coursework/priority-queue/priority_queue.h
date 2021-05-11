//Authors:
//Rafael Alfonso Goméz González - A01733983
//Bryan González Arellano - A01734198
//Date:
//24/10/2020
//File: priority_queue.h
// This is a class priority_queue based on a vector with some methods
//that push data into the queue, print the data, etc.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//clase
class priority_queue {
private:
	vector <int> q; //attribut
public:
	priority_queue(); //constructor
	void ordena(int); //support functions
	void heapSort();

	void push(int); //methods
	void pop();
	void print();
	void top();
	bool isEmpty();
	void size();
};

priority_queue::priority_queue() {

}

/* Void function where it gets the index of the vector
and verifies if the order is correct by calculating
the max value*/
void priority_queue:: ordena(int i){
  int head = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < q.size() && q[left] > q[head])
    head = left;

  if (right < q.size() && q[right] > q[head])
    head = right;

  if (head != i) {
    swap(q[i], q[head]);
    ordena(head);
  }
}

/* Void function where the vector the heap gets build,
the method sort the data like a selection sort calculating
the higher value and doing a swap*/
void priority_queue:: heapSort() {
    for (int i = q.size() / 2 - 1; i >= 0; i--)
        ordena(i);

    for (int i = q.size() - 1; i >= 0; i--) {

        swap(q[0], q[i]);

        ordena(i);

    }
}


//void function. Recieves the data to be pushed
//Pushes data into the heap
//Complexity O(nlogn) 
void priority_queue:: push(int data) {
  if (count(q.begin(), q.end(), data)) //checks if the data exists
    return;
  else {
    q.push_back(data); //data is pushed
    heapSort(); //this method sorts the heap according to priority
  }

}


//void function.  No parameters, nor returns values.
//Prints out the element to be erased and erases that element
//Complexity O(nlogn)
void priority_queue:: pop() {
  cout << q[0] << endl;
  swap(q[0],q[q.size()-1]);
	q.pop_back();
  heapSort();
}


//Void method. No parameters, nor returns values.
//Prints out the content of the heap
//Complexity O(n)
void priority_queue:: print(){
  for (int i = 0 ; i < q.size() ; i++)
    cout << q[i] << " "; //Prints out each element in the heap
  cout << endl;
}

//Void function.  No parameters, nor returns values.
//Prints out the first element of the heap
//Complexity O(1)
void priority_queue:: top() {
	cout << q[0] << endl;
}


//Bool method. Returns a boolean value.
//Checks if the heap is empty, returns a value according to that.
//Complexity O(1)
bool priority_queue:: isEmpty() {
	if (q.empty()) //checks if is empty
		return false;
	return true;
}

//void method. No parameters, nor returns values.
//Prints out the size of the heap.
//Complexity O(1)
void priority_queue:: size() {

	cout << q.size() << endl; //prints out the size of the heap
}
