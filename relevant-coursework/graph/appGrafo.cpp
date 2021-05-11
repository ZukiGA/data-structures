//Authors:
//Rafael Alfonso Goméz González - A01733983
//Bryan González Arellano - A01734198
//Date:
//15/11/2020
//File: appGrafo.cpp
//This program makes a graph through a matrix and then it gets passed
//to an adjacency list, it is also posible to print the graph using DFS or
//BSF methods.

//Libraries

#include <bits/stdc++.h>
using namespace std;


//Declaration of strctures
struct Node{
  string data;
  struct Node *next;
  struct Arco *ady;
  int estado;
  int espera;
  int terminado;
};

struct Arco{
  struct Node *vertice;
  struct Arco *next;
};

struct Lista{
  struct Node *data;
  struct Lista *next;
};

//Function that insert a value list into a stack
//Complexity O(1)
void insertarPila(struct Node **h, struct Lista** inicial, struct Lista**final){
  struct Lista *tmp = new Lista;

  tmp -> data = *h;
  tmp -> next = NULL;

  if (*inicial == NULL){
    *inicial = tmp;
    *final = NULL;
  }else{
    tmp -> next = *inicial;
    *inicial = tmp;
  }
}

//Function that insert a value list into a tail
//Complexity O(1)
void insertarCola(struct Node**h, struct Lista **inicial, struct Lista **final){
  struct Lista *tmp = new Lista;

  tmp -> data = *h;
  tmp -> next = NULL;
  if ((*inicial) == NULL){
    (*inicial) = tmp;
    (*final) = tmp;
  }else{
    (*final)  -> next = tmp;
    (*final) = tmp;
  }
}

//Function that prints the graph using the DFS statement
//Complexity O(n)
void DFS(struct Node **h, struct Lista **inicial, struct Lista **final){
  Arco *tmp = new Arco;
  bool boolean = true;
  (*h) -> estado = 1;
  if ((*h)->ady != NULL){
    tmp = (*h)->ady;
    while(tmp != NULL){
      if (tmp -> vertice -> estado == 1) {
        if (tmp -> vertice -> terminado != 1) {
          if ((*h)-> espera != 1)
            return;
        }
      } else {
        DFS(&(tmp -> vertice), &*inicial, &*final);

      } //acabamos :))))
      tmp = tmp -> next;
    }
  }
    (*h)->terminado = 1;
  insertarCola(&*h, &*inicial, &*final);

  if ((*h)->ady != NULL){
    tmp = (*h)->ady;
    while(tmp != NULL){
      if (tmp->vertice->terminado !=1){
        tmp->vertice->espera = 1;
        DFS(&(tmp -> vertice), &*inicial, &*final);
      }
      tmp = tmp -> next;
    }
  }
}

//Function that eliminates a list value from the tail
//Complexity O(1)
Node* eliminarDeCola(struct Lista **inicial, struct Lista **final){
  struct Lista *tmp = new Lista;

  if (*inicial == NULL){
    return NULL;
  }else{
    tmp = *inicial;
    *inicial = (*inicial) -> next;
    tmp -> next = NULL;
    if (*inicial == NULL)
      *final = NULL;
  }
  struct Node *res = tmp -> data;
  delete tmp;

  return res;
}

//Function that turn the state negative, so the nodes restarts
//Complexity O(n^2)
void reiniciarNodos(struct Node **h){
  if(*h != NULL){
    struct Node *tmp = *h;
    while (tmp != NULL){
      tmp -> estado = 0;
      tmp -> terminado = 0;
      tmp = tmp -> next;
    }
  }
}

