#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using std::vector;
using std::cout;
using std::string;


// Let's see who survives the josephus scenario

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

vector<int> josephus(int n, int k);

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


vector<int> josephus(int n, int k){
    if(k == 0){
        exit(-1);
    }

    if(n == 1){
        return {1};
    }
    if(n == 0){
        return {0};
    }

    if(k == 1){
        vector<int> ret;
        for (int i = 1; i <= n; ++i) {
            ret.push_back(i);
        }
        return ret;
    }

    Link<int> *head;
    head = new Link<int> (1);
    Link<int> * cu = head;
    for (int i = 1; i < n; ++i) {
        Link<int> *tem;
        tem = new Link<int> (i + 1);
        cu->next = tem;
        if(i == n - 1){
            cu->next->next = head;
        }
        cu = cu->next;
    }

    vector<int> ord;

    bool a = true;

    Link<int> * curr = head;

    int count = k - 1;
    while(ord.size() != n){

        if(count == 1){
            Link<int> * temp = curr->next;
            ord.push_back(temp->info);
            delete_node(head, temp->info);
            count = k;
        }
        else{
            curr = curr->next;
            count--;
        }
    }


    return ord;

}
