//main.cpp
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "bitacora_C.h"
#include "bitacora.h"

using namespace std;


/*Esta funcion convierte la hora en el formato de el txt con : a un formato
lineal, para así ser comparado, regresa un valor entero*/
int convertirHora(string hora){

  int horaFinal = 0;
  string horaString = "";
  horaString = hora.substr(0,2) + hora.substr(3,2) + hora.substr(6,2);
  horaFinal = stoi(horaString);
  return horaFinal;

}

/*Esta funcion se encarga de asignar los valores de los datos a nuestro
objeto Fecha, así podemos trabajar con un arreglo de objetos sin problema*/
void cargarDatos(vector<Fecha>& fecha,string nombreArchivo_) {
  setbuf(stdin,NULL);
  string mes, hora, razon, lectura, ipString, extra;
  int dia, horaEntero, ip;
  bool flag = true;

  int mesNumerico = 0;
  int contador = 30;
  int iterador = 16;

  int posicionFinalIp = 0;
  ifstream archivo (nombreArchivo_);
  while (!archivo.eof()){

    getline(archivo, lectura);
    mes = lectura.substr(0,3);

    dia = stoi(lectura.substr(4,5));

    hora = lectura.substr(7,8);
    horaEntero = convertirHora(hora);

    extra = lectura.substr(16, 70);

    Fecha f1(mes, dia, horaEntero, extra);
    fecha.push_back(f1);

  }
}
/*Esta funcion regresa los valores numéricos de los meses
para poder trabajar con ellos en nuestros diversos algoritmos*/
long indexMonth(string mes){

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
  long m = 100000000;

  for (int i = 0; i<12; i++){

    if (meses[i]==mes)
      return index[i]*m;
  }
  return 0;
}

/*
Esta función compara dos vectores y los ordena. Recibe como parámetro un vector en desorden,
así como el indice inicial, indice intermedio e indice final. No devuelve nada, únicamente ordena el arreglo.
*/
void Merge(vector <Fecha> &array, long inicio, long mitad ,long fin) {
    long i = inicio, j = mitad + 1, k = inicio;

    vector <Fecha> temp(array.size());

    long date1 = 0, date2 = 0; //variables para convertir fechas;

    while((i <= mitad) && (j <= fin)){ // comparaciones

        date1 = indexMonth(array[i].getMes()) + array[i].getDia()*1000000 + array[i].getHora(); //conversión
        date2 = indexMonth(array[j].getMes()) + array[j].getDia()*1000000 + array[j].getHora();

        if (date1<date2) {

            temp[k] = array[i];
            i++;

        } else {

            temp[k] = array[j];
            j++;

        }

        k++;
    }

    //ordenamiento
    if (i > mitad) {

      while (j <= fin) {

        temp[k] = array[j];
        j++;
        k++;

      }
    } else {

      while (i <= mitad) {

        temp[k] = array[i];
        i++;
        k++;

      }
    }

    for (long m = inicio; m < k; m++)
      array[m] = temp[m];

}


/*
Esta función ordena un vector mediante el ordenamiento por unión o merge, el cual es un ordenamiento recursivo.
Recibe como parámetro un vector en desorden, así como el indice inicial e indice final.
Divide el vector en dos partes y hace una llamada recursiva para cada uno, finalmente mediante otra función une estos dos vectores.
// Su complejidad es de orden O(nlog2(n)), puesto que las comparaciones disminuyen a la mitad en cada llamada recursiva.
*/
void ordenaMerge(vector <Fecha> &array, long inicio, long fin ){
    //variable
    long mitad = (inicio+fin)/2;

    if (inicio<fin) {
         ordenaMerge(array, inicio, mitad);
         ordenaMerge(array, mitad+1, fin);//llamadas recursivas
         Merge(array, inicio,  mitad, fin);

    }


}

/*Esta funcion se encarga de hacer la exportacion de los datos del vector
ordenados a un archivo txt*/
void exportarArchivo(vector<Fecha> v) {
  //archivo
  ofstream archivo;
  archivo.open ("sortedData.txt");

  long n = v.size();

  for (long i = 0; i<n; i++)
    archivo << v[n-i-1].imprimir();

  archivo.close();
}

/*Esta funcion se encarga de hacer la busqueda secuencial dentro del arreglo
con objetos, igualando el valor del dia y mes*/
void busqueda(vector<Fecha> &v, int x_dia, int x_mes, int f_dia, int f_mes){
  for(int i=v.size(); i>0; i--){
    string m = v[i].getMes();
    int s_mes = v[i].convertirMes(m);
    string mf = v[i].getMes();
    int sf_mes = v[i].convertirMes(mf);
    //(x_dia==v[i].getDia() && x_mes==s_mes)
    if (v[i].getDia()>=x_dia && s_mes>=x_mes && v[i].getDia()<=f_dia && sf_mes<=f_mes){
      cout<<v[i].imprimir();
    }
  }
}

//PROGRAMA PRINCIPAL
int main(){

  vector<Fecha> fecha;
  string nombreArchivo = "bitacora.txt";
  int dia_i, mes_i, dia_fin, mes_fin;
  ifstream archivo (nombreArchivo);

  if (archivo.is_open()) {
    cargarDatos(fecha,nombreArchivo);
  }

  ordenaMerge(fecha, 0, fecha.size()-1);
  exportarArchivo(fecha);
  cin>>dia_i;
  cin>>mes_i;
  cin>>dia_fin;
  cin>>mes_fin;
  busqueda(fecha, dia_i, mes_i, dia_fin, mes_fin);

  return 0;
}
