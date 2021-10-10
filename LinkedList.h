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
vector<int> LinkedList<T>::search(string ubip, int fechaInicio, int fechaFinal){
    int mes, a, cant = 0;
    vector<int> ocurr;
    Node<T> *curr = head;
    if(size > 0){
        while (curr->getNext() != nullptr && curr->getData().pais != ubip){
            curr = curr->getNext();
        }
        mes = curr->getData().mes;
        a = curr->getData().a;
        while (curr->getNext() != nullptr && curr->getData().pais == ubip){
            if(curr->getData().mes == mes && curr->getData().a == a){
                cant++;
                curr = curr->getNext();
            }
            else{
                ocurr.push_back(cant);
                mes++;
                if (mes > 12){
                    mes -= 12;
                    a++;
                }
                cant = 0;
            }
        }
        ocurr.push_back(cant);
        return ocurr;
    }
}

#include "LinkedList_2_1.h"
#include "LinkedList_2_2.h"
