/**************************


Rafael Alfonso Gomez Gonzalez A01733983
Santiago Hernández Arellano A01730547
Bryan Gonzalez Arellano A01734198

Fecha de creacion: 26/Octubre/2020


Este programa guarda los datos de un archivo de texto en un BST, después realiza un recorrido por inorder convexo y
despliega los primeros 5 datos en consola.
***************************/


//Declaración de las librerías a usar para este programa
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//se crea la estructura de Node, la cual servirá para crear la lista doblemente ligada
struct Node {
  int hour;
  int month;
  int date;
  vector<int> ip;
  string errorMessage;

  struct Node *left;
  struct Node *right;
};

//función que retorna al mes como integer
int monthConversion(string mes){

  vector <string> meses;
  meses.push_back("Jan");
  meses.push_back("Feb");
  meses.push_back("Mar");
  meses.push_back("Apr");
  meses.push_back("May");
  meses.push_back("Jun");
  meses.push_back("Jul");
  meses.push_back("Aug");
  meses.push_back("Sep");
  meses.push_back("Oct");
  meses.push_back("Nov");
  meses.push_back("Dec");

  vector <int> index;
  index.push_back(1);
  index.push_back(2);
  index.push_back(2);
  index.push_back(4);
  index.push_back(5);
  index.push_back(6);
  index.push_back(7);
  index.push_back(8);
  index.push_back(9);
  index.push_back(10);
  index.push_back(11);
  index.push_back(12);

  for (int i = 0; i<12; i++){

    if (meses[i]==mes)
      return index[i];
  }
  return 0;
}

//funcion que retorna al mes como string para poder imprimirlo
string monthConversion(int mes){
  string mesString;
  if (mes == 1)
    mesString = "Jan";
  if (mes == 2)
    mesString = "Feb";
  if (mes == 3)
    mesString = "Mar";
  if (mes == 4)
    mesString = "Apr";
  if (mes == 5)
    mesString = "May";
  if (mes == 6)
    mesString = "Jun";
  if (mes == 7)
    mesString = "Jul";
  if (mes == 8)
    mesString = "Aug";
  if (mes == 9)
    mesString = "Sep";
  if (mes == 10)
    mesString = "Oct";
  if (mes == 11)
    mesString = "Nov";
  if (mes == 12)
    mesString = "Dic";

    return mesString;
}

/*Funcion que se encarga de separar todo el valor en string de los IP y del
mensaje de error, se pasa como parametro dummy ip para asi regresar ambos strings
separados en una funcion */
string separationErrorIP(string info, string &ip){
  string emptyString ("");
  string tmpValue;
  for (int i = 0 ; i < info.size()-1 ; i++){
    if (isdigit(info[i]) == 1 || info[i] == '.' || info[i] == ':' ){
      ip.push_back(info[i]);
    }
    else {
      tmpValue.push_back(info[i+1]);
    }
  }

  return tmpValue;
}

//Funcion que convierte el string de la hora a integer en el formato indicado
int hourConversion(string hour){
  int finalHour = 0;
  string hourString = "";
  hourString = hour.substr(0,2) + hour.substr(3,2) + hour.substr(6,2);
  finalHour = stoi(hourString);
  return finalHour;
}

/*Funcion que recibe un string de ip y separa los respectivos valores en un
vector donde cada posicion representa un espacio del IP sin los puntos*/
vector<int> getValueIP(string &ip){
  vector <int> temporalVector;
  int i = 0;
  while (i < ip.length()) {
    string tmpString;
    while (ip[i] != '.' && ip[i] != ':') {
      tmpString.push_back(ip[i]);
      i++;
    }
    i++;
    temporalVector.push_back(stoi(tmpString));
    }
    return  temporalVector;
}

//struct node method. It recieves the tree and the data.
//Returns the tree with the new data inserted.
//Complexity O(log2n)
struct Node* pushBackFunction(struct Node **h, int month, int date, int hour, vector <int> ip, string errorMessage){
  struct Node *tmp = new Node; //new node


  tmp -> month = month;
  tmp -> date = date;
  tmp -> hour = hour;
  tmp -> ip = ip;
  tmp -> errorMessage = errorMessage;
  tmp -> left = NULL;
  tmp -> right = NULL;

  if (*h == NULL) { //if node is empty, the data will be the root
    (*h) = tmp;
    return tmp;
  }
  
