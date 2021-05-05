//Authors:
//Rafael Alfonso Goméz González - A01733983
//Bryan González Arellano - A01734198
//Date:
//14/11/2020
//File: main.cpp
//This program makes a graph through an adjacent list, checks if it is a tree and prints out
//its topological sort

#include <bits/stdc++.h>

using namespace std; 


//NODE DECLARATION
struct Node {

	string data; 
	int degree;
	struct Node * next;
	struct Node * adj;

};

//AUXILIAR FUNCTIONS LOAD GRAPH-------------------------------------------------


//string function. Recieves an integer
//Returns the string that corresponds to the index in the graph
//Complexity O(1)
string indexNode(int index) {

	int pi = 65;
	string character = "";
	if (index > 25) {
		int multiplo = index/26;
		character += indexNode(multiplo-1);
		index = index-multiplo*26;
	}
	character += char(pi+index);
	return character; //returns string
}

//void function. It recieves the linked list, and the new linked lists.
//Splits the linked list in two lists of the same length.
//Complexity O(n)
void splitList(struct Node *&h, struct Node *&inicial, struct Node *&final){
   struct Node *i; //index
   struct Node *j;

   j = h;
   i = h->next;

   while (i != NULL) {

      i = i->next;

      if (i != NULL) {

         j = j->next; //next node
         i = i->next;

      }
   }

   inicial = h; //first half
   final = j->next; //second half
   j->next = NULL; //head assigned

}

struct Node *mergeSortedLists(struct Node *&inicio, struct Node *&fin){

   struct Node *result = NULL; //new linked list

   if (inicio == NULL) { //
      return fin;
   } else if (fin == NULL) {
      return inicio;
   }

   char c[inicio->data.size() + 1];
   strcpy(c, inicio->data.c_str());
   char d[fin->data.size() + 1];
   strcpy(d, fin->data.c_str());


     if (c < d ) {
       result = inicio;
       result -> next = mergeSortedLists(inicio->next,fin); //recursive call
     } else {
       result = fin;
       result->next = mergeSortedLists(inicio, fin->next);
     }


   return result;
}

/*
Esta función ordena un vector mediante el ordenamiento por unión o merge, el cual es un ordenamiento recursivo.
Recibe como parámetro una lista ligada en desorden.
Divide el vector en dos partes y hace una llamada recursiva para cada uno, finalmente mediante otra función une estos dos vectores.
// Su complejidad es de orden O(nlog2(n)), puesto que las comparaciones disminuyen a la mitad en cada llamada recursiva.
*/
void mergeSort(struct Node *&head){

   struct Node *inicio = NULL; //new heads
   struct Node *fin = NULL;

   if (head == NULL || head -> next == NULL) //stop condition
      return;

   splitList(head, inicio, fin); //Splits the linked list
   mergeSort(inicio); //recursive
   mergeSort(fin);

   head = mergeSortedLists(inicio, fin); //ordered linked list


}

//void function. Recieves the graph, and both vertexes.
// It inserts vertexes into a linked list, and also the adjacent nodes.
// Complexity O(n)
void changeDegree(struct Node * &list, string v) {
	if (list == NULL) { //if the pointer is empty, then the value is inserted
		return;
	}
	if (list -> data == v) { //if the node is already in the graph, then just the adjacent nodes are inserted.
		list -> degree +=1;
		return;
	}
	changeDegree(list->next, v);	//if the node is not found, then the pointer will be the next value in the graph
}

//void function. Recieves the graph, and a vertex.
// It inserts the second vertex into a linked list, and adds the degree of that node.
// Complexity O(1)
void addVertex(struct Node * &list, string v) {
	if (list == NULL){
		struct Node * tmp = new Node;
		tmp -> data = v; //assigns the value
		tmp -> next = NULL; //inserts the new element at the beggining
		tmp -> adj = NULL;
		tmp -> degree = 0; //degree +1, because these node is a destiny
		list = tmp; // updates the list
		return;
	}
	addVertex(list->next, v);


}

//void function. Recieves the graph, and both vertexes.
// It inserts vertexes into a linked list, and also the adjacent nodes.
// Complexity O(n)
void addEdge(struct Node * &list, string v, string v2) {
	if (list == NULL) { //if the pointer is empty, then the value is inserted
		return;
	}
	if (list -> data == v) { //if the node is already in the graph, then just the adjacent nodes are inserted.
			struct Node * edge = new Node;
			edge -> data = v2; //assigns the value
			edge -> next = list->adj; //inserts the new element at the beggining
			edge -> adj = NULL;		
			list -> adj = edge; //adjacent values are assigned		
			return;

	}
	addEdge(list->next, v, v2);	//if the node is not found, then the pointer will be the next value in the graph
	
}


//AUXILIAR FUNCTIONS ISTREE -------------------------------------------------


//Int function. Recieves an adjacent list
//Searchs the number of nodes that have an entry degree of 0 and returns the count of that nodes.
//Complexity O(n)
int areThereManyRoots(struct Node * h) {
	if (h==NULL) 
		return 0;
	if (h->degree == 0) //if degree = 0, then there is a node root
		return 1 + areThereManyRoots(h->next); //recursive call
	return 0 + areThereManyRoots(h->next); //if not, another recursive call 
}

