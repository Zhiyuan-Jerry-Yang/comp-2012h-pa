#include <iostream>
#include "Deque.h"
using namespace std;


/// test_insert and test_erase are porblematic
void test_create_destroy() {
    cout << "===== Test create and destroy deque =====" << endl;
    Deque deque = create_deque();
    cout << "Deque created" << endl;

    if (deque.sentinel == nullptr) {
        cout << "[FAIL] sentinel node for empty deque should not be nullptr" << endl;
    }

    cout << "The deque now is: ";
    print_deque(deque);

    push_back(deque, 10);
    push_back(deque, 15);
    cout << "The deque now is: ";
    print_deque(deque);

    destroy_deque(deque);
    cout << "Deque destroyed" << endl;

    cout << "===== End Test =====" << endl << endl;
}

void test_push_back() {
    cout << "===== Test push back =====" << endl;
    Deque deque = create_deque();

    push_back(deque, 1);
    push_back(deque, 2);
    push_back(deque, 3);
    push_back(deque, 2);
    push_back(deque, 0);
    push_back(deque, 88);
    push_back(deque, 79);
    push_back(deque,277);
    push_back(deque, 427474);




    cout << "The deque now is: ";
    print_deque(deque);

    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_push_front() {
    cout << "===== Test push front =====" << endl;
    Deque deque = create_deque();

    push_front(deque, 1);
    push_front(deque, 2);
    push_front(deque, 3);
    push_front(deque, 2);
    push_front(deque, 0);
    push_front(deque, 88);
    push_front(deque, 79);
    push_front(deque,277);
    push_front(deque, 427474);
    push_front(deque, 10);
    push_front(deque, 2012);
    push_front(deque, 2022);
    push_front(deque, 12551);
    push_front(deque, 2351);
    push_front(deque, 427474);
    push_front(deque, 5373);
    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);

    cout << "The deque now is: ";
    print_deque(deque);

    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_front_back() {
    cout << "===== Test get front and back =====" << endl;
    Deque deque = create_deque();

    // when deque is empty, the returned value doesn't matter
    int front_item = front(deque);
    int back_item = back(deque);

    push_back(deque, 1);
/*     push_back(deque, 2);
    push_back(deque, 3);
    push_back(deque, 4);
    push_back(deque, 5);
    push_back(deque, 6);
    push_back(deque, 7);
    push_back(deque, 8);
    push_back(deque, 9);
    push_back(deque, 10);
    push_back(deque, 11);
    push_back(deque, 12);
    push_back(deque, 13);
    push_back(deque, 14);
    push_back(deque, 15);
    push_back(deque, 16);
    push_back(deque, 17);
    push_back(deque, 18); */
    push_front(deque, -1);
    push_front(deque, -2);
    push_front(deque, -3);
    push_front(deque, -4);
    push_front(deque, -5);
    push_front(deque, -6);
    push_front(deque, -7);
    push_front(deque, -8);
/*     push_front(deque, -9);
    push_front(deque, -10);
    push_front(deque, -11);
    push_front(deque, -12);
    push_front(deque, -13);
    push_front(deque, -14);
    push_front(deque, -15);
    push_front(deque, -16);
    push_front(deque, -17);
    push_front(deque, -18); */

    cout << "The deque now is: "; print_deque(deque);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;
    cout << "size of deque: " << size(deque) << '\n';

    pop_back(deque);
    cout << "The deque now is: "; print_deque(deque);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;
    cout << "size of deque: " << size(deque) << '\n';

    pop_front(deque);
    cout << "The deque now is: "; print_deque(deque);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;
    cout << "size of deque: " << size(deque) << '\n';

    cout << value(prev(prev(prev(prev(end(deque)))))) << '\n';
    cout << boolalpha << equal(next(next(next(begin(deque)))), prev(prev(prev(prev(end(deque))))));

    
    
    /* push_back(deque, 10);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;

    push_back(deque, 15);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;

    push_front(deque, 20);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;

    push_back(deque, 10);
    push_back(deque, 2012);
    push_back(deque, 2022);
    push_front(deque, 12551);
    push_back(deque, 2351);

    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;
    
    push_back(deque, 427474);
    push_front(deque, 5373);

    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl;

    push_back(deque, 3);
    push_back(deque, 375);
    push_back(deque, 473);
    push_back(deque, 375);
    push_front(deque, 37355);
    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);
    front_item = front(deque);
    back_item = back(deque);
    cout << "front: " << front_item << ", back: " << back_item << endl; */



    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_empty_size() {
    cout << "===== Test empty and size =====" << endl;
    Deque deque = create_deque();

    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;
    cout << "size: " << deque.ll_size << endl;
    push_back(deque, 10);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_front(deque, 15);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_front(deque, 20);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_back(deque, 20);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_back(deque, 20);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_back(deque, 20);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_back(deque, 2240);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    push_back(deque, 1520);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;
    push_back(deque, 13540);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;
    push_back(deque, 15230);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;
    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);
    push_front(deque, 473);
    cout << "deque is empty: " << (empty(deque) ? "true" : "false") << endl;
    cout << "size of deque: " << size(deque) << endl;

    cout << "size: " << deque.ll_size << endl;

    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_pop_back() {
    cout << "===== Test pop back =====" << endl;
    Deque deque = create_deque();

    pop_back(deque);

    push_front(deque, 1);
    push_front(deque, -1);
    


    cout << "The deque now is: ";
    print_deque(deque);

    pop_back(deque);
    cout << "The deque now is: ";
    print_deque(deque);

    pop_back(deque);
    cout << "The deque now is: ";
    print_deque(deque);


    pop_back(deque);
    cout << "The deque now is: ";
    print_deque(deque);
    pop_back(deque);
    cout << "The deque now is: ";
    print_deque(deque);


    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_pop_front() {
    cout << "===== Test pop front =====" << endl;
    Deque deque = create_deque();

    pop_front(deque);

    push_back(deque, 10);
    //push_back(deque, 2012);
    /* push_back(deque, 2022);
    push_back(deque, 2012);
    push_back(deque, 2022);
    push_back(deque, 2351);
    push_back(deque, 427474);
    push_back(deque, 3);
    push_back(deque, 375);
    push_front(deque, 12551);
    push_front(deque, 5373); */

    cout << "The deque now is: ";
    print_deque(deque);
    

    pop_front(deque);
    cout << "The deque now is: ";
    print_deque(deque);
    pop_front(deque);
    cout << "The deque now is: ";
    print_deque(deque);
    pop_front(deque);
    /* cout << "The deque now is: ";
    print_deque(deque);

    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);
    push_front(deque, 473);
    pop_front(deque);
    cout << "The deque now is: ";
    print_deque(deque);
    pop_front(deque);
    cout << "The deque now is: ";
    print_deque(deque); */

    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_insert() {
    cout << "===== Test insert =====" << endl;
    Deque deque = create_deque();

/*     push_back(deque, 10);
    push_back(deque, 15);
    push_back(deque, 25);
    push_back(deque, 10);
    push_back(deque, 2012);
    push_back(deque, 2022);
    push_back(deque, 2351);
    push_back(deque, 427474);
    push_back(deque, 2012);
    push_front(deque, 12551);
    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);
    push_front(deque, 375);
    push_front(deque, 37355);
 */
    
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, begin(deque), 5);
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, next(begin(deque)), 7);
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, next((begin(deque))), 777);
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, end(deque), 225);
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, prev(end(deque)), 20);
    cout << "The deque now is: ";
    print_deque(deque);

    insert(deque, prev(prev(end(deque))), 2023);
    cout << "The deque now is: ";
    print_deque(deque);


    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_erase() {
    cout << "===== Test erase =====" << endl;
    Deque deque = create_deque();

    push_back(deque, 10);
    push_front(deque, 15);
    /* push_back(deque, 25);
    push_back(deque, 10);
    push_back(deque, 2012);
    push_back(deque, 2022);
    push_back(deque, 2351);
    push_back(deque, 427474); */
    /* push_front(deque, 12551);
    push_front(deque, 3);
    push_front(deque, 375);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355);
    push_front(deque, 473);
    push_front(deque, 375);
    push_front(deque, 37355); */



    cout << "The deque now is: ";
    print_deque(deque);
    cout << "Size of deque: " << size(deque) << '\n';
    

    erase(deque, begin(deque));
    cout << "The deque now is: ";
    print_deque(deque);
    cout << "Size of deque: " << size(deque) << '\n';

    /* erase(deque, next(begin(deque)));
    cout << "The deque now is: ";
    print_deque(deque);
    cout << "Size of deque: " << size(deque) << '\n'; */

    erase(deque, prev(end(deque)));
    cout << "The deque now is: ";
    print_deque(deque);
    cout << "Size of deque: " << size(deque) << '\n';

    /* erase(deque, prev(prev(end(deque))));
    cout << "The deque now is: ";
    print_deque(deque);
    cout << "Size of deque: " << size(deque) << '\n'; */

    cout << "no. of nodes: " << deque.ll_size << '\n';
    cout << "Empty? " << boolalpha << empty(deque);


    destroy_deque(deque);
    cout << "===== End Test =====" << endl << endl;
}

