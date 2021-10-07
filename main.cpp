#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "LinkedList.h"
#include "Entrada.h"

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

// Complejidad: 0(1) Revisa si los UBI de las entradas son iguales, si lo son, compara las fechas, si nó compara los UBI
bool comparaDate( Entrada x, Entrada y) // compara fecha por fecha
{
  if (x.getUbi() == y.getUbi()) // checar si hay empate, si hay empate ordena por fecha
  {
    return x.getFechaCode() < y.getFechaCode(); // cual de las dos fechas es más grande
  }
  return x.getUbi() < y.getUbi();
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

int main(){
    
    int fechaCode;
    char puntoEntrada;
    string archivoM, archivoR, archivo, fecha, ubi, hora, pais, paisABuscar, paisaux;
    ifstream archivoSuez;
    ofstream suezM, suezR;
    Entrada *objAuxiliar; //Crear variable que guarde el objeto fuera del ciclo

    // 2. Crear 2 listas encadenadas Angela
    LinkedList<Entrada> llMarMed;
    LinkedList<Entrada> llMarRojo;

    // 1. Solicitar el nombre del archivo de entrada Angela
    cin >> " Ingresar archivo: " >> archivo;

    archivoSuez.open(archivo);

    
    // 3. En una almacenar los datos del Mar Mediterraneo Angela
    while (archivoSuez >> fecha >> puntoEntrada >> ubi){
    }
    // 4. En la otra los del Mar Rojo Angela

    // 5. Ordenar ascendentemente ambas listas por Ubi + fecha Rositas
    // 7. Solocitar los 3 caracteres de UBI a buscar Rositas

    // 6. Guardar las listas encadenadas en un txt con el nombre que de el usuario Dani
    string archivoR, archivoM;

    cin >> archivoR;

    suezR.open(archivoR);

    for (int i = 0; i < llMarRojo.getSize(); i++){
        suezR << llMarRojo.get(i);
    }

    cin >> archivoM;

    suezM.open(archivoM);

    for(int i = 0; i < llMarMed.getSize(); i++){
        suezM << llMarMed.get(i);
    }
    // 8. Desplegar mes por mes las entradas por mar; mmm_aa_MM_MR Dani
    

    // Investigacion y reflexion individual
}