//Int function. Recieves an adjacent list
//Searchs the number of nodes that have an entry degree greater than 1 and returns the count of that nodes.
//Complexity O(n)
int areThereManyParents(struct Node * h) {
	if (h==NULL) 
		return 0;
	if (h->degree > 1) //if degree > 1, then there is node with more than 1 parent
		return 1 + areThereManyParents(h->next);//recursive call
	return 0 + areThereManyParents(h->next);//if not, another recursive call 
}

//AUXILIAR FUNCTIONS TOPOLOGICAL SORT -------------------------------------------------

//Int function. Recieves an adjacent list
//Searchs the number of nodes that have an entry degree of 0 and returns the count of that nodes.
//Complexity O(n)
void nodesDegreeCero(struct Node * h, queue <string> &queueSort) {
	if (h==NULL) 
		return;
	if (h->degree == 0) {//if degree = 0, then there is a node root
		queueSort.push(h->data);
	}
	nodesDegreeCero(h->next, queueSort); //recursive call 
}

//bool function. Recieves the adjacent list and the data to search
//Searchs for the node, decreases its degree by one and returns true if it is equal to 0
//Complexity O(n)
bool whatsMyDegree(struct Node * &h, string data) {
	if (h==NULL)
		return false; 

	if (h->data == data) { //if the node is the one we're searching then
		h->degree -=1; //its degree is reduced by one

		if (h->degree == 0)  //and if that node has a degree of one, then returns true
			return true;
	}
	return whatsMyDegree(h->next, data); //recursive call

}

//void function. Recieves the adjacent list of a node, the queue, a copy of the queue and the graph.
//Adds elements of the adjacent list of a node to the queue if it has some properties.
//Complexity O(n)
void adjacentNodes(struct Node * &h, queue <string> &queueSort, queue <string> queue, struct Node * &h2) {
	bool a = true; //flag

	if (h==NULL) 
		return;
	while (!queue.empty()) {
		if (queue.front()==h->data) //if the element is already in the queue, then the flag is false
			a = a && false;
		else
			a = a && true;
		queue.pop();
	}

	if (a and whatsMyDegree(h2, h->data)) { //if both conditions are true, then the node is inserted in the queue
		queueSort.push(h->data);
	}
	queue = queueSort; //copy of queue is updated
	adjacentNodes(h->next, queueSort, queue, h2); //recursive call
}


//void function. Recieves the graph, the queue and a copy of the graph
//Searchs for the first node in the queue into the graph, then adds its adjacent nodes to the queue.
//Complexity O(n)
void searchNode(struct Node * &h, queue <string> &queueSort, struct Node * &h2) {
	if (h==NULL)
		return;
	if (h->data==queueSort.front()) { //if element is found
		mergeSort(h->adj);
		adjacentNodes(h->adj,queueSort, queueSort, h2); //adjacents nodes are added
		return;
	}

	searchNode(h->next,queueSort, h2); //recursive call
}

//MAIN FUNCTIONS -------------------------------------------------------------

//void function. Recieves the graph, number of vertexes and number of edges.
//Loads the nodes into the graph, also the edges.
//Complexity O(n)
void loadGraph(struct Node * &list, int nVertex, int nEdges) {

	string vertex1, vertex2;

	for (int j = 0; j<nVertex; j++) {
		addVertex(list, indexNode(j)); //vertex is added into the list
	}

	for (int i = 0; i<nEdges; i++) {

	cin >> vertex1; 
	cin >> vertex2;
	addEdge(list, vertex1, vertex2); //first vertex is linked with the second one
	changeDegree(list, vertex2); //incoming degree is updated

	}

}

//bool function. Recieves the adjacent list, the number of vertexes and edges.
//Returns a boolean value of true if DAG is a tree, either case returns false
//Complexity O(1)
bool isTree(struct Node * &list, int nVertex, int nEdges) {
	bool roots, parents;
	if (areThereManyRoots(list)==1) //if the number of roots = 1, then it could be a tree
		roots = true;
	else
		roots = false;
	if (areThereManyParents(list)==0) //if all the nodes have only one parent, then it could be a tree
		parents = true;
	else 
		parents = false;
	return roots && parents; //if both conditions are true, then it is a tree
}

//void function. Recieves the DAG, number of vertexes and number of edges.
//Displays the topological sort of the given DAG.
//Complexity O(n)
void topologicalSort(struct Node * &list, int nVertex, int nEdges) {
	queue <string> topoSort; //queue with the data

	nodesDegreeCero(list, topoSort); //searchs for the nodes with incoming degree of 0, 
	//then are added to the queue
	while (!topoSort.empty()) { //when the queue is empty, the topological sort has finished

		searchNode(list, topoSort, list); //searchs the front node in the queue, adds its adjacent nodes
		cout << topoSort.front() << " ";  //prints every element of the queue
		topoSort.pop();
	}
	cout << "\n";
}

//MAIN PROGRAM
int main() {          
	struct Node *graph = NULL; //head
	int n, m; 

	cin >> n;// NUMBER OF NODES
	cin >> m; //number of edges

	loadGraph(graph, n, m); //graph is loaded

	if (isTree(graph, n, m))
		cout << "true" << endl; //prints the right message
	else
		cout << "false" << endl;

	topologicalSort(graph, n, m); //displays topological sort of DAG
	
	return 0;
}