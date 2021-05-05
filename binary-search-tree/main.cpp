//Authors: 
//Rafael Gómez González
//Bryan González Arellano
//IDs:
//A01733983
//A01734198
//Start date: Oct 15, 2020.
//Finish date: Oct 18, 2020.
//The program inserts, deletes and searchs for data in a tree. It also make
//different kinds of traversals, calculates the height of the tree and the level
// in the tree of a node, and displays the ancestors of a node.

#include <iostream>
#include <string>
using namespace std;

//node declaration
struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

//struct node method. It recieves the tree and the data.
//Returns the tree with the new data inserted.
//Complexity O(log2n)
struct Node* insertNewValue(struct Node **h, int newData){
  struct Node *tmp = new Node; //new node

  tmp -> data = newData; //data assigned
  tmp -> left = NULL;
  tmp -> right = NULL;

  if (*h == NULL) { //if node is empty, the data will be the root
    (*h) = tmp;
    return tmp;
  } 
  if ((*h) -> data == newData) { //if the data is already in th tree, nothing changes.
  	return *h;
  } else if (newData < (*h) -> data){ //data is searched in the left side
    (*h) -> left = insertNewValue((&(*h) -> left), newData);
  } else { //data is searched in the right side.
    (*h) -> right = insertNewValue((&(*h) -> right), newData);
  }
  return (*h); //returns the tree updated.
}

//void function. Recieves the tree.
//Makes a traversal in preorder. Displays the traversal.
//Complexity O(n)
void preOrder(struct Node *h){

  if ((h) != NULL) { 
    cout << (h) -> data << " "; // Root Left Right
    preOrder((h) -> left);
    preOrder((h) -> right);
  } else {
    return; // if the tree is empty, nothing to print
  }

}

//void function. Recieves the tree.
//Makes a traversal in preorder. Displays the traversal.
//Complexity O(n)
void inOrder (struct Node *h){
  if ((h) != NULL){
    inOrder ((h) -> left);   // Left Root Right
    cout << (h) -> data << " ";
    inOrder ((h) -> right);
  }else{
    return;// if the tree is empty, nothing to print
  }
}

//void function. Recieves the tree.
//Makes a traversal in preorder. Displays the traversal.
//Complexity O(n)
void postOrder (struct Node *h){
  if ((h) != NULL){
    postOrder ((h) -> left);   // Left Right Root
    postOrder ((h) -> right);
    cout << (h) -> data << " ";
  }else{
    return; // if the tree is empty, nothing to print
  }
}

//void function. It recieves the root of the tree. // Prints out the level by
//It level traversal. 
// Complexity O(n) 
void levelByLevel(struct Node *h) {

  if (h == NULL) //if node is empty, nothing to print. 
    return;

	cout << h -> data << " "; // root

	if (h->left != NULL) // if right and left are empty, nothing to print
    cout << (h -> left) -> data << " "; //left value

  if (h->right != NULL)
    cout << (h -> right) -> data << " "; // right value

  if (h->left != NULL) {
    levelByLevel(h -> left -> left);	//recursive call
	  levelByLevel(h -> left -> right);
  }

  if (h->right != NULL) {
	  levelByLevel(h -> right -> left);
	  levelByLevel(h -> right -> right);
  }

}


//struct Node function. Recieves a tree.
//Returns the smaller value of the right side. (minmay)
//Complexity O(n)
struct Node * minValueNode(struct Node* h)
{
    struct Node* current = new Node; //new node
    current = h; 

    while (current && current->left != NULL) //searchs for the minmay value
        current = current->left;
    return current;
}

//struct node function. Recieves the tree and the data.
//Returns the tree with the specified node deleted.
//Complexity O(log2(n))
struct Node * deleteNode(struct Node *h, int data){

   if (h == NULL) // if the tree is empty, nothing to delete
    return h;

   if (data < h -> data) //if the data searched is bigger or smaller, the correct side is changed
       h->left = deleteNode(h->left, data);
   else if (data > h->data)
       h->right = deleteNode(h->right, data);