  if ((*h) -> ip == ip) { //si el ip es igual entonces se comparan los siguientes datos

	if ((*h) -> month == month) {//si el mes es igual entonces se comparan los siguientes datos

		if ((*h) -> date == date) { //si el dia es igual entonces se compara la hora

			if (hour < (*h) -> hour) //data is searched in the left side
    			(*h) -> left = pushBackFunction((&(*h) -> left), month, date, hour, ip, errorMessage);
  			else  //data is searched in the right side.
    			(*h) -> right = pushBackFunction((&(*h) -> right), month, date, hour, ip, errorMessage);
  			
		} else {

			if (date < (*h) -> date) //data is searched in the left side
    			(*h) -> left = pushBackFunction((&(*h) -> left), month, date, hour, ip, errorMessage);
  			else //data is searched in the right side.
    			(*h) -> right = pushBackFunction((&(*h) -> right), month, date, hour, ip, errorMessage);

		}
	} else {

		if (month < (*h) -> month) //data is searched in the left side
    	(*h) -> left = pushBackFunction((&(*h) -> left), month, date, hour, ip, errorMessage);
  		else //data is searched in the right side.
    	(*h) -> right = pushBackFunction((&(*h) -> right), month, date, hour, ip, errorMessage);

	}
  } else {
  	if (ip < (*h) -> ip) //data is searched in the left side
    	(*h) -> left = pushBackFunction((&(*h) -> left), month, date, hour, ip, errorMessage);
  	else //data is searched in the right side.
    	(*h) -> right = pushBackFunction((&(*h) -> right), month, date, hour, ip, errorMessage);
  }
  return (*h); //returns the tree updated.
}

/*funcion para cargar los datos a partir del archivo de bitacora.txt
recibe como argumento un double pointer al head y el nombre del archivo a extraer los datos*/
void cargarDatos(struct Node **h, string nombreArchivo_) {
  setbuf(stdin,NULL);
  string month, hour, errorMessage, lecture, ipString, errorMessageTemporal;
  int date, integerHour, integerMonth;

  ifstream archivo (nombreArchivo_);
  while (!archivo.eof()){

    getline(archivo, lecture);
    month = lecture.substr(0,3);

    integerMonth = monthConversion(month);

    date = stoi(lecture.substr(4,5));

    hour = lecture.substr(7,8);
    integerHour = hourConversion(hour);

    errorMessageTemporal = lecture.substr(16, 70);
    errorMessage = separationErrorIP(errorMessageTemporal, ipString);

    // Fecha f1(month, date, integerHour, errorMessage);
    (*h) = pushBackFunction(h, integerMonth, date, integerHour, getValueIP(ipString), errorMessage);
    ipString = "";
  }
}

//Funcion que convierte el valor del dia en su correcto formato
string dateConversionString(string dateString){
  if (dateString.length() == 1){
    return ("0" + dateString + " ");
  }else{
    return (dateString + " ");
  }
}

//Funcion que regresa las horas con sus respectivos 0 y ":"
string hourConversionString(string horaString, int hour){
    if (hour >= 100000){
    horaString = (horaString.substr(0, 2) + ":" + horaString.substr(2,2) + ":" + horaString.substr(4,2) +  " ");
  } else if (hour >= 10000) {
    horaString = ("0"+horaString.substr(0, 1) + ":" + horaString.substr(1,2) + ":" + horaString.substr(3,2) +  " ");
  } else if (hour >= 1000) {
    horaString = ("00:"  + horaString.substr(0,2) + ":" + horaString.substr(2,2) + " ");
  } else if (hour >= 100) {
    horaString = ("00:0" + horaString.substr(0,1) + ":" + horaString.substr(1,2) + " ");
  } else if (hour >= 10) {
    horaString = ("00:00:" + horaString + " ");
  } else {
    horaString = ("00:00:0" + horaString + " ");
  }
  return (horaString);
}


//Función de tipo string. Recibe un nodo del árbol
//Regresa una cadena con los datos de cada estructura
//Complejidad O(1)
string printNode(struct Node *&h) { //impresión de nodo

  string final;
  int value;
  int j = 0;

  final += monthConversion(h->month) + " " + dateConversionString(to_string(h -> date)); //fecha añadida
  final += hourConversionString(to_string(h -> hour),h ->hour);


  for (int i = 0; i<5; i++){ //ip añadida
    if (i != 3 && i != 4)
      final += to_string(h->ip[i]) + '.';
    else if (i == 4)
      final += to_string(h->ip[i]);
    else
      final += to_string(h -> ip[i]) + ":";
  }

  final += " " + h -> errorMessage; //mensaje de error añadido

  return final; //regresa la string

}

//void function. Recieves the tree.
//Makes a traversal in preorder. Displays the traversal.
//Complexity O(n)
void inOrder (struct Node *h, vector <string> &v){
  if ((h) != NULL){
      inOrder ((h) -> right, v);   // Left Root Right
      v.push_back(printNode(h));
      // printNode(h);
      inOrder ((h) -> left, v);
  }else{
    return;// if the tree is empty, nothing to print
  }
}

int main() {
  struct Node *head = NULL; //head

  vector<string> temporal; //temporal vector

  string nombreArchivo = "bitacora.txt"; //carga de archivo
  ifstream archivo (nombreArchivo);
  if (archivo.is_open()) {
    cargarDatos(&head,nombreArchivo);
  }

  inOrder(head, temporal); //inOrderConvexo

  for (int i = 0 ; i < 5 ; i++){ //5 primeras ips
    cout << temporal[i] << endl;
  }


  return 0;
}
