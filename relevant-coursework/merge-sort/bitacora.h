//bitacora.h
# pragma once

//Declaracion de clase con nombre Fecha
class Fecha {
  //Metodos de la clase Fecha
public:
  //Constructor de la clase
  Fecha (string mes_, int dia_, int hora_, string extra_);
  Fecha ();
  //Getters
  string getMes();
  int getDia();
  int getHora();
  string getExtra();
  //Setter
  void setMes(string m);
  void setDia(int d);
  void setHora(int hr);
  void setExtra(string extra);
  //Conversion de mes a numero entero
  int convertirMes(string mes);
  //Impresion de datos
  string imprimir();
  //Formato hora
  string formatoHora();

  //Atributos
private:
  int dia;
  string mes;
  int hora;
  string extra;
};
