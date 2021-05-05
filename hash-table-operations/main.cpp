/*Tecnologico de Monterrey Campus Puebla
El programa calcula los nodos que tengan un mayor numero de conexiones,
tanto para nodos red como para nodos host. La lectura es a partir de un
archivo txt y la impresion solo sera de los valores de las IP
Rafael Alfonso Gomez Gonzalez A07133983
Santiago Hernandez Arellano A01730547
Bryan González Arellano A01734198
Fecha 29/11/20*/

//Declaracion de las librerías a usar para este programa
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//Declaracion de estructuras
struct Red{
  string firstIP;
  int connections;
  struct Red *next;
  struct Host *binding;
};

struct Host{
  string secondIp;
  int connections;
  struct Host *next;
  struct Data *binding;

};

struct Data{
  string data;
  struct Data *next;
};

/*Funcion que se encarga de separar todo el valor en string de los IP y del
mensaje de error, se pasa como parametro dummy ip para asi regresar ambos strings
separados en una funcion
Complejidad O(n)*/
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

/*Funcion que se encarga de separar la ip en 2 strings para asi agregarlas
en los nodos correspondientes de Red y Host
Complejidad O(n^2)*/
string separationIP(string info, string &ip_2){
  string ip_1 = "", tmpString = "";
  vector <string> temporalVector;
  int i = 0;
  while (i < info.length()) {
    tmpString = "";
    while (isdigit(info[i])) {
      tmpString += info[i];
      i++;
    }
     i++;
     tmpString = to_string(stoi(tmpString));
     temporalVector.push_back(tmpString);
  }
  ip_1 = temporalVector[0] + '.' + temporalVector[1];
  ip_2 = '.' + temporalVector[2] + '.' +  temporalVector[3];
  return ip_1;
}

/*funcion para guardar los datos, no regresa nada
Complejidad O(n)*/
void saveData(struct Data * &h, string data) {
  if (h == NULL) { //if the pointer is empty, then the value is inserted
    struct Data * tmp = new Data;
    tmp -> data = data;
    tmp -> next = h;
    h = tmp;
    return;
  } else {
    if (h -> data == data) { //if the node is already in the graph, then just the adjacent nodes are inserted.
    return;
    } else {
      saveData(h->next, data); //if the node is not found, then the pointer will be the next value in the graph
    }
  }
}

/*funcion para guardar los datos del host, llama a la función que guarda
los datos, no regresa nada.
Complejidad O(n)*/
void saveHost(struct Host * &h, string ip2, string data) {
  if (h == NULL) { //if the pointer is empty, then the value is inserted
    struct Host * tmp = new Host;
    tmp -> secondIp = ip2;
    tmp -> connections = 0;
    tmp -> next = h;
    tmp -> binding  = NULL;
    saveData(tmp->binding, data);
    h = tmp;
    return;
  } else  {
    if (h -> secondIp == ip2) { //if the node is already in the graph, then just the adjacent nodes are inserted.
      saveData(h->binding, data);
      return;
    } else {
      saveHost(h->next, ip2, data); //if the node is not found, then the pointer will be the next value in the graph
    }
  }
}

//int function. Receives a char.
//Returns an index for a single char
//Complexity O(n)
int hashT(char *input) {
    int result = 0x55555555;

    while (*input) {
        result ^= *input++;
        result = result>>5+result<<5;
    }
    return result;
}

//int function. Receives a string with the key.
//Returns the index for a given ip.
//Complexity O(n)
int hashFunction(string ip){

  int position = 0;
  int suma = 0;

  for (int i = 0; i<ip.size(); i++) {
    suma += hashT(&ip[i]);
  }
  position = suma % 32749;
  return position;
}

//bool function. Recieves the hashtable and an index
//Returns false if there's no more space in the table.
//It also checks the collitions of an index
//Complexity O(1), worst case O(n)
bool colisionVerification(vector<Red*> &v, int &index){
  int cont = 0;

  if (v[index] != NULL) {

    while(v[index] != NULL){

      cont++;
      index++;

      if(index == 32749)
        index = 0;
      if(cont == 32749)
        return true;

    }

  }else {
    return false;
  }

  return false;
}

/*funcion para guardar los datos de la red, llama a la función que guarda
los hosts, no regresa nada
Complejidad O(n)*/
void saveRed(vector <Red*> &hashT,struct Red * &h, string ip1, string ip2, string data) {
  if (h == NULL) { //if the pointer is empty, then the value is inserted
    struct Red * tmp = new Red;
    int index;
    bool flag;
    tmp -> firstIP = ip1;
    tmp -> connections = 0;
    tmp -> next = h;
    tmp -> binding  = NULL;
    saveHost(tmp->binding,ip2, data);
    h = tmp;
    index = hashFunction(tmp->firstIP); //searchs and index for an ip
    flag = colisionVerification(hashT, index); //cheks if there are collitions
    if (flag) { //if there are no more spaces in the table
      cout << "Tabla llena, imposible meter más datos" << endl;
    } else {
      hashT[index] = tmp;
    }

    return;
  } else {
    if (h -> firstIP == ip1) { //if the node is already in the graph, then just the adjacent nodes are inserted.
      saveHost(h->binding, ip2, data);
      return;
    } else {
      saveRed(hashT,h->next, ip1, ip2, data); //if the node is not found, then the pointer will be the next value in the graph
    }
  }

}

