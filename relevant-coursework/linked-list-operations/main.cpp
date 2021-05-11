/*
Author: Bryan González Arellano
ID : A01734198
Creation date: 10/03/20
Modification date: 10/03/20
// File: main.cpp
// Act 2.2 - Operaciones con listas Ligadas
*/

#include <bits/stdc++.h>

using namespace std;

//NODE DECLARATION
struct Node {

	int data; 
	struct Node * next;

};

//void function. Recieves the list and the tmp struct.
//It searchs for the head, and inserts the new element before it.
//Complexity O(n)
void findHead(struct Node * &list, struct Node * &tmp) {

	if (list == NULL) {

		tmp -> next = list; //inserts the new element before the head
		list = tmp; // data is updated
		return;

	}

	findHead(list -> next, tmp); //recursive

}

//void function. It Recieves the list and the new data.
// It inserts the new struct node before the head, at the end of the list.
//Complexity O(n) with the function findHead()
void insertaAlFinal(struct Node * &h, int newData) {
	
	struct Node * tmp = new Node;
	tmp -> data = newData; //assign the value
	findHead(h, tmp); //calling function

}

//void function. It Recieves the linked list.
//It prints every data from the linked list, space by space, in the console.
// Complexity O(n)
void imprime(struct Node * list) {

	if (list == NULL)
		return;

	cout << list -> data << endl;
	imprime(list -> next);

}

//void function. It recieves the linked list and returns the value of the deleted element.
//It deletes the first element of the list, by using a temporal struct.
// Complexity O(1)
int eliminaAlInicio(struct Node * &h) {

	struct Node * tmp = new Node; 
	int dat;
	tmp = h -> next; //assign the next struct of the list to a temporal struct.
	
	dat = h -> data; //stores the value of the element deleted

	h -> next = NULL; //the link of the first element is equal to null
	delete h; // memory is freed

	h = tmp; // the new list is assigned.

	return dat;

}

//void function. Iit recieves the head of the list.
// It stores the data in a linked list of m size
// Complexity O(n)
void inputData(struct Node * &h) {

	int data; //variable
	int m;

	cin >> m; // size

	for (int i = 0; i < m; i++){

		cin >> data; //value
		insertaAlFinal(h, data); //inserts data at the end of the list

	}

}


//void function. It recieves the linked list.
//It reverses the order of the linked list.
//Complexity O(n^2)
void reverse(struct Node * &h) {

	int data; //variable

	if (h == NULL) 
		return;

	data = eliminaAlInicio(h); //data backup
	reverse(h); //recursive
	insertaAlFinal(h, data); //deletes the first element and inserts it at the end

}

//void function. It receives both linked lists.
//It concatenates both lists.
//Complexity O(n)

void concat(struct Node * &hN, struct Node * &hM) {

	if (hN == NULL) {

		delete hN; //memory freed.
		hN = hM; //the head is changed by the other list.
		return;

	} 

	concat(hN -> next, hM); //recursive

}

//boolean function. It recieves both linked lists and returns
// a boolean value
//It checks if two lists are same lenght and same data, if they're
//it returns true, if not returns 0
//Complexity O(n)
bool equals(struct Node * &hM, struct Node * &hN) {

	if (hM == NULL && hN == NULL) //same length or not
		return true;
	else if (hM == NULL || hN == NULL)
		return false; 

	if (hM -> data != hN -> data) //same data or not
		return (false && equals(hM -> next, hN -> next));
	return (true && equals(hM -> next, hN -> next)); //recursive

	
}

//main
int main() {

	struct Node *headM = NULL; //head M list
	struct Node *headN = NULL; //head N list
	bool key;

	unordered_map <int, string> messages; //messages for boolean value
	messages = {{1,"true"},{0,"false"}}; 


	inputData(headM); //stores data in a linked list
	inputData(headN);

	key = equals(headM, headN); //checks if both lists are equals

	reverse(headM); //reverses M list
	imprime(headM); //prints out M list

	reverse(headN);	//reverses N list
	imprime(headN); //prints out N list

	concat(headN, headM); //concatenates both lists
	imprime(headN); //prints out list concatenated

	cout << messages[key] << endl; //prints out the message

	return 0;
}
//end