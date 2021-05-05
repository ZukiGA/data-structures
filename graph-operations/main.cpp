/*Tecnologico de Monterrey Campus Puebla
El programa calcula los nodos que tengan un mayor numero de conexiones,
tanto para nodos red como para nodos host. La lectura es a partir de un
archivo txt y la impresion solo sera de los valores de las IP
Rafael Alfonso Gomez Gonzalez A07133983
Santiago Hernandez Arellano A01730547
Bryan González Arellano A01734198
Fecha 22/11/20*/

//Declaracion de las librerías a usar para este programa
#include <iostream>
#include <fstream>
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

/*funcion para guardar los datos de la red, llama a la función que guarda
los hosts, no regresa nada
Complejidad O(n)*/
void saveRed(struct Red * &h, string ip1, string ip2, string data) {
  if (h == NULL) { //if the pointer is empty, then the value is inserted
    struct Red * tmp = new Red;
    tmp -> firstIP = ip1;
    tmp -> connections = 0;
    tmp -> next = h;
    tmp -> binding  = NULL;
    saveHost(tmp->binding,ip2, data);
    h = tmp;
    return;
  } else {
    if (h -> firstIP == ip1) { //if the node is already in the graph, then just the adjacent nodes are inserted.
      saveHost(h->binding, ip2, data);
      return;
    } else {
      saveRed(h->next, ip1, ip2, data); //if the node is not found, then the pointer will be the next value in the graph
    }
  }

}

/*funcion para cargar los datos a partir del archivo de bitacora.txt
recibe como argumento un double pointer al head y el nombre del archivo a extraer los datos
Complejidad O(n)*/
void cargarDatos(struct Red * &h_1, string nombreArchivo_) {
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
        saveRed(h_1, ip_1, ip_2, dataString);
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
    return 1 + networkDegree(host->next);
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


/*busca la red con mayor grado y a partir del dato
calculado, imprime las redes con mayor grado
Complejidad O(n)*/
void busqDegree(struct Red *red, int a){
  string mayor;
  string possible;
  int degree = 0;
  struct Red * tmp = new Red;
  tmp = red;
  while ((red)  != NULL){
    if ((red) -> connections > degree){
      degree = (red) -> connections;
    }
    (red) = (red)->next;
  }

  while (tmp  != NULL) {

    if (tmp->connections==degree)
      cout << tmp -> firstIP << endl;
    tmp = tmp -> next;
  }
}

/*funcion que calcula la red con mayor hosts registrados en el archivo de bitácoras
Complejida O(n^2)*/
void maxDegreeHost(struct Red *red, int a){
  string mayor;
  string possible;
  int degree = 0;
  struct Red * tmp = new Red;
  tmp = red;
  struct Host * tmpH = new Host;
  while ((red)  != NULL){
    tmpH = red -> binding;
    while (tmpH != NULL) {
      if (tmpH -> connections > degree){
        degree = tmpH -> connections;
      }
      tmpH = tmpH -> next;
    }
    (red) = (red)->next;
  }
  while ((tmp)  != NULL){
    while (tmp->binding != NULL) {
      if ((tmp) -> binding -> connections == degree){
        cout << tmp -> firstIP << tmp -> binding -> secondIp << endl;
      }
      tmp -> binding = tmp -> binding -> next;
    }
    (tmp) = (tmp)->next;
  }
}

int main(){
  struct Red *h_1 = NULL;
  string nombreArchivo = "bitacora2.txt";
  ifstream archivo (nombreArchivo);
  if (archivo.is_open()){
    cargarDatos(h_1, nombreArchivo); //carga los datos del archivo
  }
  calcDegrees(h_1); //calcula los grados de cada nodo
  busqDegree(h_1, 0); //despliega las redes con mayor grado.
  maxDegreeHost(h_1,0); //despliega los hosts con mayor grado.
}
