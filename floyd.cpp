#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using std::vector;
using std::cout;
using std::string;


//Detects loops in linked lists and the length and position of the loop using Floyd's algorithm
template<class T>
struct Link {
    explicit Link(const T& info, Link *next = 0) : info(info), next(next) { }
// This avoids stack overflow
    ~Link() {
        Link *p = next;
        while (p) {
            Link *q = p->next;
            p->next = 0;
            delete p;
            p = q;
        }
    }
    T info;
    Link *next;
};

template<class T>

vector<int> loopTail(Link<T>* head);

template<class T>

void delete_node(Link<T> * & head, int index){

    Link<T> * curr = head;
    Link<T> * prev = nullptr;
    while(curr->info != index) {
        if(curr->next == head){
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if(curr == curr->next){
        head = nullptr;
        return;
    }

    if (curr == head){
        prev = head;
        while(prev->next != head){
            prev = prev->next;
        }
        head = head->next;
        prev->next = head;

    }
    else if (curr->next == head){
        prev->next = head;

    }
    else{
        prev->next = curr->next;
    }

}


template<class T>

vector<int> loopTail(Link<T>* head) {

    if (head->next == nullptr) {
        return {0, 0};
    }
    if (head->next == head) {
        return {1, 0};
    }
    if (head->next->next == nullptr) {
        return {0, 1};
    }
    Link<T> *fast = head->next->next;
    Link<T> *slow = head->next;

    int size = 2;

    while (fast != slow) {
        if (fast->next == nullptr) {
            return {0, size};
        }
        if (fast->next->next == nullptr) {
            size += 1;
            return {0, size};
        }

        fast = fast->next->next;
        slow = slow->next;
        size += 2;
    }

    int loop_size = 1;

    slow = slow->next;

    while (slow != fast) {
        slow = slow->next;
        loop_size++;
    }

    slow = head;
    fast = head;

    for (int i = 0; i < loop_size; ++i) {
        fast = fast->next;
    }

    int tail_size = 0;

    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
        tail_size++;
    }


    if (loop_size == 0) {
        tail_size -= 1;
    }

    return {loop_size, tail_size};


}