//Function that print the graph using the BFS statement
//Complexity O(n^2)
void BFS(struct Node  **h, struct Lista **inicial, struct Lista **final){
  struct Node *tmp = eliminarDeCola(&*inicial, &*final);

  if (tmp == NULL)
    return;
  cout << tmp -> data << " ";
  if(tmp -> ady != NULL){
    struct Arco *a = tmp -> ady;
    while (a != NULL){
      if (a -> vertice -> estado == 0){
        insertarCola(&(a->vertice), &*inicial, &*final);
        a -> vertice -> estado = 1;
      }
      a = a -> next;
    }
  }
  BFS(&*h, &*inicial, &*final);
}

//Function that iterates in the graph untill it finds the specify value, and then it calls
//the BSF and DSF functions
//Complexity O(n^2)
void recorrido(struct Node **h, string value, struct Lista **l_inicial, struct Lista **l_final){
  struct Node *tmp = new Node;
  struct Node *tmp_2 = new Node;

  struct Lista *tmpLista_1 = new Lista;
  struct Lista *tmpLista_2 = new Lista;

  tmpLista_1 = *l_inicial;
  tmpLista_2 = *l_final;

  tmp = *h;
  tmp_2 = *h;

  bool condition = false;

  if (*h != NULL)
    while (tmp != NULL){
      if(tmp->data == value)
        break;
      tmp = tmp->next;
      cout << "PASSING" << endl;
    }
    if (tmp == NULL) //NODO NO ENCONTRADO
      cout << "vertice no encontrado" << endl;
    else{
      tmp -> estado = 1;
      insertarCola(&tmp, &*l_inicial, &*l_final);
      BFS(*&h, &*l_inicial, &*l_final);
      reiniciarNodos(*&h);
      delete *l_inicial;
      delete *l_final;
      DFS(&tmp, &tmpLista_1, &tmpLista_2);
      while (tmp_2 != NULL) {
        if (tmp_2->terminado == 0)
          DFS(&tmp_2, &tmpLista_1, &tmpLista_2);
        tmp_2 = tmp_2 -> next;
      }
      cout << endl << endl;
      while (tmpLista_1 != NULL)
          cout << eliminarDeCola(&tmpLista_1, &tmpLista_2) -> data << " ";
      reiniciarNodos(&*h);

    }
  }

//Function that does a push_back of a node
//Complexity O(n)
void nodePushBack(struct Node **h, string dato){
  struct Node *tmp = new Node;
  struct Node *nuevo = new Node;

  nuevo -> next = NULL;
  nuevo -> ady = NULL;
  nuevo -> data = dato;
  nuevo -> estado = 0;
  nuevo -> terminado = 0;


  if (*h == NULL){
    *h = nuevo;
  } else {
    tmp = *h;
    if (tmp -> data == dato)
      return;
    while (tmp -> next != NULL) {
      if (tmp-> next -> data == dato)
        return;
      tmp = tmp -> next;
    }
    tmp -> next = nuevo;
  }
}

//Function that creates the link between two nodes
//Complexity O(1)
void addArc(struct Node **aux_1, struct Node **aux_2, struct Arco **nuevo){
  struct Arco *a;

  if ((*aux_1) -> ady == NULL){
    (*aux_1) -> ady = *nuevo;
    (*nuevo) -> vertice = *aux_2;

  } else {
    a = (*aux_1) -> ady;
    while (a -> next != NULL)
      a = a -> next;
    (*nuevo) -> vertice = *aux_2;
    a -> next = *nuevo;
  }

}

//Function that creates the and verifies the creation of an arc
//Complexity O(n)
void arcPushBack(struct Node **h, string inicial, string final){
  struct Arco *nuevo = new Arco;
  struct Node *aux_1 = new Node;
  struct Node *aux_2 = new Node;

  bool condition_1 = false;

  if (*h == NULL){
    return;
  }else{
    aux_1 = *h;
    aux_2 = *h;
    while(aux_2 != NULL && condition_1 == false){
      if (aux_2 -> data == final)
         condition_1 = true;
      if (condition_1 == false)
        aux_2 = aux_2 -> next;
    }
    if (aux_2 == NULL)
      return;
    while (aux_1 != NULL){
      if (aux_1 -> data == inicial){
        addArc(&aux_1, &aux_2, &nuevo);
        return;
      }
      aux_1 = aux_1 -> next;
      }
    }
    if (aux_1 == NULL)
      return;
}

