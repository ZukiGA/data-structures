//Authors:
//Rafael Alfonso Goméz González - A01733983
//Bryan González Arellano - A01734198
//Date:
//28/11/2020
//File: main.cpp
//This program makes a hash table using the id of a car.

#include <bits/stdc++.h>
using namespace std;

#include "Auto.h"

//returns the hash key of a given placa.
//Complexity O(1)
int hashFunctionMain(char placa[7]){
  int position = 0;
  int suma = 0;
  for (int i = 0 ; i < 8 ; i ++){
    suma = suma + placa[i];
  }
  position = suma % 97;
  return position;
}

//void function. Receives the hash table and the object to be inserted.
//Inserts the object into the hash table.
//Complexity O(1), peor caso O(n)
void ins(vector <Auto> &arr, Auto object) {
  int index = object.hashFunctionClass();
  int cont = 0;
  Auto tmp, tmp2;

  if (arr[index].getPlacaString()==object.getPlacaString()){
    cout << "imposible insertar, placa duplicada" << endl;
    return; //implementar
  }
  while(arr[index].getAnio()!=0 and cont<=97){
    if (arr[index].getPlacaString()==object.getPlacaString()){
      cout << "imposible insertar, placa duplicada" << endl;
      return; //implementar
    }
    index++;
    cont++;
    if (index == 97)
      index = 0;
  }
  if (cont>=97)
    cout << "tabla llena, imposible insertar" << endl;
  else
    arr[index] = object;
}

//void function. Receives the hash table and the key of the object.
//Deletes an object with a certain key.
//Complexity O(n), worst case O(n)
void del(vector <Auto> &v, string key) {
  char c[key.size() + 1];
  strcpy(c, key.c_str());
  int i = hashFunctionMain(c);


  bool found = false;
  int cont = 0;
  while(found == false){
    if(v[i].getPlacaString() == key){
      found = true;
      Auto tmp;
      v[i] = tmp;
    }else{
      //LLAMADA A FUNCIONES CONEXIONES
      cont++;
      i++;
      if(i == 97)
        i = 0;
      if (cont == 97) {
        return;
      }
    }
  }


}

//void function. Receives the hash table and the key of the object.
//Looks up for a certain object.
//Complexity O(1), worst case O(n)
void search(vector <Auto> &v, string key) {
  char c[key.size()+1];
  strcpy(c,key.c_str());
  int i = hashFunctionMain(c);

  bool found = false;
  int cont = 0;
  while(found == false){
    if(v[i].getPlacaString() == key){
      found = true;
      cout << v[i] << endl;
    }else{
      //LLAMADA A FUNCIONES CONEXIONES
      cont++;
      i++;
      if(i == 97)
        i = 0;
      if (cont == 97) {
        cout << "dato no encontrado" << endl;
        return;
      }
    }
  }
}

//void function. Receives the hash table.
//Prints out hash table.
//Complexity O(n)
void print(vector <Auto> &arr) {
  for (int i = 0; i<97; i++){
    if (arr[i].getAnio()!=0)
      cout << i  << " " << arr[i] << endl;
    else 
      cout << i << endl;
  }
}


//void function. No parameters, nor returns values.
//It calls a function according to the user's input.
void menu(vector<Auto> &v) {
	int userChoose = 1, data; //variable

  string placa;
  string marca;
  string modelo;
  int anio;

	while (userChoose!=0) {
		cin >> userChoose;
		if (userChoose == 1) {
			cin >> placa;
      cin >> marca;
      cin >> modelo;
      cin >> anio;

      Auto a1(placa, marca, modelo, anio);
			ins(v, a1);
      
		} else if (userChoose == 2) {
      cin >> placa;
			del(v, placa);
    } else if (userChoose == 3) {
			print(v);
      cout << endl;
		} else if (userChoose == 4) {
      cin >> placa;
      search(v, placa);
      cout << endl;
		} else if (userChoose == 0) {
			exit(0);  
		}
	}
}

int main (){
  vector <Auto> arr(97);
  menu(arr);
  return 0;
}
