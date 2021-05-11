#include <bits/stdc++.h>
#pragma once

class Auto{
private:
  char placa[7];
  string marca;
  string modelo;
  int anio;
  string placaString;
public:
  Auto() {
    anio = 0;
  }
  Auto(string plac, string marc, string model, int ani){
    strcpy(placa, plac.c_str());
    marca = marc;
    modelo = model;
    anio = ani;
    placaString = plac;
  }

  friend ostream& operator <<(ostream& os, const Auto& pr);


  string placaConversion(){
    string placaString;
    for(int i = 0 ; i < 8 ; i++){
      placaString.push_back(placa[i]);
    }
    return placaString;
  }
  int hashFunctionClass(){
    int position = 0;
    int suma = 0;
    for (int i = 0 ; i < 8 ; i ++){
      suma = suma + placa[i];
    }
    position = suma % 97;
    return position;
  }

  int getAnio(){
    return anio;
  }
  string getPlacaString(){
    return placaString;
  }

};
//OPERATOR <<
ostream& operator<<(ostream& os, const Auto& tn) {
  os << tn.placaString << " " << tn.marca << " " << tn.modelo << " " << tn.anio;
  return os;
}
