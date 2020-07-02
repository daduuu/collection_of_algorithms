#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <chrono>
using namespace std;

void insertionSort(vector<int> & a, int left, int right);
int medianOf3(vector<int> & a, int left, int right);
int partitionIt(vector<int> & a, int left, int right, int pivot);
void recQuickSort(vector<int> & a, int left, int right);

void quickSort(vector<int> & a) {
    recQuickSort(a, 0, a.size() - 1);
}

void recQuickSort(vector<int> & a, int left, int right) {

    if (right - left + 1 < 10)
        insertionSort(a, left, right);
    else {
        int median = medianOf3(a, left, right);
        int partition = partitionIt(a, left, right, median);
        recQuickSort(a, left, partition - 1);
        recQuickSort(a, partition + 1, right);
    }
}

int medianOf3(vector<int> & a, int left, int right) {
    int center = (left + right) / 2;

    if (a[left] > a[center])
        swap(a[left], a[center]);

    if (a[left] > a[right])
        swap(a[left], a[right]);

    if (a[center] > a[right])
        swap(a[center], a[right]);

    swap(a[center], a[right - 1]);
    return a[right - 1];
}


int partitionIt(vector<int> & a, int left, int right, int pivot) {
    int leftPtr = left;
    int rightPtr = right - 1;

    while (true) {

        while (a[++leftPtr] < pivot);

        while (a[--rightPtr] > pivot);

        if (leftPtr >= rightPtr)
            break;
        else
            swap(a[leftPtr], a[rightPtr]);
    }
    swap(a[leftPtr], a[right - 1]);

    return leftPtr;
}

void insertionSort(vector<int> & a, int left, int right) {
    int i = left, j = left;
    while(i <= right){
        j = i;
        while (j > left  && a[j - 1] > a[j]){
            swap(a[j - 1], a[j]);
            j--;
        }
        i ++;
    }
}

int main(){
    int size = 1000000; // change size
    vector<int> v(0);
    srand(1); // change seed
    for (int i = 0;i < size;i++) {
        int a[5];
        while (true) {
            for (int i = 0;i < 5;i++) {
                a[i] = rand() % 52;
            }
            bool good = true;
            for (int i = 0;i < 4;i++) {
                for (int j = i+1;j < 5;j++) {
                    if (a[i] == a[j]) {
                        good = false;
                        break;
                    }
                }
                if (!good) {
                    break;
                }
            }
            if (good) break;
        }
        int enc = 1;
        int val = 0;
        for (int i = 0;i < 5;i++) {
            val += a[i]*enc;
            enc *= 52;
        }
        v.push_back(val);
    }
    vector<int> vc = v;

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(v);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    cout << duration.count() << std::endl;


}