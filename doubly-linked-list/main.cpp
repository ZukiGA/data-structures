/**************************
El programa ordena mediante una lista doblemente ligada los datos con respecto
a la ip de manera ascendente en un principio, si estos son iguales el proximo
arugmento a tomar es el mes, si este es igual, se toma el dia y si este es igual
se toma la hora y por ultimo si la hora es la misma se ordenara la lista conforme
a el mensaje de error. Se usa el metodo de buubbleSort para el ordenamiento
de los datos, este tiene la complejidad de  O(n^2) en caso de no estar ordenada
y en el caso de estarlo su complejidad sera de O(n)


Rafael Alfonso Gomez Gonzalez A01733983
Santiago Hernández Arellano A01730547
Bryan Gonzalez Arellano A01734198

Fecha de creacion: 12/Octubre/2020
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

  struct Node *next;
  struct Node *prev;
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
  string emptyString (" ");
  string tmpValue;
  for (int i = 0 ; i < info.size() ; i++){
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

//función que inserta un elemento (nodo) al final de la lista doblemente ligada
void pushBackFunction(struct Node **h, int month, int date, int hour, vector <int> ip, string errorMessage){
  struct Node* tmp = new Node;
  struct Node* last= new Node;

  //se crea el nodo con los atributos deseados
  last -> month = month;
  last -> date = date;
  last -> hour = hour;
  last -> ip = ip;
  last -> errorMessage = errorMessage;
  last -> next = NULL;
  last -> prev = *h;

  //verifica si el head no tiene valores asignados
  if (*h == NULL)
    (*h) = last;
  else{
    tmp = (*h);
    while (tmp -> next != NULL){
      tmp = tmp -> next;
    }
    tmp -> next = last;
  }
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
    pushBackFunction(h, integerMonth, date, integerHour, getValueIP(ipString), errorMessage);
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

//funcion para imprimir la lista doblemente ligada que recibe como argumento un pointer al head
void printList(struct Node *ch){
  string horaString, dateString;
  while (ch != NULL){
    int numP = 0;
    horaString = to_string(ch -> hour);
    dateString = to_string(ch -> date);


    cout << monthConversion(ch -> month) << " ";

    cout << dateConversionString(dateString);

    cout << hourConversionString(horaString, ch -> hour);

    for (int i = 0 ; i < ch->ip.size() ; i++) {
      if (numP < 4) {
        numP++;
        if (numP < 4){
          cout << ch -> ip[i]<<".";
        }else{
          cout << ch -> ip[i];
        }
      } else
        cout << ":" << ch -> ip[i]<<" ";
    }


    cout << ch -> errorMessage << " ";
    cout << endl;
    ch = ch -> next;
  }
}

/*Funcion de ordenamiento bubbleSort de orden O(n^2)
recibe como argumeto el head de la lista doblemente ligada
y toma diferentes criterios para ordenar la lista*/
void bubbleSort (struct Node * &h){
  int swapped;
  struct Node* ntemp;
  struct Node* tail = NULL;

  //si la lista está vacía, termina la funcion
  if (h ==NULL){
    return;
  }
  //ciclo para recorrer la lista y ordenarla de acuerdo a los cirterios
  do {
    swapped = 0;
    ntemp = h;

    while (ntemp->next != tail){
      //compara la ip
      if (ntemp->ip > ntemp->next->ip){
        swap(ntemp->ip, ntemp->next->ip);
        swap(ntemp->hour, ntemp->next->hour);
        swap(ntemp->month, ntemp->next->month);
        swap(ntemp->date, ntemp->next->date);
        swap(ntemp->errorMessage, ntemp->next->errorMessage);
        swapped=1;
      }
      //si las ip's son iguales, compara el mes
      if (ntemp->ip == ntemp->next->ip && ntemp -> month > ntemp -> next -> month){
        swap(ntemp->ip, ntemp->next->ip);
        swap(ntemp->hour, ntemp->next->hour);
        swap(ntemp->month, ntemp->next->month);
        swap(ntemp->date, ntemp->next->date);
        swap(ntemp->errorMessage, ntemp->next->errorMessage);
        swapped=1;
      }
      //si las ip's y el mes son iguales, compara el día
      if (ntemp->ip == ntemp->next->ip && ntemp -> month == ntemp -> next -> month && ntemp->date > ntemp->next->date){
        swap(ntemp->ip, ntemp->next->ip);
        swap(ntemp->hour, ntemp->next->hour);
        swap(ntemp->month, ntemp->next->month);
        swap(ntemp->date, ntemp->next->date);
        swap(ntemp->errorMessage, ntemp->next->errorMessage);
        swapped=1;
      }
      //si las ip's y el mes son iguales, compara el día y la hora
      if (ntemp->ip == ntemp->next->ip && ntemp -> month == ntemp -> next -> month && ntemp->date == ntemp->next->date && ntemp->hour > ntemp->next->hour){
        swap(ntemp->ip, ntemp->next->ip);
        swap(ntemp->hour, ntemp->next->hour);
        swap(ntemp->month, ntemp->next->month);
        swap(ntemp->date, ntemp->next->date);
        swap(ntemp->errorMessage, ntemp->next->errorMessage);
        swapped=1;
      }
      //si todos los parametros previos son iguales, compara el errorMessage
      if (ntemp->ip == ntemp->next->ip && ntemp -> month == ntemp -> next -> month && ntemp->date == ntemp->next->date && ntemp->hour == ntemp->next->hour){
        for(int i=0; i < 30; i++){
          if(ntemp->errorMessage[i] > ntemp->next->errorMessage[i]){
            swap(ntemp->ip, ntemp->next->ip);
            swap(ntemp->hour, ntemp->next->hour);
            swap(ntemp->month, ntemp->next->month);
            swap(ntemp->date, ntemp->next->date);
            swap(ntemp->errorMessage, ntemp->next->errorMessage);
            swapped=1;
          }
        }
      }
      ntemp = ntemp->next;
    }
    tail=ntemp;

  } while (swapped);

}

