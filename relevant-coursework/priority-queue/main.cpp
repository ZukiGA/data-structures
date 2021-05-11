//Authors:
//Rafael Alfonso Goméz González - A01733983
//Bryan González Arellano - A01734198
//Date:
//24/10/2020
//File: main.cpp
//This program creates a priority queue by a class and performs some operations
//based on user input.

#include "priority_queue.h"
using namespace std;

//void function. No parameters, nor returns values.
//It calls a function according to the user's input.
void menu(priority_queue q) {

	int userChoose = 1, data; //variable


	while (userChoose!=0) {

		cin >> userChoose;

		if (userChoose == 1) {

			cin >> data;
			q.push(data);

		} else if (userChoose == 2) {

			q.pop();

		} else if (userChoose == 3) {

			q.print();

		} else if (userChoose == 4) {

			q.top();

		} else if (userChoose == 5) {

			bool empty;

			empty = q.isEmpty();

			if (empty) //message printed if heap is not empty
				cout << "false" << endl;
			else
				cout << "true" << endl;

		} else if (userChoose == 6) {

			q.size();

		} else {

			userChoose = 0;

		}
	}
}

int main() {
  priority_queue heap; //declaration
  menu(heap); //menu
  return 0;
}
