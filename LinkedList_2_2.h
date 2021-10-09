// Jose Rositas
// 30 Sept 2021

//Complejidad O(n) Lineal, depende de size
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &otra){
    this->size = 0;
    this->head = nullptr;
    this->operator=(otra);
}

//Complejidad O(n) Lineal, depende de size
template <class T>
void LinkedList<T>::operator+=(const LinkedList<T> &otra){
    Node<T> *curr1 = head;
    Node<T> *curr2 = otra.head;

    // posicionar curr1 en el último espacio
    while(curr1->getNext() != nullptr){
        curr1 = curr1->getNext();
    }

    // añadir al final todos los valores de otra
    while(curr2->getNext() != nullptr){
        T data = curr2 -> getData();
        curr1->setNext(new Node<T>(data, curr1->getNext()));
        size++;

        curr1 = curr1->getNext();
        curr2 = curr2->getNext();
    }
    T data = curr2 -> getData();
    curr1->setNext(new Node<T>(data, curr1->getNext()));
}

//Complejidad O(n) Lineal, depende de size
template <class T>
void LinkedList<T>::operator=(const LinkedList<T> &otra){
    this->deleteAll();

    this->addFirst(otra.head->getData());

    Node<T> *curr1 = head;
    Node<T> *curr2 = otra.head;

    while(curr2->getNext() != nullptr){
        curr2 = curr2 ->getNext();

        curr1->setNext(new Node<T>(curr2->getData(), curr1->getNext()));
        curr1 = curr1->getNext();
    }
    this->size = otra.size;
}