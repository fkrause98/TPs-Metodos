#include <type_traits>
#include <utility>
#include <unordered_map>
#include <algorithm>
using namespace std;
template <typename T>
struct Matrix {
    int N;
    int M;
    unordered_map<int, unordered_map<int, T>> values;
    Matrix(int N, int M){
        this->N = N;
        this->M = M;
        for(int i = 0; i <= N; i++)
            values[i] = {};
    }
    unordered_map<int, T> operator[](int row){
        return values[row];
    }
    void set(int i, int j, T value){
        if(i > this->N || j > M)
            return;
        this->values[i][j] = value;
    }
};
