#include <iostream>
#include <fstream>
using namespace std;

const int CHUNK_SIZE = 8;

struct Node {
    int arr[CHUNK_SIZE];        // the chunk
    Node* prev;                 // previous Node
    Node* next;                 // next Node
};

struct Iterator {
    int* current;           // current position
    int* first;             // begin of the chunk, i.e., the position of first item
    int* last;              // end of the chunk, i.e., the position after the last item
    const Node* node;       // current Node
};


struct Deque {
    Iterator start;     // the position of first item in deque
    Iterator end;       // the position after last item in deque

    Node* sentinel;     // sentinel of the circular doubly-linked list
    int ll_size;        // size of linked list, notice that this is number of chunks, not items
};

void print_deque(const Deque& deque){
    Iterator working_iter;
    working_iter.node = deque.start.node;
    working_iter.first = deque.start.first;
    working_iter.last = deque.start.last;
    working_iter.current = deque.start.current;
    cout << "[";
    while (working_iter.current != deque.end.current){
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
    }
}


Deque create_deque(){
    Deque* dequeptr = new Deque;
    Node* nodeptr = new Node;
    dequeptr->ll_size = 1;
    dequeptr->sentinel->next = nodeptr;
    dequeptr->sentinel->prev = nodeptr;

    nodeptr->next = dequeptr->sentinel;
    nodeptr->prev = dequeptr->sentinel;

    dequeptr->start.node = nodeptr;
    dequeptr->end.node = nodeptr;
    dequeptr->start.first = nodeptr->arr;
    dequeptr->start.last = nodeptr->arr + CHUNK_SIZE;
    dequeptr->end.first = nodeptr->arr;
    dequeptr->end.last = nodeptr->arr + CHUNK_SIZE;
    dequeptr->start.current = dequeptr->start.first;
    dequeptr->end.current = dequeptr->end.first;

    return *dequeptr;
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
    delete deque.sentinel;
    deque.sentinel = nullptr;
}



void test_create_destroy() {
    cout << "===== Test create and destroy deque =====" << endl;
    Deque deque = create_deque();
    cout << "Deque created" << endl;

    if (deque.sentinel == nullptr) {
        cout << "[FAIL] sentinel node for empty deque should not be nullptr" << endl;
    }

    cout << "The deque now is: ";
    print_deque(deque);

    destroy_deque(deque);
    cout << "Deque destroyed" << endl;

    cout << "===== End Test =====" << endl << endl;
}


struct Point{
    int x;
    int y;
};

class Cell; // Forward declaration of Cell
class List
{
int size;
Cell* data; // Points to a (forward-declared) Cell object
Cell x; // Error: Cell not defined yet!
};
class Cell // Definition of Cell
{
int info;
Cell* next;
};

int main(){
/*     int a = 777234;
    ofstream ofs("test.txt");
    char b = static_cast<char>(a % 10);
    cout << b;
    a /= 10;
    while (a != 0){
        ofs.put(b);
        char b = static_cast<char>(a % 10);
        a /= 10;
    }
    ofs.put('\n');
    ofs.put('A');
    ofs.put('A');
    ofs.put('A');
    ofs.put('\n');
    ofs.close(); */
/*     int test[3] = {777, 2, 3};
    ofstream ofs("temp_test.txt");
    for (int i = 0; i < 2; i++){
        ofs << test[i] << '\n';
    }
    ofs << test[2];
    ofs.close(); */

}