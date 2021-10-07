#ifndef Entrada_h
#define Entrada_h 

using namespace std;
#include <iostream>

class Entrada
{
  public:
    Entrada();
    Entrada(string, int, string, char, string, string);

    // get
    string getFecha() { return fecha;}
    int getFechaCode() { return fechaCode;}
    string getHora() { return hora;}
    char getPuntoEntrada() { return puntoEntrada;}
    string getUbi() { return ubi;}
    string getPais() { return pais;}

    //set 
    void setFecha(string _fecha) { fecha =  _fecha; }
    void setFechaCode(int _fechaCode) { fechaCode = _fechaCode; }
    void setHora( string _hora) { hora = _hora; }
    void setPuntoEntrada( char _puntoEntrada) { puntoEntrada = _puntoEntrada;}
    void setUbi(string _ubi) { ubi = _ubi; }
    void setPais(string _pais) { pais = _pais;}

    // imprimir 
    void mostrar();

    //Escritura
    friend ostream& operator<<(ostream& os, const Entrada &r);

    private:
      string fecha;
      int fechaCode;
      string hora;
      char puntoEntrada;
      string ubi;
      string pais;
};

Entrada::Entrada()
{
  fecha = " ";
  fechaCode = 0;
  hora = " ";
  puntoEntrada = ' ';
  ubi = " ";
  pais = " ";
}

Entrada::Entrada(string _fecha, int _fechaCode, string _hora, char _puntoEntrada, string _ubi, string _pais)
{
  fecha =  _fecha;
  fechaCode = _fechaCode;
  hora = _hora;
  puntoEntrada = _puntoEntrada;
  ubi = _ubi;
  pais = _pais;
}

void Entrada::mostrar()
{
  cout << fecha << " " << hora << " " << puntoEntrada << " " << ubi << endl;
}


ostream& operator<<(ostream& os, const Entrada &r){
    os << r.ubi << " " << r.fecha << " " << r.hora << " " << r.puntoEntrada << endl;
}

#endif // Entrada_h 