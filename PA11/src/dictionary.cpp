#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

using namespace std;

// this function will not be used in any way. For C++, templates are usually defined in header files. 
// However, for ZINC grading, we separate it into different files. So we need to use this 'trick' to
// instantiate the temnplate.
void compiler_trick_useless_function(){
    Dictionary d{""};
    lambda_for_main_cpp ct;
    d.foreach(ct);
}

int Dictionary::character_to_index(const char& ch){
    return ch - 97;
}

char Dictionary::index_to_character(const int& idx){
    return (char) (idx + 97);
}

const string& Dictionary::get_name() const{
    return name;
}

void Dictionary::set_name(const string& name){
    this->name = name;
}

Dictionary::Dictionary(const string& name)
    : name(name) 
{
    root = new Node;
}

Dictionary::~Dictionary(){
    delete root;
}

Dictionary::Dictionary(Dictionary&& d){
    root = d.root;
    d.root = nullptr;
}

Dictionary& Dictionary::operator=(Dictionary&& d){
    delete root;
    root = d.root;
    d.root = nullptr;

    return *this;
}

ostream& operator<<(ostream& o, Node* n){
    o << (*n);
    return o;
}

ostream& operator<<(ostream& o, const Node& n){
    o << " (" << n.meaning.type << ") " << n.meaning.meaning << " ";
    return o;
}

/**
 * TODO - Constructor for deep copy of dictionary.
*/
Dictionary::Dictionary(const Dictionary& d){
    root = new Node;
    *this = d;
}

/**
 * TODO - Assignment operator for deep copy of dictionary.
*/
Node* copy_helper (Node* dptr, Node* const parent) {
    Node* this_node = new Node; Node* this_dptr;
    this_node->meaning.meaning = dptr->meaning.meaning;
    this_node->meaning.type = dptr->meaning.type;
    this_node->get_parent() = parent;
    for (int i = 0; i < 26; i++) {
        this_dptr = dptr->operator[](i);
        if (this_dptr != nullptr) {
            this_node->set_child(i, copy_helper(this_dptr, this_node));
        }
    }
    return this_node;
}
Dictionary& Dictionary::operator=(const Dictionary& d){
    
        delete root;
        name = d.name;
        root = copy_helper(d.root, nullptr);

    return *this;
}

/**
 * TODO - Adds a node with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::add_node(const char* key){
    char this_char = key[0];
    Node* nodeptr = this->root; Node* locptr = this->root; int this_idx{0};
    for (int j = 0; key[j] != '\0'; j++) {
        this_char = key[j];
        this_idx = character_to_index(this_char);
        nodeptr = locptr->operator[](this_idx);
        if (nodeptr != nullptr) {
            
            locptr = locptr->operator[](this_idx);
        }
        else {
            nodeptr = new Node;
            nodeptr->meaning.meaning = string("");
            nodeptr->meaning.type = string("");
            locptr->set_child(this_idx, nodeptr);
            nodeptr->get_parent() = locptr;
            locptr = locptr->operator[](this_idx);
        }
        if (key[j + 1] == '\0') return nodeptr;
    
    }
    return nodeptr;
}

/**
 * TODO - Shorthand for add_node.
*/
Node* Dictionary::operator+=(const char* key){
    Node* new_node = this->add_node(key);
    return new_node;
}

/**
 * TODO - Removes all nodes starting with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer const char* key (of course you should clean up the nodes that are removed).
*/
void Dictionary::remove_node(const char* key){
    Node* nodeptr = this->root; Node* locptr = this->root;
    char this_char = key[0]; int this_idx{0};
    for (int j = 0; key[j] != '\0'; j++) {
        this_char = key[j]; this_idx = character_to_index(this_char);
        if (locptr->operator[](this_idx) == nullptr) return;
        nodeptr = locptr->operator[](this_idx);
        if (key[j + 1] == '\0') {
            locptr->set_child(this_idx, nullptr);
            delete nodeptr;
            return;
        }
        locptr = locptr->operator[](this_idx);
    }
}

/**
 * TODO - Shorthand for remove_node.
*/
void Dictionary::operator-=(const char* key){
    this->remove_node(key);
}

