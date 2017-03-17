#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
using namespace std;

const int N = 6, M = 3;
const int n[N] = {1000, 5000, 10000, 50000, 100000, 500000};
const int m[M] = {100, 500, 1000};

int main() {

    string name = "data(";
    string format = ").in";
    fstream file;
    int cas = 1;

    mt19937 mt(time(NULL));
    uniform_int_distribution<int> dis(0, 25);

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++) {

            string filename = "";
            filename = filename + name + to_string(cas++) + format;
            file.open(filename, ios::out);

            file << m[i] << " " << n[j] << endl;
            for(int k = 0; k < n[j]; k++) {
                string tmp = "";

                for(int l = 0; l < m[i]; l++)
                    tmp += 'a' + dis(mt);
                file << tmp << endl;
            }

            file << endl;
            file.close();
        }


    return 0;
}
