/*
El programa tiene como propósito solicitar al usuario el archivo .txt,
de tal manera que instantáneamente se guarden los datosz en las dos LinkedLists hechas para Mar Rojo y Mar Mediterraneo,
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

//Creación de la estructura entrada que contendrá los datos de las lineas del archivo
struct entrada  {
    string fecha;
    int fechaCode;
    int mes;
    int a;
    string hora;
    char puntoEntrada;
    string ubi;
    string pais;

    //Complejidad o(1)
    //Sobrecarga del operador > para comparar entradas.
    bool operator > (const entrada &otro) const{
        return (ubi == otro.ubi) ? (fechaCode > otro.fechaCode) : (ubi.compare(otro.ubi) > 0);
    }

    // Declaración de la sobrecarga del operador << para entradas.
    friend ostream& operator <<(ostream& os, entrada &e);
};

// Complejidad O(1)
// Desplegar datos de la entrada.
void printE(entrada e){
    cout << e.fecha << " " << e.hora << " " << e.puntoEntrada << " " << e.ubi << endl;
}

// Complejidad O(1)
// Escribir datos de la entrada en un archivo de salida.
ostream& operator<<(ostream& os, const entrada &e){
    os << e.fecha << " " << e.hora << " " << e.puntoEntrada << " " << e.ubi << endl;
}

// Complejidad O(n) Lineal, dependiente del largo de "date"
// Transformar fecha leída a entero.
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

//Complejidad: O(1)
//Regresa los primeros tres caractéres de un código UBI ingresado.
string countryFromUbi(string ubi){
    string pais;
    for (int i = 0; i < 3; i++)
    {
        pais += ubi[i];
    }
    return pais;
}

//Complejidad O(1)
//Compara los ubis de las entradas, si son iguales compara las fechas.
bool compDate(entrada x, entrada y) // compara fecha por fecha
{
    if (x.ubi == y.ubi) // checar si hay empate, si hay empate ordena por fecha
    {
        return x.fechaCode < y.fechaCode; // cual de las dos fechas es más grande
    }
    return x.ubi < y.ubi;
}

//Complejidad: Mejor caso O(1) Peor Caso O(n2)
vector<int> obtPeriod(LinkedList<entrada> llMarMed, LinkedList<entrada> llMarRojo, string paisB){
    // Inicializar las variables.
    int fechaInicioM, fechaInicioR, fechaFinalM = 0, fechaFinalR = 0, fechaFinal, fechaInicial, mes, a;
    int i = 0, j = 0;
    vector<int> periodo;
    // Booleans que monitorearan si hat coincidencias.
    bool coincidenciasM = true, coincidenciasR = true;
    
    //Obtencion del periodo en el que el UBI coincide.
    if(llMarRojo.getSize() > 0 || llMarMed.getSize() > 0){
        //Revisión Mar Mediterraneo
        while (i <= llMarMed.getSize()-1 && llMarMed.get(i).pais != paisB){ // Recorre la lista hasta llegar al final o al país buscado.
            i++;
        }
        if(i > llMarMed.getSize()-1){ // Si llega al final establece que no hay coincidencias y no realiza la comparación posterior.
            coincidenciasM = false;
            fechaInicioM = 0;
            fechaFinalM = 0;
        }
        else{ // Cuando encuentra coincidencias: 
            fechaInicioM = llMarMed.get(i).fechaCode; // Establece el punto de inicio de las coincidencias.
            while(i < llMarMed.getSize()-1 && llMarMed.get(i).pais == paisB){ // Continua el recorriddo hasta no encontrar mas.
                fechaFinalM = (fechaFinalM < llMarMed.get(i).fechaCode) ? llMarMed.get(i).fechaCode : fechaFinalM; // Establece la ultima fecha con coincidencias solo si la fecha encontrada es mayor que la actual.
                i++;
            }
            if(llMarMed.get(i).pais == paisB){ // Condicional en caso de que se necesite agregar la útlima linea
                fechaFinalM = (fechaFinalM < llMarMed.get(i).fechaCode) ? llMarMed.get(i).fechaCode : fechaFinalM; // Establece la ultima fecha con coincidencias solo si la fecha encontrada es mayor que la actual.
                i++;
            }
        }

        //Revisión Mar Rojo
        while (j <= llMarRojo.getSize()-1 && llMarRojo.get(j).pais != paisB){ // Recorre la lista hasta llegar al final o al país buscado.
            j++;
        }
        if(j > llMarRojo.getSize()-1){ // Si llega al final establece que no hay coincidencias y no realiza la comparación posterior.
            coincidenciasR = false;
            fechaInicioR = 0;
            fechaFinalR = 0;
        }
        else{ // Cuando encuentra coincidencias: 
            fechaInicioR = llMarRojo.get(j).fechaCode; // Establece el punto de inicio de las coincidencias.
            while(j < llMarRojo.getSize()-1 && llMarRojo.get(j).pais == paisB){ // Continua el recorriddo hasta no encontrar mas.
                fechaFinalR = (fechaFinalR < llMarRojo.get(j).fechaCode) ? llMarRojo.get(j).fechaCode : fechaFinalR; // Establece la ultima fecha con coincidencias solo si la fecha encontrada es mayor que la actual.
                j++;
            }
            if(llMarRojo.get(j).pais == paisB){ // Condicional en caso de que se necesite agregar la útlima linea
                fechaFinalR = (fechaFinalR < llMarRojo.get(j).fechaCode) ? llMarRojo.get(j).fechaCode : fechaFinalR; // Establece la ultima fecha con coincidencias solo si la fecha encontrada es mayor que la actual.
                j++;
            }
        }

        if(coincidenciasR == true || coincidenciasM == true){ // Si se encontraron coincidencias en cualquiera de las dos lista.
            fechaFinal = (fechaFinalM > fechaFinalR) ? fechaFinalM : fechaFinalR; // Establece la fecha final general como la mas a reciente.
            if(fechaInicioM != 0 && fechaInicioR != 0){ // Si hay coincidencias en ambas listas: 
                fechaInicial = (fechaInicioM > fechaInicioR) ? fechaInicioR : fechaInicioM; // Compara las fechas iniciales y guarda la mas antigua.
            }
            else if(fechaInicioM != 0){ //Si no, guarda la fehca que sea diferente a 0.
                fechaInicial = fechaInicioM;
            }
            else{ //Si no, guarda la fehca que sea diferente a 0.
                fechaInicial = fechaInicioR;
            }
        }
        else{ //Si no hubo coincidencias lo notifica.
            fechaInicial = 0;
            fechaFinal = 0;
            cout << "No se enconctro el ubi en los registros" << endl;
        }

        periodo.push_back(fechaInicial);
        periodo.push_back(fechaFinal);
        return periodo;
    }
    else{
        periodo.push_back(0);
        periodo.push_back(0);

        return periodo;
    }
}

int main(){
    // Establecer variables
    char puntoEntrada;
    string archivo, fecha, ubi, hora, pais, sPais, archivoM, archivoR;
    int fechaCode;
    ofstream salidaSuezM, salidaSuezR;
    // Solicitar el nombre del archivo de entrada
    ifstream archivoSuez;
    cout << "Ingresa el nombre del archivo a leer --> ";
    cin >> archivo;
    archivoSuez.open(archivo);
    // Crear 2 listas encadenadas
    LinkedList<entrada> llMarMed;
    LinkedList<entrada> llMarRojo;

    cout << "Leyendo archivo..." << endl;
    // En una almacenar los datos del Mar Mediterraneo
    while (archivoSuez >> fecha >> hora >> puntoEntrada >> ubi)
    {
      pais = countryFromUbi(ubi); //Extraer los los primeros carácteres del UBI y guardarlos como el país de origen 
      fechaCode = date2Int(fecha); //Convertir fechas a enteros para permitir la comparación

      entrada objAuxiliar; //Crear objetto auxiliar
      objAuxiliar.fecha = fecha;
      objAuxiliar.fechaCode = fechaCode;
      objAuxiliar.mes = fechaCode/100%100;
      objAuxiliar.a = fechaCode/10000;
      objAuxiliar.hora = hora;
      objAuxiliar.puntoEntrada = puntoEntrada;
      objAuxiliar.ubi = ubi;
      objAuxiliar.pais = pais;

      // Apendizarlo a una lista segun su entrada
      (objAuxiliar.puntoEntrada == 'M') ? llMarMed.addLast(objAuxiliar) : llMarRojo.addLast(objAuxiliar);
    }
    // Ordenar ascendentemente ambas listas por Ubi + fecha.
    llMarMed.sort();
    llMarRojo.sort();
    cout << "Archivo leido y orgainzado correctamente." << endl;

    // Guardar las listas en los archivos que decida el usuario.
    cout << "Ingresa el archivo donde se guardan los datos del Mar Rojo --> ";
    cin >> archivoR; // Solicitar nombre del archivo.

    salidaSuezR.open(archivoR); // Abrir archivo.

    cout << "Guardando datos..." << endl;
    for (int i = 0; i < llMarRojo.getSize(); i++){ // Por cada dato guardar en el archivo.
        salidaSuezR << llMarRojo.get(i);
    }

    cout << "Datos almacenados correctamente." << endl;

    cout << "Ingresa el archivo donde se guardan los datos del Mar Mediterraneo --> ";
    cin >> archivoM; // Solicitar nombre del archivo.

    salidaSuezM.open(archivoM); // Abrir archivo.

    cout << "Guardando datos..." << endl;
    for(int i = 0; i < llMarMed.getSize(); i++){ // Por cada dato guardar en el archivo.
        salidaSuezM << llMarMed.get(i);
    }
    cout << "Datos almacenados correctamente." << endl;

    // Solocitar los 3 caracteres de UBI a buscar
    vector<int> listaM, listaR, periodo; //Inicializar vectores que guarden las ocurrencias y los tiempos entre los cuales ocurren

    cout << "Ingresa la serie del país a buscar --> ";
    cin >> sPais; // Solicitar la serie del país
    periodo = obtPeriod(llMarMed, llMarRojo, sPais); // Obtener el periodo en el cual se encuentra esa serie en ambas listas.
    
    if(periodo[0] > 0 && periodo[1] > 0){ // Revisa que el pais a buscar este en los registros.
        listaM = llMarMed.search(sPais, periodo[0], periodo[1]);
        listaR = llMarRojo.search(sPais, periodo[0], periodo[1]);

        // Desplegar mes por mes las entradas por mar; mmm_aa_MM_MR.
        string meses[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dic"};
        int mes, a;
        
        // Establece la fecha inicial.
        mes = periodo[0]/100%100;
        a = periodo[0]/10000;

        cout << "Fecha  " << "M " << "R " << endl;
        for(int i = 0; i < listaR.size(); i++){
            cout << meses[mes-1] << " " << a << " " << listaM[i] << " " << listaR[i] << endl;
            mes++;
            if (mes > 12){
                mes -= 12;
                a++;
            }
        }
    }
}
