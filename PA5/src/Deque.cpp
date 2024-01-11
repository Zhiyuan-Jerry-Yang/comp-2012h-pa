#include <iostream>
#include <fstream>
#include "Deque.h"
using namespace std;

Deque create_deque(){
    Deque new_deque;
    Node* nodeptr = new Node;
    Node* senptr = new Node;
    new_deque.ll_size = 1;
    new_deque.sentinel = senptr;
    new_deque.sentinel->next = nodeptr;
    new_deque.sentinel->prev = nodeptr;

    nodeptr->next = new_deque.sentinel;
    nodeptr->prev = new_deque.sentinel;

    new_deque.start.node = nodeptr;
    new_deque.end.node = nodeptr;
    new_deque.start.first = nodeptr->arr;
    new_deque.start.last = nodeptr->arr + CHUNK_SIZE;
    new_deque.end.first = nodeptr->arr;
    new_deque.end.last = nodeptr->arr + CHUNK_SIZE;
    new_deque.start.current = new_deque.start.first;
    new_deque.end.current = new_deque.end.first;

    return new_deque;
    /* Deque empty_deque;
    Node empty_node, empty_sentinel;
    empty_deque.ll_size = 1;
    empty_deque.sentinel = &empty_sentinel;
    empty_node.prev = empty_deque.sentinel;
    empty_node.next = empty_deque.sentinel;
    empty_deque.sentinel->next = &empty_node;
    empty_deque.sentinel->prev = &empty_node;
    
    empty_deque.start.node = &empty_node;
    empty_deque.start.first = empty_node.arr;
    empty_deque.start.last = empty_node.arr;

    empty_deque.end.node = &empty_node;
    empty_deque.end.first = empty_node.arr;
    empty_deque.end.last = empty_node.arr;

    return empty_deque; */
}

void destroy_deque(Deque& deque){
    Node* ptr = deque.sentinel->prev;
    while (ptr != deque.sentinel){
        ptr = ptr->prev;
        delete ptr->next;
    }
    delete ptr;
    deque.sentinel = nullptr;
}

Iterator begin(const Deque& deque){
    Iterator begin_iter;
    begin_iter = deque.start;
    return begin_iter;
}

Iterator end(const Deque& deque){
    Iterator end_iter;
    end_iter = deque.end;
    return end_iter;
}

int front(const Deque& deque){
    if (deque.start.node == deque.end.node && deque.end.current == deque.start.current){
        cout << "Cannot get front: deque is empty" << endl;
        return -1;
    }
    return *deque.start.current;
}

int back(const Deque& deque){
    if (deque.start.node == deque.end.node && deque.end.current == deque.start.current){
        cout << "Cannot get back: deque is empty" << endl;
        return -1;
    }
    if (deque.end.current != deque.end.first) return *(deque.end.current - 1);
    else return *(deque.end.node->prev->arr + CHUNK_SIZE - 1);
}

bool empty(const Deque& deque){
    return (deque.start.node == deque.end.node && deque.end.current == deque.start.current);
}

int size(const Deque& deque){
    if (deque.start.node == deque.end.node){
        return (deque.end.current - deque.start.current);
    }
    else return ((deque.ll_size - 2) * 8 + deque.end.current - deque.end.first + deque.start.last - deque.start.current);
}

void push_back(Deque& deque, int val){
    if (empty(deque)){
        *deque.start.current = val;
        deque.end.current++;
    }
    else if (deque.end.current < deque.end.last - 1){
        *deque.end.current = val;
        deque.end.current++;
    }
    else if (deque.end.current == deque.end.last - 1){
        Node* new_node = new Node;
        new_node->next = deque.sentinel;
        new_node->prev = deque.sentinel->prev;
        deque.sentinel->prev = new_node;
        new_node->prev->next = new_node->next->prev;
        set_node(deque.end, new_node);
        *deque.end.current = val;
        deque.end.current = new_node->arr;
        deque.ll_size++;
    }
/*     else if (deque.end.node->next == deque.sentinel){
        Node* new_node = new Node;
        new_node->next = deque.sentinel;
        new_node->prev = deque.sentinel->prev;
        deque.sentinel->prev = new_node;
        new_node->prev->next = new_node->next->prev;
        set_node(deque.end, new_node);
        deque.end.current = new_node->arr;
        *deque.end.current = val;
        deque.end.current++;
        deque.ll_size++;
    } */
/*     else {
        deque.end.current = deque.end.node->next->arr;
        set_node(deque.end, deque.end.node->next);
        *deque.end.current = val;
        deque.end = next(deque.end);
        deque.ll_size++;
    }
 */}

