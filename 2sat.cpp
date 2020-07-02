#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <chrono>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::make_pair;
using std::list;
using std::memset;
using std::stack;


//Solves 2sat problem and gives solution
class Graph{
public:

    int nv;

    vector<int> *adj;

    Graph(int nv);

    void addEdge(int nv, int w);


};

Graph::Graph(int nv){
    this->nv = nv;
    adj = new vector<int>[20000 + 1];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}


int strongComponent[20001] = {0};

bool visited[200001];

bool visitedInv[200001];

int values[200001] = {0};

bool visited3[200001];

vector<int> top;

stack<int> sta;

int strongComponentNumber = 1;


void dfsOne(int u, Graph g){
    if(visited[u]){
        return;
    }

    visited[u] = 1;

    for (int i = 0 ; i < g.adj[u].size();i++){
        dfsOne(g.adj[u][i], g);
    }

    sta.push(u);
}

void dfsTwo(int u, Graph g){
    if(visitedInv[u]){
        return;
    }

    visitedInv[u] = 1;
    top.push_back(u);

    for (int i=0;i<g.adj[u].size();i++){
        dfsTwo(g.adj[u][i], g);
    }

    strongComponent[u] = strongComponentNumber;
}

bool isSatisfiable(Graph g, Graph gInv, int nv){

    for (int j = 1; j <= 2 * nv; ++j) {
        if (!visited[j]) {
            dfsOne(j, g);
        }
    }

    while(!sta.empty()){
        int n = sta.top(); sta.pop();

        if(!visitedInv[n]){
            dfsTwo(n, gInv);
            strongComponentNumber++;

        }
    }

    for (int i = 1; i <= 2 * nv; i++){

        if(strongComponent[i] == strongComponent[2 * nv - i + 1]){
            return false;
        }
    }
    return true;
}


int main(){
    /*
     * Input:
     * num_verticles num_clauses
     * x1 y1 (clause1)
     * x2 y2 (clause2)
     * .
     * .
     * .
     * xn yn (clause n)
     *
     *
     * Output:
     * Not satisfiable : If not satisfiable
     *
     * x1 where x_u is a T or F
     * x2
     * x3
     * x4
     * .
     * .
     * .
     * xn
     */
    freopen("", "r", stdin);
    freopen("", "w+", stdout);

    int nv, nc;
    cin >> nv >> nc;

    Graph g (2 * nv) ;
    Graph gInv (2 * nv) ;




    int a, b;

    for (int i = 0; i < nc; ++i) {
        cin >> a >> b;

        if(a < 0){
            a = 2 * nv + a + 1;
        }
        if(b < 0){
            b = 2 * nv + b + 1;
        }

        g.addEdge(2 * nv - a + 1, b);
        g.addEdge(2 * nv - b + 1, a);

        gInv.addEdge(b, 2 * nv - a + 1);
        gInv.addEdge(a, 2 * nv - b + 1);

    }

    bool possible = isSatisfiable(g, gInv, nv);

    if(!possible){
        cout << "Not satisfiable" << '\n';
    }
    else{
        for (int i = 0; i < top.size(); ++i) {
            visited3[top[i]] = true;
            if(top[i] > nv && visited3[2 * nv - top[i] + 1] ){
                values[2 * nv - top[i] + 1] = 1;
            }
        }
        for (int j = 1; j < nv + 1; ++j) {
            if(values[j] == 0){
                cout << "T" << '\n';
            }
            else{
                cout << "F" << '\n';
            }
        }
    }
}