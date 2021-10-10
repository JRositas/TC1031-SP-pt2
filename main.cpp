/*
El programa tiene como propósito solicitar al usuario el archivo .txt,
de tal manera que instantáneamente se guarden los datos en las dos LinkedLists hechas para Mar Rojo y Mar Mediterraneo,
por lo que se va dar la instrucción que las dos listas se ordenen de manera ascendente por UBI + Fecha.
Para que por último despliegue mes por mes con respecto a su distintiva serie por cada entrada que realizó.
*/


// Integrantes (Equipo 12) :
// Daniel Evaristo Escalera Bonilla - A00831289
// José Arnoldo Rositas Salinas - A00829760
// Ángela Felicia Guajardo Olveda - A00829821

// SP TC1031
// 09 Oct 2021





#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "LinkedList.h"

struct entrada  {
    string fecha;
    int fechaCode;
    string hora;
    char puntoEntrada;
    string ubi;
    string pais;

    bool operator > (const entrada &otro) const{
        return (ubi == otro.ubi) ? (fechaCode > otro.fechaCode) : (ubi.compare(otro.ubi) > 0);
    }

    friend ostream& operator <<(ostream& os, entrada &e);
};

// Complejidad O(1)
void printE(entrada e){
    cout << e.fecha << " " << e.hora << " " << e.puntoEntrada << " " << e.ubi << endl;
}

// Complejidad O(1)
ostream& operator<<(ostream& os, const entrada &e){
    os << e.ubi << " " << e.fecha << " " << e.hora << " " << e.puntoEntrada << endl;
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


vector<int> obtPeriod(LinkedList<entrada> llMarMed, LinkedList<entrada> llMarRojo, string paisB){
    int fechaInicioM, fechaInicioR, fechaFinalM, fechaFinalR, fechaFinal, fechaInicial, mes, a;
    int i = 0, j = 0;
    vector<int> periodo;
    bool coincidenciasM = true, coincidenciasR = true;
    
    //Obtencion del periodo en el que el UBI coincide
    while (i <= llMarMed.getSize()-1 && llMarMed.get(i).pais != paisB){
        i++;
    }
    if(i > llMarMed.getSize()-1){
        coincidenciasM = false;
        fechaInicioM = 0;
        fechaFinalM = 0;
    }
    else{
        fechaInicioM = llMarMed.get(i).fechaCode;
        while(i <= llMarMed.getSize()-1 && llMarMed.get(i).pais == paisB){
            fechaFinalM = llMarMed.get(i).fechaCode;
            i++;
        }
    }

    while (j <= llMarRojo.getSize()-1 && llMarRojo.get(j).pais != paisB){
        j++;
    }
    if(j > llMarRojo.getSize()-1){
        coincidenciasR = false;
        fechaInicioR = 0;
        fechaFinalR = 0;
    }
    else{
        fechaInicioR = llMarRojo.get(j).fechaCode;
        while(j <= llMarRojo.getSize()-1 && llMarRojo.get(j).pais == paisB){
            fechaFinalR = llMarRojo.get(j).fechaCode;
            j++;
        }
    }

    if(coincidenciasR == true || coincidenciasM == true){
        fechaFinal = (fechaFinalM > fechaFinalR) ? fechaFinalM : fechaFinalR;
        if(fechaInicioM != 0 && fechaInicioR != 0){
            fechaInicial = (fechaInicioM > fechaInicioR) ? fechaInicioR : fechaInicioM;
        }
        else if(fechaInicioM != 0){
            fechaInicial = fechaInicioM;
        }
        else{
            fechaInicial = fechaInicioR;
        }
    }
    else{
        fechaInicial = 0;
        fechaFinal = 0;
        cout << "No se enconctro el ubi en los registros" << endl;
    }
    
    periodo.push_back(fechaInicial);
    periodo.push_back(fechaFinal);

    return periodo;
}

int main(){
    char puntoEntrada;
    string archivo, fecha, ubi, hora, pais, sPais, archivoM, archivoR;
    int fechaCode;
    ofstream salidaSuezM, salidaSuezR;
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

    // 6. Guardar las listas encadenadas en un txt con el nombre que de el usuario Dani
    cin >> archivoR;

    salidaSuezR.open(archivoR);

    for (int i = 0; i < llMarRojo.getSize(); i++){
        salidaSuezR << llMarRojo.get(i);
    }

    cin >> archivoM;

    salidaSuezM.open(archivoM);

    for(int i = 0; i < llMarMed.getSize(); i++){
        salidaSuezM << llMarMed.get(i);
    }

    // Solocitar los 3 caracteres de UBI a buscar
    vector<int> listaM, listaR, periodo;
    cin >> sPais;
    periodo = obtPeriod(llMarMed, llMarRojo, sPais);
    listaM = llMarMed.search(sPais, periodo[1], periodo[2]);
    listaR = llMarRojo.search(sPais, periodo[1], periodo[2]);

  // 8. Desplegar mes por mes las entradas por mar; mmm_aa_MM_MR Dani
    string meses[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dic"};
    int mes, a;
    
    mes = periodo[1]/100%100;
    a = periodo[1]/10000;
    for(int i; i < listaR.size(); i++){
        cout << meses[mes] << " " << a << " " << listaM[i] << " " << listaR[i] << endl;
    }

  // Investigacion y reflexion individual
}
