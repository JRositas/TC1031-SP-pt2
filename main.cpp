#include <iostream>
#include <fstream>
using namespace std;

#include "LinkedList.h"

struct entrada{
  string fecha;
  int fechaCode;
  string hora;
  char puntoEntrada;
  string ubi;
  string pais;
  bool operator > (const entrada &otro) const{
    return (ubi == otro.ubi) ? (fechaCode > otro.fechaCode) : (ubi.compare(otro.ubi) > 0);
  }
};

// Complejidad O(1)
void printE(entrada E){
  cout << E.fecha << " " << E.hora << " " << E.puntoEntrada << " " << E.ubi << endl;
}

// Complejidad O(n) Lineal, dependiente del largo de "date"
int date2Int(string date){
    int dateCode = 0;
    int aux = 0;
    int i = 0;
    while(date[i] != '-'){
        aux *= 10;
        aux += (date[i++] - '0');
    }
    dateCode += aux;

    string month = "";
    while(date[++i] != '-'){
        month += date[i];
    }
    int monthCode = 0;
    if(month == "jan"){
        monthCode = 1;
    } else if(month == "feb"){
        monthCode = 2;
    } else if(month == "mar"){
        monthCode = 3;
    } else if(month == "apr"){
        monthCode = 4;
    } else if(month == "may"){
        monthCode = 5;
    } else if(month == "jun"){
        monthCode = 6;
    } else if(month == "jul"){
        monthCode = 7;
    } else if(month == "aug"){
        monthCode = 8;
    } else if(month == "sep"){
        monthCode = 9;
    } else if(month == "oct"){
        monthCode = 10;
    } else if(month == "nov"){
        monthCode = 11;
    } else if(month == "dec"){
        monthCode = 12;
    }
    dateCode += (monthCode * 100);

    aux = 0;
    while(++i < date.length()){
        aux *= 10;
        aux += (date[i] - '0');
    }
    dateCode += (aux * 10000);

    return dateCode;
}

//Complejidad: O(1) Regresa los primeros tres caractéres de un código UBI ingresado
string countryFromUbi(string ubi){
    string pais;
    for (int i = 0; i < 3; i++)
    {
        pais += ubi[i];
    }
    return pais;
}

//Complejidad O(1)
bool compDate(entrada x, entrada y) // compara fecha por fecha
{
  if (x.ubi == y.ubi) // checar si hay empate, si hay empate ordena por fecha
  {
    return x.fechaCode < y.fechaCode; // cual de las dos fechas es más grande
  }
  return x.ubi < y.ubi;
}

int main(){
  char puntoEntrada;
  string archivo, fecha, ubi, hora, pais;
  int fechaCode;

  // Solicitar el nombre del archivo de entrada
  ifstream archivoSuez;
  cin >> archivo;
  archivoSuez.open(archivo);

  // Crear 2 listas encadenadas
  LinkedList<entrada> llMarMed;
  LinkedList<entrada> llMarRojo;

  // En una almacenar los datos del Mar Mediterraneo
  while (archivoSuez >> fecha >> hora >> puntoEntrada >> ubi)
    {
      pais = countryFromUbi(ubi); //Extraer los los primeros carácteres del UBI y guardarlos como el país de origen 
      fechaCode = date2Int(fecha); //Convertir fechas a enteros para permitir la comparación

      entrada objAuxiliar; //Crear objetto auxiliar
      objAuxiliar.fecha = fecha;
      objAuxiliar.fechaCode = fechaCode;
      objAuxiliar.hora = hora;
      objAuxiliar.puntoEntrada = puntoEntrada;
      objAuxiliar.ubi = ubi;
      objAuxiliar.pais = pais;


      // Apendizarlo a una lista segun su entrada
      (objAuxiliar.puntoEntrada == 'M') ? llMarMed.addLast(objAuxiliar) : llMarRojo.addLast(objAuxiliar);
    }

  // Ordenar ascendentemente ambas listas por Ubi + fecha
  llMarMed.sort();
  llMarRojo.sort();

  // 7. Solocitar los 3 caracteres de UBI a buscar Rositas


  // 6. Guardar las listas encadenadas en un txt con el nombre que de el usuario Dani

  // 8. Desplegar mes por mes las entradas por mar; mmm_aa_MM_MR Dani


  // Investigacion y reflexion individual
}