/*funcion para cargar los datos a partir del archivo de bitacora.txt
recibe como argumento un double pointer al head y el nombre del archivo a extraer los datos
Complejidad O(n)*/
void cargarDatos(vector <Red*> &hash,struct Red * &h_1, string nombreArchivo_) {
  setbuf(stdin,NULL);

  string month, hour, errorMessage, lecture, ipString, errorMessageTemporal, date;

  string ip_1, ip_2, dataString;
  ifstream archivo (nombreArchivo_);

  while (!archivo.eof()){
  getline(archivo, lecture);
    if (lecture.size()!=0) {


      month = lecture.substr(0,3);

        date = lecture.substr(4,2);

        hour = lecture.substr(7,8);

        errorMessageTemporal = lecture.substr(16, 70);

        errorMessage = separationErrorIP(errorMessageTemporal, ipString);

         ip_1 = separationIP(ipString, ip_2);

        dataString = month + " " + date + " " + hour + " " + errorMessage;
        saveRed(hash,h_1, ip_1, ip_2, dataString);

      }
    ipString = "";
  }
}

/*funcion que almacena el grado de cada host y regresa
el grado calculado de la red
Complejidad O(n)*/
int dataDegree(struct Data *&data) {
  if (data == NULL)
    return 0;
  else
    return 1 + dataDegree(data->next);
}

/*función que almacena el grado de cada host, y regresa
el grado calculado de la red
Complejidad O(n)*/
int networkDegree(struct Host *&host) {
  if (host == NULL)
    return 0;
  else{
    host->connections = dataDegree(host->binding);
    return host->connections + networkDegree(host->next);
  }
}

/*funcion que calcula el input degree de los nodos
Complejidad O(n)*/
void calcDegrees(struct Red *&red) {
  if (red == NULL)
    return;
  red -> connections = networkDegree(red->binding);

  calcDegrees(red->next);
}



/*void function. Recieves a host and a string with the network
Prints out every host from a network
Complexity O(n)*/
void printNodes(struct Host *h, string red, vector <string> &vecHost ){
  string str2;
  if (h==NULL){
    sort(vecHost.begin(), vecHost.end(), [](auto& a,auto &b) { return stoi(a) < stoi(b); });

    for (auto&& s : vecHost) {
        cout << red << "." << s << endl;
    }
    return;
  }
  str2 = h->secondIp;
  str2.erase(str2.begin());
  vecHost.push_back(str2);
  printNodes(h->next,red, vecHost);
}

//void function. Receives the host.
//Prints out the number of connections of network
//complexity O(n)
void redHostConnections(struct Host *h) {
  int sum = 0;
  while(h != NULL){
    sum++;
    h = h -> next;
  }
  cout << sum << endl;;
}

//void function. Searchs in the hash table a given ip
//Prints out the data of the given ip if is found
//Complexity O(n)
void search(vector<Red*> v, string ip){
  bool found = false;
  int i = 0;
  int cont = 0;
  int sumador = 0;
  vector <string> hosts;
  i = hashFunction(ip);

  while(found == false){

    if (v[i] == NULL){
      struct Red *tmp;
      v[i] = tmp;
    }

    if(v[i]->firstIP == ip && v[i] != NULL){
      found = true;

    }else{

    if (v[i] != NULL){

      //LLAMADA A FUNCIONES CONEXIONES
      cont++;
      i++;

      if(i == 32749)
        i = 0;
      if (cont == 32749) {
        cout << "Dato no encontrado" << endl;
        return;
      }

    }
    }
  }

  cout << v[i]->firstIP << endl; //network
  cout << v[i]->connections << endl;  //total connections
  redHostConnections(v[i]->binding);  //total red-host connections
  printNodes(v[i]->binding,v[i]->firstIP, hosts); //hosts in the network

}


//main program
int main(){

  struct Red *h_1 = NULL;
  int cant;
  string data;
  string nombreArchivo = "bitacora2.txt";
  ifstream archivo (nombreArchivo);
  vector <Red*> hashTable(32749);

  if (archivo.is_open()){
    cargarDatos(hashTable,h_1, nombreArchivo); //carga los datos del archivo
  }

  calcDegrees(h_1); //calcula las conexiones de cada nodo

  cin >> cant;

  while (cant>0){
    cin >> data;
    search(hashTable, data);
    cout << endl; //endline
    cant --;
  }

  return 0;
}
