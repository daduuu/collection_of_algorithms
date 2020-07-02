#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <chrono>
#include <list>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::make_pair;
using std::list;
using std::memset;
using std::stack;
using std::copy;

#define MAX_ROW 6000
#define MAX_COL 6000

using namespace std;

struct Node{
    struct Node *left;
    struct Node *right;
    struct Node *up;
    struct Node *down;
    struct Node *column;
    int rowID;
    int colID;
    int nodeCount;
};


struct Piece{
    vector<char> instructions;
    char name;
};

struct Coordinate{
    int y;
    int x;

    Coordinate(int y, int x) : y(y), x(x) {}


};

struct Node *header = new Node();

struct Node Matrix[MAX_ROW][MAX_COL];

vector<vector<int>> results;


bool ProbMat[MAX_ROW][MAX_COL];

vector <struct Node*> solutions;

int nRow = 0,nCol = 0;

int getRight(int i){
    return (i + 1) % nCol;
}
int getLeft(int i){
    if(i - 1 < 0){
        return nCol - 1;
    }
    return i - 1;

}
int getUp(int i){
    if(i - 1 < 0){
        return nRow;
    }
    return i - 1;

}
int getDown(int i){
    return (i + 1) % (nRow + 1);
}

Node *create4WayMatrix(){

    for(int i = 0; i <= nRow; i++){
        for(int j = 0; j < nCol; j++){
            if(ProbMat[i][j]){
                int a, b;

                if(i) {
                    Matrix[0][j].nodeCount += 1;
                }

                Matrix[i][j].column = &Matrix[0][j];

                Matrix[i][j].rowID = i;
                Matrix[i][j].colID = j;


                a = i; b = j;
                do{
                    b = getLeft(b);
                } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].left = &Matrix[i][b];

                a = i; b = j;
                do {
                    b = getRight(b);
                } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].right = &Matrix[i][b];


                a = i; b = j;
                do {
                    a = getUp(a);
                } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].up = &Matrix[a][j];


                a = i; b = j;
                do {
                    a = getDown(a);
                } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].down = &Matrix[a][j];
            }
        }
    }

    header->right = &Matrix[0][0];

    header->left = &Matrix[0][nCol-1];

    Matrix[0][0].left = header;
    Matrix[0][nCol-1].right = header;
    return header;
}

void cover(struct Node *targetNode){
    struct Node *row, *right;

    struct Node *col = targetNode->column;

    col->left->right = col->right;
    col->right->left = col->left;

    for(row = col->down; row != col; row = row->down){
        for(right = row->right; right != row; right = right->right){
            right->up->down = right->down;
            right->down->up = right->up;

            Matrix[0][right->colID].nodeCount -= 1;
        }
    }
}


void uncover(struct Node *target){
    struct Node *row, *left;

    struct Node *colNode = target->column;

    for(row = colNode->up; row != colNode; row = row->up){

        for(left = row->left; left != row; left = left->left){
            left->up->down = left;
            left->down->up = left;

            Matrix[0][left->colID].nodeCount += 1;
        }
    }

    colNode->left->right = colNode;
    colNode->right->left = colNode;
}


Node *getMinColumn(){
    struct Node *h = header;
    struct Node *min = h->right;
    h = h->right->right;
    do{
        if(h->nodeCount < min->nodeCount){
            min = h;
        }
        h = h->right;
    }
    while(h != header);

    return min;
}


void addSolutions(){
    vector<struct Node*>::iterator i;

    vector<int> temp;
    for(i = solutions.begin(); i != solutions.end(); i++){
        temp.push_back((*i) ->rowID);
    }

    results.push_back(temp);

}

void search(int k){
    struct Node *row;
    struct Node *right;
    struct Node *left;
    struct Node *column;

    if(header->right == header){
        addSolutions();
        return;
    }

    column = getMinColumn();

    cover(column);

    for(row = column->down; row != column; row = row->down ){
        solutions.push_back(row);

        for(right = row->right; right != row; right = right->right){
            cover(right);
        }

        search(k+1);


        solutions.pop_back();

        column = row->column;
        for(left = row->left; left != row;left = left->left){
            uncover(left);
        }

    }

    uncover(column);
}