void test_store_load() {
    cout << "===== Test store and load deque =====" << endl;
    Deque deque = create_deque();

    push_back(deque, 1);
    push_back(deque, 2);
    push_back(deque, 3);
    push_back(deque, 4);
    push_back(deque, 5);
    push_back(deque, 6);
    push_back(deque, 7);
    push_back(deque, 8);
    push_back(deque, 9);
    push_front(deque, -1);
    push_front(deque, -2);
    push_front(deque, -3);
    push_front(deque, -4);
    push_front(deque, -5);
    push_front(deque, -6);
    push_front(deque, -7);
    push_front(deque, -8);
    push_front(deque, -9);

    cout << "no. of nodes: " << deque.ll_size << "    " << "size of deque: " << size(deque) << '\n';
    
    cout << "The deque now is: ";
    print_deque(deque);

    store_deque(deque, "deque_demo.txt");
    cout << "Successfully stored deque to 'deque_demo.txt'" << endl;

    destroy_deque(deque);

    Deque restored_deque = load_deque("deque_demo.txt");
    cout << "The restored deque is: ";
    print_deque(restored_deque);
    destroy_deque(restored_deque);

    cout << "===== End Test =====" << endl;
}
int main() {
    //test_create_destroy();
    //test_push_back();
    //test_push_front();
    test_front_back();
    //test_empty_size();
    //test_pop_back();
    //test_pop_front();
    //test_insert();
    //test_erase();
    //test_store_load();

    return 0;
}
