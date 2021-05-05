
/*
Author: Bryan González Arellano
ID : A01734198
Creation date: 10/02/20
Modification date: 10/02/20
// File: main.cpp
*/

#include <bits/stdc++.h>

using namespace std;

//NODE DECLARATION
struct Node {

	int data; 
	struct Node * next;

};

//void function. Recieves the list and the new data.
// It inserts the new struct node before at the beggining.
// Complexity O(1)
void insertaAlInicio(struct Node * &h, int newData) {

	struct Node * tmp = new Node;
	tmp -> data = newData; //assigns the value
	tmp -> next = h; //inserts the new element at the beggining
	h = tmp; // updates the list

}

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

//void function. Recieves the list and the new data.
// It inserts the new struct node before the head, at the end of the list.
//Complexity O(n) with the function findHead()
void insertaAlFinal(struct Node * &h, int newData) {
	
	struct Node * tmp = new Node;
	tmp -> data = newData; //assign the value
	findHead(h, tmp); //calling function

}

//void function. Recieves the linked list.
//It deletes the first element of the list, by using a temporal struct.
// Complexity O(1)
void eliminaAlInicio(struct Node * &h) {

	if (h == NULL) {

		cout << "ERROR" << endl; // if the list is empty

	} else {

		struct Node * tmp = new Node; 
		tmp = h -> next; //assign the next struct of the list to a temporal struct.
	
		h -> next = NULL; //the link of the first element is equal to null
		delete h; // memory is freed
	
		h = tmp; // the new list is assigned.

	}
}

//int function, recieves the linked list, a new head and the flag c
//It deletes the last element of the list, by using a flag
//Complexity O(n)
int newHead(struct Node * &list, struct Node * &head, int c) {

	if (list == NULL) {

		c = 1; //flag
		return c; //returns value

	}	
		

	c = newHead(list -> next, head, c); //recursive, recieve c = 1 if applies

	if (c == 1) { //element before head

		delete list; //deletes last element and head
		list = head; //updates the list with a new head

	}

	return 0; // no more changes
}


//void function. Recieves the linked list using two pointers.
//It deletes the last element of the list.
//Complexity O(n) with the function newHead()
void eliminaAlFinal(struct Node * &h) {

	if (h == NULL) {

		cout << "ERROR" << endl; // if the list is empty

	} else  {

		struct Node *head = NULL; //new head
		int c = 0; // flag
		c = newHead(h, head, c); //deletes the last element

	}

}

//void function. Recieves the linked list.
//It prints every data from the linked list, space by space, in the console.
// Complexity O(n)
void imprime(struct Node * list) {

	if (list == NULL)
		return;

	cout << list -> data << endl;
	imprime(list -> next);

}





//void function. No parameters, nor return values. 
//It calls a function according to the user's input.
void menu(struct Node * &h) {

	int userChoose = 1, data; //variable


	while (userChoose!=0) {

		cin >> userChoose;

		if (userChoose == 1) {

			cin >> data;
			insertaAlInicio(h, data);

		} else if (userChoose == 2) {

			cin >> data;
			insertaAlFinal(h, data);

		} else if (userChoose == 3) {

			eliminaAlInicio(h);

		} else if (userChoose == 4) {

			eliminaAlFinal(h);

		} else if (userChoose == 5) {

			imprime(h);

		} else {

			userChoose = 0;

		}
	}
}


//MAIN
int main() {

	struct Node *head = NULL; //head

	menu(head); //menu

	return 0;
}