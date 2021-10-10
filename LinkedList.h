#include <vector>
#include "Node.h"

template <class T>
class LinkedList{
    public:
        LinkedList();
        LinkedList(const LinkedList<T> &otra);
        ~LinkedList();
        void addFirst(T data);
        void addLast(T data);
        bool add(T data, int pos);
        void deleteFirst();
        void deleteLast();
        void del(int pos);
        int deleteAll();
        bool isEmpty();
        int getSize();
        void change(int pos1, int pos2);
        T set(T data, int pos);
        T get(int pos);
        void print();
        void reverse();
        void shift(int n);
        void sort();
        vector<int> search(string ubi, int fechaInicio, int fechaFinal);
        bool operator==(const LinkedList<T> &otra);
        void operator+=(const LinkedList<T> &otra);
        void operator=(const LinkedList<T> &otra);
    private:
        Node<T> *head;
        int size;
};

template <class T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
    deleteAll();
}

template <class T> 
// Complejidad: O(1)
void LinkedList<T>::addFirst(T data){
    head = new Node<T>(data, head);
    size++;
}

template <class T>
// Complejidad: O(n)
void LinkedList<T>::addLast(T data){
    if (size == 0){
        addFirst(data);
    }else{
        Node<T> *curr = head;
        while (curr->getNext() != nullptr){
            curr = curr->getNext(); // Avanzar un elemento en la lista
        }
        curr->setNext(new Node<T>(data)); // Encadenando un elemento al final de la lista
        size++;
    }
}

template <class T>
// Complejidad: Peor Caso O(n)
bool LinkedList<T>::add(T data, int pos){
    if (pos > size){
        return false;
    }
    if (pos == 0){
        addFirst(data);
    }else if (pos == size){
        addLast(data);
    }else{
        Node<T> *curr = head;
        for (int i=1; i<pos; i++){
            curr = curr->getNext();
        }
        curr->setNext(new Node<T>(data, curr->getNext()));
        size++;
    }
    return true;
}

template <class T>
// Complejidad: O(1)
void LinkedList<T>::deleteFirst(){
    if (size > 0){
        Node<T> *curr = head;
        head = head->getNext();
        delete curr;
        size--;
    }
}

template <class T>
// Complejidad: O(n)
void LinkedList<T>::deleteLast(){
    if (size <= 1){
        deleteFirst();
    }else{
        Node<T> *curr = head;
        while (curr->getNext()->getNext() != nullptr){
            curr = curr->getNext();
        }
        delete curr->getNext();
        curr->setNext(nullptr);
        size--;
    }
}

template <class T>
// Complejidad: Peor Caso O(n)
void LinkedList<T>::del(int pos){
    if (pos == 0){
        deleteFirst();
    }else if (pos == size-1){
        deleteLast();
    }else{
        Node<T> *curr = head;
        for (int i=1; i<pos; i++){
            curr = curr->getNext();
        }
        Node<T> *aux = curr->getNext();
        curr->setNext(aux->getNext()); // curr->setNext(curr->getNext()->getNext());
        delete aux;
        size--;
    }
}

template <class T>
// Complejidad: O(n)
int LinkedList<T>::deleteAll(){
    Node<T> *curr = head;
    while (head != nullptr){
        head = head->getNext();
        delete curr;
        curr = head;
    }
    int cant = size;
    size = 0;
    return cant;
}

template <class T>
// Complejidad: O(1)
bool LinkedList<T>::isEmpty(){
    return (size == 0); // return (head == nullptr);
}

template <class T>
// Complejidad: O(1)
int LinkedList<T>::getSize(){
    return size;
}

template <class T>
// Complejidad O(n)
void LinkedList<T>::change(int pos1, int pos2){
    if(pos1!=pos2){
        int posMen = (pos1 < pos2) ? pos1 : pos2;
        int posMay = (pos1 > pos2) ? pos1 : pos2;
        Node<T> *curr1 = head;
        for(int i=1; i<=posMen; i++){
            curr1 = curr1->getNext();
        }
        Node<T> *curr2 = curr1;
        for(int i=1; i>=(posMay-posMen); i++){
            curr2 = curr2->getNext();
        }
        T dataAux = curr1->getdata();
        curr1->setData(curr2->getdata());
        curr2->setData(dataAux);
    }
}

template <class T>
// Complejidad: Peor Caso O(n)
T LinkedList<T>::set(T data, int pos){
    Node<T> *curr = head;
    for (int i=1; i<=pos; i++){
        curr = curr->getNext();
    }
    T dataAux = curr->getData();
    curr->setData(data);
    return dataAux;
}

