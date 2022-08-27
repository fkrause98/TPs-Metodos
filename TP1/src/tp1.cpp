#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "matrix.h"
using namespace std;


Matrix<double> read_test(string path, float p){
        // Read file as stream
        ifstream stream(path);
        // Use line as buffer
        string line;

        // First line is n,
        // number of pages.
        getline(stream, line);
        int n = stoi(line);

        // Second line is m, number
        // of links.
        getline(stream, line);
        int m = stoi(line);

        Matrix<double> A(n, m);
        for(int k = 1; k <= m; k++){
            getline(stream, line);
            int split = line.find(" ");
            string fst = line.substr(0, split);
            string snd = line.substr(split);
            int i = stod(fst);
            int j = stod(snd);
            A.set(i, j, 1);
        }
        return A;
}
int main(int argc, char *argv[]) {
    if(argc != 3){
        cout << "Numero incorrecto de argumentos" << endl;
        return -1;
    }
    string file_path = argv[1];
    float p_value = atof(argv[2]);
    cout << "Reading file: " << (file_path) << endl << "P: " << p_value << endl;
    read_test(file_path, p_value);
    return 0;
}