/**
 * TODO - Finds a node with the given key string, which is terminated with '\0'.
 * Returns nullptr if no such node is found.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::find_node(const char* key) const{
    if (key[0] == '\0') return root;
    Node* nodeptr = this->root;
    char this_char = key[0]; int this_idx{0};
    int i = 0;
    while (nodeptr != nullptr && this_char != '\0') {
        this_idx = character_to_index(this_char);
        nodeptr = nodeptr->operator[](this_idx); //might be nullptr if the node does not exist
        i++;
        this_char = key[i];
    }
    return nodeptr; //nullptr if node does not exist
    /* for (int j = 0; key[j] != '\0'; j++) {
        this_char = key[j]; this_idx = character_to_index(this_char);
        if (locptr->operator[](this_idx) == nullptr) return nullptr;
        nodeptr = locptr->operator[](this_idx);
        if (key[j + 1] == '\0') {
            return nodeptr;
        }
        locptr = locptr->operator[](this_idx);
    } */
    
}

/**
 * TODO - A function to do pre-order traversal on the tree. The function accepts a lambda function as argument,
 * and then the lambda function would be called for every node in the tree (except the root node). 
 * The lambda function accepts two arguments, (Node* current_node, vector<int>& current_key).
 * For each node accessed via pre-order traversal (except root node), call the lambda function.
 * 
 * Of course current_node should be the pointer to the node accessed. current_key should contain
 * a list of integers which corresponds to the indices required to travel to current_node from
 * the root node. For more explanation see the webpage.
 * 
 * The lambda is not supposed to change the dictionary.
*/
template<typename T>
void foreach_helper(T&& lambda, Node* curr_node, vector<int>& curr_key) {
    Node* this_child;
    for (int i = 0; i < 26; i++) {
        this_child = curr_node->operator[](i);
        if (this_child != nullptr) {
            curr_key.push_back(i);
            lambda(this_child, curr_key);
            foreach_helper(lambda, this_child, curr_key);
            curr_key.pop_back();
        }
    }
    return;
}
template<typename T> void Dictionary::foreach(T&& lambda) const{
    Node* curr_node = this->root; vector<int> curr_key;
    foreach_helper<T>(lambda, curr_node, curr_key);
}

/**
 * TODO - Prints all the nodes in the dictionary, in depth first alphabetical order.
 * See the webpage description for more details.
*/
void Dictionary::print_all_elements(ostream& o) const{
    int num_elems{0};
    auto f = [&](Node* curr_node, vector<int> curr_key) {
        char key[curr_key.size() + 1];
        for (int i = 0; i < curr_key.size() + 1; i++) {
            if (i == curr_key.size()) {
                key[i] = '\0';
                break;
            }
            key[i] = this->index_to_character(curr_key[i]);
        }
        num_elems++;
        o << key << " (" << curr_node->meaning.type << ") " << curr_node->meaning.meaning << " [" << num_elems << "]\n";
    };
    this->foreach(f);
}

/**
 * TODO - Calls print_all_elements
*/
std::ostream& operator<<(std::ostream& o, const Dictionary& dict){
    dict.print_all_elements(o);
    return o;
}

/**
 * TODO - Prints all the words in the dictionary, such that the word type is equal to the given type,
 * in depth first alphabetical order. See the webpage description for more details.
*/
void Dictionary::print_elements_given_type(const char* type) const{
    int num_words{0};
    auto f = [&](Node* curr_node, vector<int> curr_key) {
        if (curr_node->meaning.meaning == "") return;
        else if ((type == nullptr || type[0] == '\0' || curr_node->meaning.type == type)) {
            char key[curr_key.size() + 1];
            for (int i = 0; i < curr_key.size() + 1; i++) {
                if (i == curr_key.size()) {
                    key[i] = '\0';
                    break;
                }
                key[i] = this->index_to_character(curr_key[i]);
            }
            num_words++;
            cout << key << " (" << curr_node->meaning.type << ") " << curr_node->meaning.meaning << " [" << num_words << "]\n";
        }
    };
    this->foreach(f);
}