Piece rotatePieces90(Piece p){

    Piece a;
    a.name = p.name;

    vector<char> ins;

    for (char c: p.instructions) {
        if(c == 'S'){
            ins.push_back('W');
        }
        else if(c == 'N'){
            ins.push_back('E');
        }
        else if(c == 'W'){
            ins.push_back('N');
        }
        else if(c == 'E'){
            ins.push_back('S');
        }
        else{
            ins.push_back(c);
        }
    }

    a.instructions = ins;
    return a;

}
Piece rotatePieces180(Piece p){

    Piece a;
    a.name = p.name;

    vector<char> ins;

    for (char c: p.instructions) {
        if(c == 'S'){
            ins.push_back('N');
        }
        else if(c == 'N'){
            ins.push_back('S');
        }
        else if(c == 'W'){
            ins.push_back('E');
        }
        else if(c == 'E'){
            ins.push_back('W');
        }
        else{
            ins.push_back(c);
        }
    }

    a.instructions = ins;
    return a;

}
Piece rotatePieces270(Piece p){

    Piece a;
    a.name = p.name;

    vector<char> ins;

    for (char c: p.instructions) {
        if(c == 'S'){
            ins.push_back('E');
        }
        else if(c == 'N'){
            ins.push_back('W');
        }
        else if(c == 'W'){
            ins.push_back('S');
        }
        else if(c == 'E'){
            ins.push_back('N');
        }
        else{
            ins.push_back(c);
        }
    }

    a.instructions = ins;
    return a;

}

Piece horizontalFlip(Piece p){

    Piece a;
    a.name = p.name;

    vector<char> ins;

    for (char c: p.instructions) {
        if(c == 'S'){
            ins.push_back('S');
        }
        else if(c == 'N'){
            ins.push_back('N');
        }
        else if(c == 'W'){
            ins.push_back('E');
        }
        else if(c == 'E'){
            ins.push_back('W');
        }
        else{
            ins.push_back(c);
        }
    }

    a.instructions = ins;
    return a;

}

Piece verticleFlip(Piece p){

    Piece a;
    a.name = p.name;

    vector<char> ins;

    for (char c: p.instructions) {
        if(c == 'S'){
            ins.push_back('N');
        }
        else if(c == 'N'){
            ins.push_back('S');
        }
        else if(c == 'W'){
            ins.push_back('W');
        }
        else if(c == 'E'){
            ins.push_back('E');
        }
        else{
            ins.push_back(c);
        }
    }

    a.instructions = ins;
    return a;

}

vector<Coordinate> createCoordinatesFromPiece(Piece p, Coordinate start){
    int currx = start.x;
    int curry = start.y;

    Coordinate curr (curry, currx);

    vector<Coordinate> res;
    res.push_back(curr);

    for(char c : p.instructions){
        if(c == 'N'){
            curry--;
            res.push_back(Coordinate (curry, currx)); //check to see if out of bounds
        }
        else if(c == 'S'){
            curry++;
            res.push_back(Coordinate (curry, currx)); //check to see if out of bounds
        }
        else if(c == 'E'){
            currx++;
            res.push_back(Coordinate (curry, currx)); //check to see if out of bounds
        }
        else if(c == 'W'){
            currx--;
            res.push_back(Coordinate (curry, currx)); //check to see if out of bounds
        }
        else if(isdigit(c)){
            int m = c - '0';
            currx = res[res.size() - m - 1].x;
            curry = res[res.size() - m - 1].y;
        }
    }

    return res;
}


void createTileMatrix(vector<Piece> pieces, int h, int w, int numpieces){
    int row = 1;
    for(Piece p : pieces){
        for (int i = 0; i < h; ++i) { //i is y  coordinate

            for (int j = 0; j < w; ++j) { //j is x coordinate
                ProbMat[row][p.name - 65] = true;

                Coordinate start (i, j);
                vector<Coordinate> coordinates = createCoordinatesFromPiece(p, start);
                for (Coordinate c : coordinates) {
                    if(c.y >= h || c.y < 0 || c.x >= w || c.x < 0){ //tries to place the piece but goes out of board
                        for (int k = 0; k < h * w + numpieces; ++k) {//resets the entire row to false in order to save space
                            ProbMat[row][k] = false;
                        }
                        row--; //try the same row of ProbMat to save space
                        break;
                    }
                    else{
                        ProbMat[row][h * c.y + c.x + numpieces] = true;
                    }
                }

                row++;
            }

        }
    }
}

set<string> processResults(int h, int w, int numPieces){
    set<string> seq;
    for (int i = 0; i < results.size(); ++i) {
        char st [h * w ];
        for (int j = 0; j < results[i].size(); ++j) {
            char currChar = '0';
            for (int l = 0; l < numPieces; ++l) {
                if(ProbMat[results[i][j]][l]){
                    currChar = l + 65;
                    break;
                }
            }
            for (int k = numPieces; k < h * w + numPieces; ++k) {
                if (ProbMat[results[i][j]][k]) {
                    st[k - numPieces] = currChar;
                }

            }
        }
        string a = "";
        for(char b : st){
            a += b;
        }

        seq.emplace(a);
    }
    return seq;
}



string rotate90String(string a, int h, int w){
    string res;
    char arr [h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = a[w * i + j];
        }
    }
    for (int l = 0; l < w; ++l) {
        for (int k = h - 1; k >= 0; --k) {
            res += arr[k][l];
        }
    }
    return res;
}