template <class T>
// Complejidad: Peor Caso O(n)
T LinkedList<T>::get(int pos){
    Node<T> *curr = head;
    for (int i=1; i<=pos; i++){
        curr = curr->getNext();
    }
    return curr->getData();
}

template <class T>
// Complejidad: O(n)
void LinkedList<T>::print(){
    Node<T> *curr = head;
    while (curr != nullptr){
        cout << curr->getdata() << endl;
        curr = curr->getNext();
    }
}

template <class T>
void LinkedList<T>::sort(){
    if(size > 1){
        Node<T> *i = head;
        while(i->getNext() != nullptr){
            Node<T> *j = i->getNext();
            while (j != nullptr){
              if(i->getData() > j->getData()){
                  T aux = i->getData();
                  i->setData(j->getData());
                  j->setData(aux);
              }
              j = j->getNext();
            }
            i = i->getNext();
        }
    }
}

template <class T>
//Complejidad: Mejor Caso O(1) Peor Caso O(n2)
vector<int> LinkedList<T>::search(string ubip, int fechaInicio, int fechaFinal){
    //Declaración de variables
    int mes, a, mesF, aF, cant = 0, i = 0, j = 0;
    vector<int> ocurr;
    Node<T> *curr = head;

    if(size > 0){ // Cuando la lista tenga datos 
        while (curr->getNext() != nullptr && curr->getData().pais != ubip){ // Busqueda de el ubi 
            curr = curr->getNext();
        }
        // Establecer las fechas en las que aparece el ubi
        mes = fechaInicio/100%100;
        a = fechaInicio/10000;
        mesF = fechaFinal/100%100;
        aF = fechaFinal/10000;
        if(curr->getData().pais != ubip){ // Si no se encontró el ubi.
            while(mes != mesF || a != aF){ //Llenar el vector de ceros.
                ocurr.push_back(0);
                mes++;
                if (mes > 12){
                    mes -= 12;
                    a++;
                }
            }
            ocurr.push_back(0);
            return ocurr;
        }
        while(curr != nullptr && curr->getNext()->getData().pais == ubip){ // Mientras se encuentre el ubi
            while (mes != mesF || a != aF && curr != nullptr){ // Mientras se esté dentro del rango
                if(curr->getData().mes == mes && curr->getData().a == a && curr->getData().pais == ubip){ // Mientras la fecha coincide se acumula el valor
                    cant++;
                    curr = curr->getNext();
                }
                else{ // Cuando la fecha ya no coincida se guarda el valor
                    if(i == 0){ // Si es el primer tipo de Ubi se crea la posición en el vector 
                        ocurr.push_back(cant);
                    }
                    else{ // Si es otro ubi se suma a la posición de la fecha
                        ocurr[j] += cant;
                    }
                    j++;
                    mes++;
                    if (mes > 12){
                        mes -= 12;
                        a++;
                    }
                    cant = 0; //Reinicio del acumulador
                }
            }
            while (mes == mesF && a == aF && curr != nullptr){ //Ultimo ciclo con la fecha final
                if(curr->getData().mes == mes && curr->getData().a == a && curr->getData().pais == ubip){ // Mientras la fecha coincide se acumula el valor
                    cant++;
                    curr = curr->getNext();
                }
                else{ // Cuando la fecha ya no coincida se guarda el valor
                    if(i == 0){ // Si es el primer tipo de Ubi se crea la posición en el vector
                        ocurr.push_back(cant);
                    }
                    else{ // Si es otro ubi se suma a la posición de la fecha
                        ocurr[j] += cant;
                    }
                    j++;
                    mes++;
                    if (mes > 12){
                        mes -= 12;
                        a++;
                    }
                    cant = 0;
                }
            }
            if(curr == nullptr){ //Ultimo almacenamiento en caso de encontrar las ultimas lineas de la lista
                ocurr[j] += cant;
            }
            // Se recorrió la fecha hasta el final, pero hay mas ubis con diferente número que inician de una fecha mas temprana
            mes = fechaInicio/100%100; // Se reinicia la fecha
            a = fechaInicio/10000; 
            i++; // Se guarda una variable para indicar que ya hubo un ciclo
            j = 0; // Se reinicia la variable que marca el índice
        }
    }
    return ocurr;
}

#include "LinkedList_2_2.h"