void push_front(Deque& deque, int val){
    if (empty(deque)){
        *deque.start.current = val;
        deque.end.current++;
    }
    else if (deque.start.current != deque.start.first || (deque.start.current == deque.start.first && deque.start.node->prev != deque.sentinel)){
        deque.start = prev(deque.start);
        *deque.start.current = val;
    }
    else if (deque.start.node->prev == deque.sentinel){
        Node* new_node = new Node;
        new_node->prev = deque.sentinel;
        new_node->next = deque.sentinel->next;
        deque.sentinel->next = new_node;
        new_node->next->prev = new_node->prev->next;
        set_node(deque.start, new_node);
        deque.start.current = new_node->arr + CHUNK_SIZE - 1;
        *deque.start.current = val;
        deque.ll_size++;
    }
}

void pop_back(Deque& deque){
    if (empty(deque)){
        cout << "Cannot pop_back: deque is empty" << endl;
    }
    else if (deque.end.current == deque.end.first){
        Iterator working_iter = end(deque);
        deque.end.current = deque.end.node->prev->arr + CHUNK_SIZE - 1;
        set_node(deque.end, deque.end.node->prev);
        working_iter.node->next->prev = working_iter.node->prev;
        working_iter.node->prev->next = deque.sentinel;
        delete working_iter.node;
        deque.ll_size--;
    }
    else {
        deque.end.current--;
    }
}

void pop_front(Deque& deque){
    if (empty(deque)){
        cout << "Cannot pop_front: deque is empty" << endl;
    }
    else if ((deque.start.current != deque.start.last - 1) || ((deque.start.current == deque.start.last - 1) && deque.ll_size == 1)){
        deque.start = next(deque.start);
    }
    else if ((deque.start.current == deque.start.last - 1 ) && deque.ll_size > 1){
        Iterator working_iter = begin(deque);
        deque.start = next(deque.start);
        working_iter.node->next->prev = deque.sentinel;
        working_iter.node->prev->next = working_iter.node->next;
        delete working_iter.node;
        deque.ll_size--;
    }
}

/*     if (deque.end.current == deque.end.last && deque.end.node->next->arr < deque.start.current){
        deque.end.node = deque.end.node->next;
        if (deque.end.node == deque.sentinel) deque.end.node = deque.end.node->next;
        deque.end.first = deque.end.node->arr;
    } */

void print_deque(const Deque& deque){
    Iterator working_iter;
    working_iter.node = deque.start.node;
    working_iter.first = deque.start.first;
    working_iter.last = deque.start.last;
    working_iter.current = deque.start.current;
    cout << "[";
    while (working_iter.current != deque.end.current){
        if (working_iter.current != working_iter.last){
            cout << *working_iter.current;
            if (working_iter.current == deque.end.current) {
                cout << "]" << endl;
                return;
            }
            else if ((working_iter.current != deque.end.current - 1)){
                if (working_iter.current == working_iter.last - 1 && working_iter.node->next == deque.end.node && deque.end.current == deque.end.first){;}
                else cout << ", ";
            }

            if (working_iter.current != working_iter.last - 1) working_iter.current++;
            else {
                working_iter.first = working_iter.node->next->arr;
                working_iter.last = working_iter.node->next->arr + CHUNK_SIZE;
                working_iter.current = working_iter.first;
                working_iter.node = working_iter.node->next;
            }
        }
        else {
                working_iter.first = working_iter.node->next->arr;
                working_iter.last = working_iter.node->next->arr + CHUNK_SIZE;
                working_iter.current = working_iter.first;
                working_iter.node = working_iter.node->next;
            }
    }
    if (working_iter.current == deque.end.current) { //the deque is empty
        cout << "]" << endl;
    }
/*     while (working_iter.current != deque.end.current){
        if (working_iter.node != deque.sentinel){
            while (working_iter.current != working_iter.last){
                cout << *working_iter.current;
                working_iter.current++;
                if (working_iter.current == deque.end.current) {
                    cout << "]";
                    return;
                }
                else cout << ", ";
            }
        }
        working_iter.first = working_iter.node->next->arr;
        working_iter.last = working_iter.node->next->arr + CHUNK_SIZE;
        working_iter.current = working_iter.first;
        working_iter.node = working_iter.node->next;
    } */
}