/**
 * TODO - Merges with another dictionary. Creates a new dictionary,
 * and does not modify the contents of the original dictionaries.
 * For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
void merge_helper(Node* locptr, Node* mergeptr) {
    Node* newnode; Node* this_mergeptr; Node* this_locptr;
        for (int i = 0; i < 26; i++) {
            this_locptr = locptr->operator[](i);
            if (this_locptr != nullptr) {
                this_mergeptr = mergeptr->operator[](i);
                if (this_mergeptr != nullptr) {
                    //recordptr = locptr; //record the current location of locptr
                    if (this_locptr->meaning.meaning != "") {
                    this_mergeptr->meaning.meaning = this_locptr->meaning.meaning;
                    this_mergeptr->meaning.type = this_locptr->meaning.type;
                    }
                    merge_helper(this_locptr, this_mergeptr);
                }
                if (this_mergeptr == nullptr) {
                    newnode = new Node;
                    if (this_locptr->meaning.meaning != "") {
                    newnode->meaning.meaning = this_locptr->meaning.meaning;
                    newnode->meaning.type = this_locptr->meaning.type;
                    }
                    mergeptr->set_child(i, newnode);
                    newnode->get_parent() = mergeptr;
                    this_mergeptr = newnode;
                    merge_helper(this_locptr, this_mergeptr);
                }
            }
        }
        return;
}
Dictionary Dictionary::merge(const Dictionary& d2) const{
    Dictionary newdic("");
    newdic = *this;
    Node* locptr = d2.root; Node* mergeptr = newdic.root;
    vector<int> own_children;

    merge_helper(locptr, mergeptr);
    return newdic;
}

/**
 * TODO - Merges with another dictionary. Moves the contents of d2
 * into a new dictionary. For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
void move_merge_helper(Node* locptr, Node* mergeptr) {
        for (int i = 0; i < 26; i++) {
            if (locptr->operator[](i) == nullptr && i != 25) continue;
            if (mergeptr->operator[](i) != nullptr && locptr->operator[](i) != nullptr) {
                move_merge_helper(locptr->operator[](i), mergeptr->operator[](i));
            }
            else if (mergeptr->operator[](i) == nullptr && locptr->operator[](i) != nullptr) {
                mergeptr->set_child(i, locptr->operator[](i));
                locptr->operator[](i)->get_parent() = mergeptr;
                merge_helper(locptr->operator[](i), mergeptr->operator[](i));
            }
            if (i == 25) return;
        }
}
void del_helper(Node* delptr) {
        for (int i = 0; i < 26; i++) {
            if (delptr->operator[](i) == nullptr) continue;
            else {
                del_helper(delptr->operator[](i));
            }
        }
        delptr = nullptr;
        return;
}
Dictionary Dictionary::merge(Dictionary&& d2) const{
    Dictionary newdic("");
    newdic = *this;
    Node* locptr = d2.root; Node* mergeptr = newdic.root;
    for (int i = 0; i < 26; i++) {
        if (locptr->operator[](i) == nullptr) continue;
        else if (mergeptr->operator[](i) == nullptr) {
            mergeptr->set_child(i, locptr->operator[](i));
            locptr->operator[](i)->get_parent() = mergeptr;
            locptr->set_child(i, nullptr);
        }
    }
    
    delete d2.root;
    d2.root = nullptr;
    
    return newdic;
}

/**
 * TODO - Creates a new dictionary, consisting only of the words
 * starting with the given key.
*/
Dictionary Dictionary::filter_starting_word(const char* key) const{
    if (key == nullptr || key[0] == '\0') {
        Dictionary newdic(*this);
        return newdic;
    }
    Dictionary newdic("");
    Node* keyptr = find_node(key);
    if (keyptr != nullptr) {
        Node* children = copy_helper(keyptr, nullptr);
        char last_char; Node* locptr = newdic.root; Node* nodeptr;

        vector<char> parents;
        for (int i = 0; key[i] != '\0'; i++) {
            if (key[i + 1] == '\0') {
                last_char = key[i];
                break;
            }
            parents.push_back(key[i]);
        }
        parents.push_back('\0');

        char parents_char[parents.size()];
        for (int i = 0; i < parents.size(); i++) parents_char[i] = parents[i];
        
        char this_char;
        for (int j = 0; parents_char[j] != '\0'; j++) {
            nodeptr = new Node;
            nodeptr->meaning.meaning = string("");
            nodeptr->meaning.type = string("");
            locptr->set_child(character_to_index(parents_char[j]), nodeptr);
            nodeptr->get_parent() = locptr;

            locptr = nodeptr;
            if (parents_char[j + 1] == '\0') break;
        }

        locptr->set_child(character_to_index(last_char), children);
        children->get_parent() = locptr;
    }

        return newdic;


    
}

Dictionary Dictionary::operator+(const Dictionary& d2) const{
    return merge(d2);
}

Dictionary Dictionary::operator+(Dictionary&& d2) const{
    return merge(move(d2));
}