string rotate180String(string a, int h, int w){
    string res;
    char arr [h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = a[w * i + j];
        }
    }
    for (int k = h - 1; k >= 0; --k) {
        for (int l = w - 1; l >= 0; --l) {
            res += arr[k][l];
        }

    }

    return res;
}

string rotate270String(string a, int h, int w){
    string res;
    char arr [h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = a[w * i + j];
        }
    }
    for (int k = h - 1; k >= 0; --k) {
        for (int l = 0; l < h; ++l) {
            res += arr[l][k];
        }
    }

    return res;
}

string horizontalFlipString(string a, int h, int w){
    string res;
    char arr [h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = a[w * i + j];
        }
    }
    for (int l = 0; l < h; ++l) {
        for (int k = w - 1; k >= 0 ; --k) {
            res += arr[l][k];
        }
    }


    return res;
}

string verticalFlipString(string a, int h, int w){
    string res;
    char arr [h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = a[w * i + j];
        }
    }
    for (int l = h - 1; l >= 0; --l) {
        for (int k = 0; k < w ; ++k) {
            res += arr[l][k];
        }
    }


    return res;
}

vector<string> removeReflectionsandRotations(set<string> s, int h, int w){
    set<string> seen;
    vector<string> res;
    for (string a : s) {
        if(!binary_search(seen.begin(), seen.end(), a)){
            seen.emplace(a);
            seen.emplace(rotate90String(a, h, w));
            seen.emplace(rotate180String(a, h, w));
            seen.emplace(rotate270String(a, h, w));
            seen.emplace(horizontalFlipString(a, h, w));
            seen.emplace(horizontalFlipString(rotate90String(a, h, w), h, w));
            seen.emplace(horizontalFlipString(rotate180String(a, h, w), h, w));
            seen.emplace(horizontalFlipString(rotate270String(a, h, w), h, w));
            seen.emplace(verticalFlipString(a, h, w));
            seen.emplace(verticalFlipString(rotate90String(a, h, w), h, w));
            seen.emplace(verticalFlipString(rotate180String(a, h, w), h, w));
            seen.emplace(verticalFlipString(rotate270String(a, h, w), h, w));
            seen.emplace(verticalFlipString(horizontalFlipString(a, h, w), h, w));
            res.push_back(a);

        }

    }
    return res;

}



int main(){
    /*
    * Input:
    * num of pieces and name
    * shape of piece
    * 0 w h (dimensions of board)
    * 
    *
    * Output:
    * n lines
    * A string of text of the name of the piece where 0 to width represents the first row, then width + 1 to 2 * width represents second row, and so on


    */
    Piece aam;
    aam.name = 'P';
    aam.instructions = {'E', '1', 'S'};

    createCoordinatesFromPiece(aam, Coordinate(0, 0));

    freopen("polycube.in", "r", stdin);
    int n;

    cin >> n;

    cin.ignore();

    vector<Piece> pieces;

    vector<char> ins;

    for (int i = 0; i < n; ++i) {
        string a;
        getline(cin, a);
        char tem [a.length() + 1];

        strcpy(tem, a.c_str());
        ins.insert(ins.end(), &tem[0], &tem[(sizeof(tem)/ sizeof(char)) - 1]);

        Piece b;
        b.name = i + 65;
        b.instructions = ins;

        pieces.push_back(b);
        pieces.push_back(rotatePieces90(b));
        pieces.push_back(horizontalFlip(rotatePieces90(b)));
        pieces.push_back(horizontalFlip(rotatePieces180(b)));
        pieces.push_back(horizontalFlip(rotatePieces270(b)));
        pieces.push_back(rotatePieces180(b));
        pieces.push_back(rotatePieces270(b));
        pieces.push_back(horizontalFlip(b));
        pieces.push_back(verticleFlip(b));
        pieces.push_back(verticleFlip(rotatePieces90(b)));
        pieces.push_back(verticleFlip(rotatePieces180(b)));
        pieces.push_back(verticleFlip(rotatePieces270(b)));
        pieces.push_back(verticleFlip(horizontalFlip(b)));

        ins.clear();

    }

    int d, w, h;


    cin >> d >> w >> h;

    d = 1;

    nRow = MAX_ROW;
    //nCol = n + w + h;
    nCol = n + w * h;

    for(int i=0; i<=nRow; i++){
        for(int j=0; j<nCol; j++){
            if(i == 0) ProbMat[i][j] = true;
            else ProbMat[i][j] = false;
        }
    }

    createTileMatrix(pieces, h, w, n);

    create4WayMatrix();

    search(0);


    set<string> allRes = processResults(h, w, n);

    vector<string> distinctResults = removeReflectionsandRotations(allRes, h, w);

    cout << distinctResults.size() << '\n';

    for (string a : distinctResults) {
        cout << a << '\n';
    }

    return 0;
}