void insert(Deque& deque, const Iterator& pos, int val){
    Iterator working_iter = end(deque);
    Iterator pos_ref = pos;
    if (deque.end.current == deque.end.last - 1){ // there's no space to accommodate the newly inserted number - append one new node
        Node* new_node = new Node;
        new_node->next = deque.sentinel;
        new_node->prev = deque.sentinel->prev;
        deque.sentinel->prev = new_node;
        new_node->prev->next = new_node->next->prev;
        deque.end.current = deque.end.node->next->arr;
        set_node(deque.end, deque.end.node->next);
        deque.ll_size++;
    }
    else deque.end.current++;
    while (working_iter.current != pos_ref.current){
        if (working_iter.current == working_iter.last - 1){
            *(working_iter.node->next->arr) = *(working_iter.current);
        }
        else {
            *(working_iter.current + 1) = *(working_iter.current);
        }
            
        if (working_iter.current == working_iter.first) {
            set_node(working_iter, working_iter.node->prev);
            working_iter.current = working_iter.last - 1;
        }
        else working_iter.current--;
    }
    if (working_iter.current == pos_ref.current){
        if (working_iter.current == working_iter.last - 1){
            *(working_iter.node->next->arr) = *(working_iter.current);
        }
        else {
            *(working_iter.current + 1) = *(working_iter.current);
        }
    }
    *(working_iter.current) = val;
}
///////////////////////////////////// |
///////////////////////////////////// v
void erase(Deque& deque, const Iterator& pos){
    Iterator working_iter = pos;
    Iterator pos_ref = pos;
    while ((working_iter.current != deque.end.current - 1) && (working_iter.node->next->arr != deque.end.current || working_iter.current != working_iter.last - 1)){
        if (working_iter.current != working_iter.last - 1) {
            *(working_iter.current) = *(working_iter.current + 1);
            working_iter.current++;
        }
        else if (working_iter.node->next->arr != deque.end.current){
            *(working_iter.current) = *(working_iter.node->next->arr);
            working_iter.current = working_iter.node->next->arr;
            set_node(working_iter, working_iter.node->next);
        }
        
    }

    if (deque.end.current == deque.end.first){
        set_node(deque.end, deque.end.node->prev);
        deque.end.current = deque.end.last - 1;
        set_node(working_iter, working_iter.node->next);
        working_iter.node->next->prev = working_iter.node->prev;
        working_iter.node->prev->next = deque.sentinel;
        deque.ll_size--;
        delete working_iter.node;
    }
    else deque.end.current--;
}

void store_deque(const Deque& deque, const char* filename){
    ofstream ofs(filename);
    Iterator working_iter = begin(deque);
    const char separation = '\n';
    if (empty(deque)){
        ofs.close();
        return;
    }
    while ((working_iter.current != deque.end.current - 1) && !(working_iter.node->next->arr == deque.end.current && working_iter.current == working_iter.last - 1)){
        ofs << *working_iter.current << separation;
        if (working_iter.current != working_iter.last - 1) working_iter.current++;
        else {
            working_iter.current = working_iter.node->next->arr;
            set_node(working_iter, working_iter.node->next);
            if (working_iter.current == deque.end.current) break;
        }
    }
    ofs << *working_iter.current;
    ofs.close();
}

Deque load_deque(const char* filename){
    ifstream ifs(filename);
    Deque restored_deque = create_deque();
    Iterator working_iter = begin(restored_deque);
    int this_num;
    while (!ifs.eof()){
        ifs >> this_num;
        if (!ifs.fail()){
            push_back(restored_deque, this_num);        
        }
    }
    return restored_deque;
}