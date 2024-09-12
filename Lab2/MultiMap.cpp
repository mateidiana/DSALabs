#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//best=worst=average=θ(1)
MultiMap::MultiMap() {
    //TODO - Implementation
    nrelems=0;
    head= nullptr;
    tail= nullptr;
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
void MultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    nrelems++;
    keys* node = searchNode(c);

    if (node!= nullptr)
        addNewValue(c,v);
    else
        addNewKey(c,v);

}

//best=worst=average=θ(n)
void MultiMap::addNewValue(TKey k, TValue v) {
    keys* node= searchNode(k);
    values* newValue = new values{v, nullptr, nullptr};
    values* aux = node->headvalue;
    while(aux->next != nullptr){
        aux = aux->next;
    }
    aux->next = newValue;
    newValue->prev = aux;
}

//best=worst=average=θ(1)
void MultiMap::addNewKey(TKey k, TValue v) {

    if(head == nullptr){
        head = new keys{k, nullptr, nullptr, nullptr};
        head->headvalue = new values{v, nullptr, nullptr};
        tail = head;
    } else {
        keys* aux = new keys{k, nullptr, nullptr, nullptr};
        aux->headvalue = new values{v, nullptr, nullptr};

        aux->next = head;
        head->prev = aux;
        head = aux;

    }
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
bool MultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    keys *aux = searchNode(c);
    if (aux == nullptr)
        return false;

    bool removed = removeValue(c, v);

    if (aux->headvalue == nullptr)
        removeKey(c);

    return removed;
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
bool MultiMap::removeValue(TKey k, TValue v) {
    keys* node = searchNode(k);
    values* aux = node->headvalue;

    while(aux->value != v && aux->next != nullptr){
        aux = aux->next;
    }

    if(aux==node->headvalue && aux->value == v){
        node->headvalue = aux->next;
        if(node->headvalue!= nullptr)
            aux->next->prev = nullptr;
        delete aux;
        nrelems--;

    } else {

        if(aux->next == nullptr){
            if(aux->value == v){
                aux->prev->next = nullptr;
                aux->prev = nullptr;
                delete aux;
                nrelems--;
            } else return false;
        } else {
            values* previous = aux->prev;
            previous->next = aux->next;
            aux->next->prev = previous;
            delete aux;
            nrelems--;
        }
    }
    return true;

}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
void MultiMap::removeKey(TKey k) {

    keys *curr= searchNode(k);
    keys *previous = curr->prev;

    if (previous == nullptr)
    {
        head = curr->next;
        if(head!= nullptr)
            head->prev = nullptr;
    }

    else if (curr->next== nullptr)
    {
        tail=tail->prev;
        tail->next= nullptr;
    }
    else
    {
        previous->next = curr->next;
        curr->next->prev=previous;
    }

    delete curr;
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
vector<TValue> MultiMap::search(TKey c) const {
    //TODO - Implementation
    keys *aux = searchNode(c);
    vector<TValue> result{};

    if (aux == nullptr)
        return result;

    values *vNode = aux->headvalue;
    while (vNode != nullptr) {
        result.push_back(vNode->value);
        vNode = vNode->next;
    }

    return result;

}


//best=θ(1)
//worst=θ(n)
//average=θ(n)
vector<pair<TKey ,int>> MultiMap::Occurences() const {
    vector<pair<TKey,int>> occvec;
    keys *aux=head;
    pair<TKey,int> pair1;

    if (aux== nullptr)
        return occvec;

    while(aux!= nullptr)
    {
        int nrocc=0;
        pair1.first=aux->key;
        values *vNode=aux->headvalue;
        while(vNode!= nullptr)
        {
            nrocc++;
            vNode=vNode->next;
        }
        pair1.second=nrocc;
        occvec.push_back(pair1);
        aux=aux->next;
    }
    return occvec;
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
keys* MultiMap::searchNode(TKey k) const {
    keys *aux = head;

    while (aux != nullptr)
        if (aux->key == k)
            return aux;
        else
            aux = aux->next;

    return nullptr;
}

void MultiMap::print() {
    keys* node = head;
    while(node!= nullptr){
        cout << node->key << ": ";
        values* currV = node->headvalue;
        while (currV!= nullptr){
            cout << currV->value << " ";
            currV = currV->next;
        }
        cout << endl;
        node = node->next;
    }
}

//best=worst=average=θ(1)
int MultiMap::size() const {
    //TODO - Implementation
    return nrelems;
}

//best=worst=average=θ(1)
bool MultiMap::isEmpty() const {
    //TODO - Implementation
    return nrelems==0;
}

//best=worst=average=θ(1)
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

//best=worst=average=θ(n)
void MultiMap::deleteValues(keys *node) {
    values *vNode = node->headvalue;
    while (vNode != nullptr) {
        values *aux = vNode;
        vNode = vNode->next;
        delete aux;
    }
}

//best=worst=average=θ(n)
MultiMap::~MultiMap() {
    //TODO - Implementation
    while (head != nullptr) {
        keys *aux = head;
        head = head->next;
        deleteValues(aux);
        delete aux;
    }
}


