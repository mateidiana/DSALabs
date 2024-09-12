#include "MultiMapIterator.h"
#include "MultiMap.h"

//best=worst=average=θ(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    //TODO - Implementation
    first();
}

//best=worst=average=θ(1)
TElem MultiMapIterator::getCurrent() const{
    //TODO - Implementation
    if (!valid())
        throw exception();

    TKey key = keycurrent->key;
    TValue val = valuecurrent->value;

    return {key, val};
}

//best=worst=average=θ(1)
bool MultiMapIterator::valid() const {
    //TODO - Implementation
    return keycurrent!= nullptr;
}

//best=worst=average=θ(1)
void MultiMapIterator::next() {
    //TODO - Implementation

    if (!valid())
        throw exception();

    valuecurrent = valuecurrent->next;
    if (valuecurrent == nullptr) {
        keycurrent = keycurrent->next;
        if (valid())
            valuecurrent = keycurrent->headvalue;
    }
}

//best=worst=average=θ(1)
void MultiMapIterator::first() {
    //TODO - Implementation

    keycurrent = col.head;
    if (keycurrent != nullptr)
        valuecurrent = keycurrent->headvalue;
}


