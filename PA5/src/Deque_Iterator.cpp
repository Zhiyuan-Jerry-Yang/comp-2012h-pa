#include <iostream>
#include "Deque_Iterator.h"
using namespace std;

bool equal(const Iterator& it1, const Iterator& it2){
    return it1.current == it2.current;
}

int value(const Iterator& it){
    return *it.current;
}

void set_node(Iterator& it, Node* new_node){
    it.node = new_node;
    it.first = new_node->arr;
    it.last = new_node->arr + CHUNK_SIZE;
}

Iterator next(const Iterator& it){
    Iterator next_it;
    if (it.current == it.last - 1){
        set_node(next_it, it.node->next);
        next_it.current = it.node->next->arr;
    }
    else {
        next_it = it;
        next_it.current++;
    }
    return next_it;
}

Iterator prev(const Iterator& it){
    Iterator prev_it;
    if (it.current == it.first){
        set_node(prev_it, it.node->prev);
        prev_it.current = it.node->prev->arr + CHUNK_SIZE - 1;
    }
    else {
        prev_it = it;
        prev_it.current--;
    }
    return prev_it;
}