//Function that converts an integer number to string equivalent
//Complexity O(1)
string conversion(int position){
  string text;
  if (position == 0){
    text.push_back('A');
  }
  if (position == 1){
    text.push_back('B');
  }
  if (position == 2){
    text.push_back('C');
  }
  if (position == 3){
    text.push_back('D');
  }
  if (position == 4){
    text.push_back('E');
  }
  if (position == 5){
    text.push_back('F');
  }
  if (position == 6){
    text.push_back('G');
  }
  if (position == 7){
    text.push_back('H');
  }
  if (position == 8){
    text.push_back('I');
  }
  if (position == 9){
    text.push_back('J');
  }
  if (position == 10){
    text.push_back('K');
  }
  if (position == 11){
    text.push_back('L');
  }
  if (position == 12){
    text.push_back('M');
  }
  if (position == 13){
    text.push_back('N');
  }
  if (position == 14){
    text.push_back('O');
  }
  if (position == 15){
    text.push_back('P');
  }
  if (position == 16){
    text.push_back('Q');
  }
  if (position == 17){
    text.push_back('R');
  }
  if (position == 18){
    text.push_back('S');
  }
  if (position == 19){
    text.push_back('T');
  }
  if (position == 20){
    text.push_back('U');
  }
  if (position == 21){
    text.push_back('V');
  }
  if (position == 22){
    text.push_back('W');
  }
  if (position == 23){
    text.push_back('X');
  }
  if (position == 24){
    text.push_back('Y');
  }
  if (position == 25){
    text.push_back('Z');
  }
  if (position > 25){
    int i = -1;
    while (position>25) {
      position -=26;
      i++;
    }
    text += conversion(i);
    text += conversion(position);
  }
  return text;
}

//Function that prints the graph as an adjacency list
//Complexity O(n)
void printGraph(struct Node **h, int mode, struct Arco **h2) {
  if (*h==NULL)
    return;
  if (mode == 0)
    cout << (*h) -> data;
  if (mode == 1) {
    cout << " - " << (*h) -> data;
    if ((*h2)->next!=NULL and (*h2)->next->vertice!=NULL ) {
      printGraph(&((*h2)->next->vertice),1, &((*h2)->next));
    }
    return;
  }
  if ((*h)->ady!=NULL)
    printGraph(&((*h)->ady->vertice),1,&((*h)->ady));
  cout << endl;
  printGraph(&((*h)->next),0, NULL);
}

//Main function which start all the process and capture of the data
//Complexity O(n^2)
void creation(vector<string> &v, struct Node **h, struct Lista **ini, struct Lista **final){
  string inicio, fin;

  for (int i = 0 ; i < v.size() ; i++){
    for (int j = 0 ; j < v.size() ; j++){
      if(v[i][j] == '1'){
        nodePushBack(&*h, conversion(i));
        arcPushBack(&*h, conversion(i), conversion(j));
        arcPushBack(&*h, conversion(j), conversion(i));
      }
    }
  }


  printGraph(&*h, 0, NULL);
  cout << endl;
  recorrido(&*h, (*h)->data , &*ini, &*final);
  cout << endl;



}

//Main
int main(){
  struct Node *inicio = NULL;
  string tempString, matriz;
  vector<string> v;
  int value;

  struct Lista *inicial = NULL;
  struct Lista *final = NULL;
  cin >> value;
  cin.ignore();

  while (value >= 0){
    getline(cin,tempString);
    matriz = tempString;
    tempString.erase(remove(tempString.begin(),tempString.end(),' '),tempString.end());
    v.push_back(tempString);
    cout<< matriz << endl;
    value--;
  }

  creation(v, &inicio, &inicial, &final);

  return 0;
}