   else {

       if (h->left == NULL) { //if a side is empty, the other is changed
           struct Node *tmp = h->right;
           delete h;
           return tmp;
       }
       else if (h->right == NULL) {
           struct Node *tmp = h->left;
           delete h;
           return tmp;
       }
       else { //the minmay value is searched, that is the new root.
         struct Node * tmp = minValueNode (h -> right);
         h -> data = tmp -> data;
         h -> right = deleteNode(h -> right, tmp -> data);
       }
   }
   return h; //returns the updated tree
 }


//bool function. It recieves the tree and the data.
//Returns a boolean false if the node is in the tree and true if it is not
//Complexity O(log2(n))
bool localizarNodo(struct Node * &h, int data) {
  if (h == NULL)
    return true;
  else if (h -> data == data)
    return false;
  else if (h -> data > data)  
    return true && localizarNodo(h -> left, data); 
  return true && localizarNodo(h -> right, data);
}


//void function. Recieves a tree as parameter. 
//It makes different traversals in a tree.
//Complexity O(1)
void traversal(struct Node *head) {

  if (head != NULL) { //if no data, nothing to print

    preOrder (head); //preorder traversal
    cout << endl;
    inOrder (head); //inorder traversal
    cout << endl;
    postOrder(head); //postorder traversal
    cout << endl;
    levelByLevel(head); //levelbyleveltraversal

  }

  cout << endl;

}


//int function. Recieves the tree.
//Returns the height of a tree.
//Complexity O(n)
int height(struct Node *h) {

  int leftSide; //variables
  int rightSide;

  if(h == NULL) //if the tree is empty, function is ended.
    return 0;
  else { 

    leftSide = height(h -> left); //recursive call
    rightSide = height(h -> right);

    if(leftSide > rightSide) //the bigger side is taken
      return leftSide + 1; //then, one is added to the result.
    else
      return rightSide + 1;
  }
}


//void function. It recieves the tree and the data.
//Prints out all the ancestors of a node
//Complexity O(log2(n))
void ancestors(struct Node * &h, int data) {

  if (data < h -> data) { // if the data is smaller or bigger, a node is printes

    cout << h -> data << " ";
    ancestors(h -> left, data);  //recursive call

  } else  if (data > h -> data) {

    cout << h -> data << " ";
    ancestors(h -> right, data); 

  }
} 


//int function. Recieves a tree and an integer.
//Returns the level in which a node is
//Complexity O(log2n)

int  whatLevelamI(struct Node * &h, int data) {

  if (data < h -> data) // if the data is smaller or bigger, 1 is added
    return 1+ whatLevelamI(h -> left, data);  //recursive call
  else  if (data > h -> data)
    return 1 + whatLevelamI(h -> right, data); 
  return 0;
}

//void function. It recieves the root of the tree.
// It makes different functions.
// Complexity O(n)
void inputData(struct Node * &h, int mode) {

	int data; //variable
	int m;
  bool nodeIsThere;

	cin >> m; // size

	for (int i = 0; i < m; i++){

		cin >> data; //value

    if (mode == 1) {

		  insertNewValue(&h, data); //inserts data at the end of the list

    } else if (mode == 2) {

      h = deleteNode(h,data); //deletes data in the tree

    } else if (mode == 3) { 

      nodeIsThere = not localizarNodo(h, data); //searchs if the node exists

      if (nodeIsThere) //If the node is there, the function is called.
        ancestors(h, data); //prints out the ancestors of the node

      cout << endl; // if the node is not in the tree, it just prints out an endline.
    
    } else if (mode == 4) {

      nodeIsThere = not localizarNodo(h, data); //searchs if the node exists

      if (nodeIsThere)
        cout << whatLevelamI(h, data);
      else
        cout << "-1";
      cout << endl;
    
    }
	}

}

//MAIN
int main() {
  struct Node *head = NULL;
  
  inputData(head, 1); //index 1 stores data

  inputData(head, 2); //index 2 deletes data

  traversal(head); //makes different traversals

  cout << height(head) << endl; //prints the height of the tree

  inputData(head, 3); //index 3 finds ancestors

  inputData(head, 4); //index 4 displays level


  return 0;
}
