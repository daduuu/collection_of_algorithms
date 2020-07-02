#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <chrono>
using namespace std::chrono;
using std::vector;
using std::cout;
using std::swap;


typedef vector<int> VI;
typedef vector<long> VL;

vector<VL> n_hanoi;
vector<VI> k_hanoi;

void hanoi_init();


void hanoi(vector<VI>& moves, int n_twrs, int n_dsks, VI& aux);


void hanoi_init(){

    n_hanoi = vector<vector<long>> (11, vector<long> (10001, 0));

    k_hanoi = vector<vector<int>> (11, vector<int> (10001, 0));

   //vector<vector<long>> n_hanoi  (11, vector<long> (10001, 0));
   //vector<vector<long>> k_hanoi  (11, vector<long> (10001, 0));

    for (long k = 0; k < 10000; ++k) {
        k_hanoi[3][k] = k - 1;
        k_hanoi[2][k] = 1;
        n_hanoi[2][k] = -1;
    }
    k_hanoi[3][0] = 0;
    k_hanoi[3][1] = 0;

    n_hanoi[2][1] = 1;


    for (long i = 3; i <= 10; ++i) {
        for (long j = 0; j <= 10000; ++j) {
            if(j == 0){
                n_hanoi[i][j] = 0;
                continue;
            }
            else if(j == 1){
                n_hanoi[i][j] = 1;
                k_hanoi[i][j] = 1;
                continue;
            }
            long solutions = LONG_MAX;

            for (long k = 1; k < j; ++k) {
                if(  n_hanoi[i][k] + n_hanoi[i][k]+ n_hanoi[i - 1][j - k] < solutions) {
                    if(n_hanoi[i][k] + n_hanoi[i][k] < 0 || n_hanoi[i - 1][j - k] < 0){
                        continue;
                    }

                    k_hanoi[i][j] = k;
                    solutions =  n_hanoi[i][k] + n_hanoi[i][k] + n_hanoi[i - 1][j - k];
                    if(solutions < 0){
                        solutions = LONG_MAX;
                        continue;
                    }

                }

            }
            n_hanoi[i][j]= solutions;

        }
    }
    cout << n_hanoi[4][137] << "\n";



}


void hanoi(vector<VI>& moves, int n_twrs, int n_dsks, VI& aux){
    if(n_dsks == 0){
        return;
    }
    else if(n_dsks == 1){
        moves.push_back({aux[0], aux[1]});
        return;
    }
    else if(n_dsks == -1){
        return;
    }

    swap(aux[1], aux[n_twrs - 1]);

    hanoi(moves, n_twrs, k_hanoi[n_twrs][n_dsks], aux);

    swap(aux[1], aux[n_twrs - 1]);

    hanoi(moves, n_twrs - 1, n_dsks - k_hanoi[n_twrs][n_dsks], aux);

    swap(aux[0], aux[n_twrs - 1]);

    hanoi(moves, n_twrs, k_hanoi[n_twrs][n_dsks], aux);

    swap(aux[0], aux[n_twrs - 1]);
}

bool test_hanoi(vector<vector<int>> ans,int n_dsks) { //check if the hanoi array is actually a solution
    vector<std::stack<int>> t(10);
    for (int i = n_dsks;i > 0;i--) {
        t[0].emplace(i);
    }

    for (vector<int> move : ans) {
        if (t[move[0]].empty()) return false;
        if (!t[move[1]].empty()) {
            if (t[move[0]].top() >= t[move[1]].top()) return false;
        }
        t[move[1]].emplace(t[move[0]].top());
        t[move[0]].pop();
    }

    for (int i = 1;i <= n_dsks;i++) {
        if (t[1].top() != i) {
            return false;
        }
        t[1].pop();
    }
    return true;
}

int main(){

    freopen("hanoi.out", "w+", stdout);

    auto start = high_resolution_clock::now();

    hanoi_init();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(stop - start);

    cout << " hanoi_init "<<  duration.count() << " seconds " << '\n';



    vector<VI> moves(0);
    vector<int> aux{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    start = high_resolution_clock::now();

    hanoi(moves, 5, 137, aux);
    stop = high_resolution_clock::now();


    auto duration2 = duration_cast<microseconds>(stop - start);

    cout << " hanoi "<< duration2.count() << " microseconds " << '\n';

    for (int i = 0; i < moves.size(); ++i) {
        cout <<   moves[i][0] << " ---> " << moves[i][1] << '\n';
    }

    /*

    cout << "\n";
    const int TOWERS = 10;
    const int DISKS = 10000;

    for (int twrs = 3;twrs <= 10;twrs++) {
        for (int dsks = 1;dsks < 10000;dsks++) {
            if (n_hanoi[twrs][dsks] == -1 || n_hanoi[twrs][dsks] > 10000) {
                break;
            }
            moves.clear();
            hanoi(moves,twrs,dsks,aux);
            if (moves.size() != n_hanoi[twrs][dsks] || !test_hanoi(moves,dsks)) {
                cout << "Failed on " << twrs << "towers and " << dsks << " disks" << std::endl;
            }
        }
    }
    cout << "done" << std::endl;
*/
}