//funcion para insertar un nodo al inicio de la lista
//se usa parapoder implementar reverse
void insertNode(Node* &h, Node* new_node){
    new_node->prev = NULL;
    new_node->next = h;

    if (h != NULL){
      h->prev = new_node;
    }
    h = new_node;
}

//funcion para invertir la lista doblemente ligada
void reverse(struct Node * &h){
  //si la lista está vacía o sólo hay 1 nodo, termina
  if (!(h) || !((h)->next)){
    return;
  }

  Node* new_head = NULL;
  Node *curr = h, *next;


  while (curr != NULL) {
    //obtiene el pointer al siguiente nodo
    next = curr->next;
    //pasa el nodo curr al inicio de la lista
    insertNode(new_head, curr);
    //se cambia el nodo curr al siguiente
    curr = next;
  }
  h = new_head;
}

//función para imprimir cada uno de los nodos
//Recibe la lista doblemente ligada
void printNode(struct Node *&h) { //impresión de nodo

  cout << monthConversion(h -> month) << " " << dateConversionString(to_string(h -> date));
  cout << hourConversionString(to_string(h -> hour),h ->hour);

  for (int i = 0; i<5; i++){
    if (i != 3 && i != 4)
      cout << h->ip[i]<< '.';
    else if (i == 4)
      cout << h->ip[i];
    else
      cout << h -> ip[i] << ":";
  }
  cout << " "<< h -> errorMessage << endl;
}

//función para buscar ips en el rango de busqueda
//recibe la lista doblemente ligada y los vectores de inicio y fin de busqueda.
void searching(struct Node *&h, vector <int> start, vector <int> end) {
  if (h == NULL) { //cuando se alcanza la cabeza se termina la busqueda

    return;

  } else if (start> end) {

    if (h -> ip <= start && h-> ip >=end) { //si el ip está en el rango de busqueda, se imprime
      printNode(h); //función para imprimir cada nodo
    }

  } else {
    if (h -> ip >= start && h-> ip <=end) { //si el ip está en el rango de busqueda, se imprime
     printNode(h); //función para imprimir cada nodo
   }
  }

  searching(h -> next, start, end); //llamada recursiva
}

//funcion para exportar la lista doblemente ligada a un fichero
void exportarArchivo(struct Node * &h) {

  struct Node *tmp = new Node;
  ofstream archivo;
  archivo.open("SortedData.txt");

  tmp = (h);

  while (tmp != NULL){

    int numP = 0;
    archivo << monthConversion(tmp -> month) + " ";
    archivo << dateConversionString(to_string(tmp -> date ));
    archivo << hourConversionString(to_string(tmp -> hour), tmp ->hour);

    for (int i = 0 ; i < tmp->ip.size() ; i++) {
      if (numP < 4) {
        numP++;
        if (numP < 4){
          archivo << to_string(tmp -> ip[i]) + ".";
        }else{
          archivo << to_string(tmp -> ip[i]);
        }
      } else
        archivo << ":" + to_string(tmp -> ip[i]) + " ";
    }
    archivo << tmp -> errorMessage;

    archivo << "\n";
    tmp = tmp -> next;
  }

  archivo.close();
}

int main() {
  struct Node *head = NULL;
  string startSearching, endSearching;
  string nombreArchivo = "bitacora.txt";
  ifstream archivo (nombreArchivo);
  if (archivo.is_open()) {
    cargarDatos(&head,nombreArchivo);
  }
  bubbleSort(head);
  reverse(head);
  getline(cin, startSearching);
  getline(cin, endSearching);
  searching(head, getValueIP(startSearching), getValueIP(endSearching));

  reverse(head);
  exportarArchivo(head);

  return 0;
}
