#include <iterator>
#include <type_traits>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <vector>
using namespace std;
double epsilon = 1e-4;
template <typename Num>
bool is_zero(Num x){
   return (abs(x) < epsilon);
}
template <typename Num>
struct Matrix {
    int N;
    int M;
    unordered_map<int, unordered_map<int, Num>> values;
    Matrix(){
        this->values = {};
    }
    Matrix(int N, int M){
        this->N = N;
        this->M = M;
        for(int i = 0; i <= N; i++)
            values[i] = {};
    }
    Matrix(int N, int M, vector<vector<Num>> vec_matrix){
        this->N = N;
        this->M = M;
        for(int i = 0; i <= N; i++)
            values[i] = {};

        for(int i = 0; i < vec_matrix.size(); i++){
            auto row = vec_matrix[i];
            for(int j = 0; j < row.size(); j++){
                this->set(i, j, vec_matrix[i][j]);
            }
        }
    }
    unordered_map<int, Num> operator[](int row){
        return values[row];
    }
    void set(int i, int j, Num value){
        // cout << "Received value: " << value << endl;
        if(i > this->N || j > this->N || is_zero(value)){
            return;
        }
        // if(i > this->N || j > this->N)
        //     return;
        this->values[i][j] = value;
    }
    void swap_rows(int row1, int row2){
       unordered_map<int, Num> tmp;
       tmp = values[row1];
       values[row1] = values[row2];
       values[row2] = tmp;
    }
    void gaussian_form() {
      auto n = this->N;
      for (int i = 0; i < (n - 1); i++) {
        // cout << "i: " << i << endl;
        if (!(is_zero(this->values[i][i]))) {
        // if (abs(this->values[i][i]) > epsilon) {
          for (int j = i + 1; j < n; j++) {
            if (!(is_zero(this->values[j][i]))) {
              Num m = (this->values[j][i]) / (this->values[i][i]);
              // cout << "m: " << m << endl;
              for (int k = i; k <= n; k++) {
                  Num res = this->values[j][k] - (m * (this->values[i][k]));
                  // cout << "res: " << res << endl;
                  this->set(j,k, res);
              }
            }
          }
        } else {
            bool non_zero = false;
            int j = i;
            while(!non_zero && j < n){
                j++;
                non_zero = !(is_zero(this->values[j][i]));
            }
            if(j != n){
               this->swap_rows(i, j);
               i--;
            }
        }
      }
    }
    void gaussian_upper_form() {
      auto n = this->N;
      for (int i = n-2; i > 0; i--) {
        if (!is_zero(this->values[i][i])) {
          for (int j = i - 1; j >= 0; j--) {
            if (!is_zero(this->values[j][i])) {
              Num m = (this->values[j][i]) / (this->values[i][i]);
              // cout << "m: " << m << endl;
              for (int k = n; k > i; k--) {
                  Num res = this->values[j][k] - (m * (this->values[i][k]));
                  // cout << "res: " << res << endl;
                  this->set(j, k, res);
              }
            }
          }
        } else {
            bool non_zero = false;
            int j = i;
            while(!non_zero && j >= 0){
                j--;
                non_zero = !is_zero(this->values[j][i]);
            }
            if(j != 0){
               this->swap_rows(i, j);
               i++;
            }
        }
      }
    }
    void print() {
      cout << "-----------" << endl;
      for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->N; j++) {
          cout << " " << this->values[i][j] << " ";
          // cout << "(" << i << ", " << j << ") " << " " << this->values[i][j] << " ";
        }
        cout << endl;
      }
      cout << "-----------" << endl;
    }
    Num get_cj(int column){
        Num cj = 0;
        for(int i = 0; i < this->N; i++)
            cj += this->values[i][column];
        return cj;
    }
    void times_scalar(Num scalar) {
        for (auto it_row = this->values.begin(); it_row != this->values.end();
             ++it_row) {
            int index_row = it_row->first;
            for (auto it_column = it_row->second.begin();
                 it_column != it_row->second.end(); ++it_column) {
                int index_column = it_column->first;
                double to_set = (this->values[index_row][index_column]) * scalar;
                this->set(index_row, index_column, to_set);
            }
        }
    }
    void extend_with_ones() {
        this->N = (this->N) + 1;
        int n = this->N;
        this->M = (this->M)+(n-1);
        for(int i = 0; i < n-1; i++){
           this->set(i, n-1, 1);
        } 
    }
};
Matrix<double> file_to_W_matrix(string path, float p);
Matrix<double> W_to_D_matrix(Matrix <double> W);
Matrix<double> W_times_D(Matrix<double> W, Matrix<double> D);
Matrix<double> gauss_test();
template <typename Num>
Matrix<Num> Matrix_mul_diag(Matrix<Num> A, Matrix<Num> diagonal);
