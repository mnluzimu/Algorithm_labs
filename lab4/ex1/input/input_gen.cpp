#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;
const int N[4] = {27, 81, 243, 729};
const int l[2] = {5, 7};
string infileName[4][2] = {{"input11.txt", "input12.txt"}, {"input21.txt", "input22.txt"}, {"input31.txt", "input32.txt"}, {"input41.txt", "input42.txt"}};
const int MAX_SIZE = 1000;
bool edges[MAX_SIZE][MAX_SIZE];

int main() {
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 2; n++) {
            int k = (int)(log(N[m])/log(l[n]));
            ofstream ofs;
            string infile = infileName[m][n];
            ofs.open(infile.c_str(), ios::out);
            for (int i = 0; i < N[m]; i++) {
                for (int j = 0; j < k; j++) {
                    int v = (int) rand() * N[m] / RAND_MAX;
                    while (edges[i][v] == true) {
                        v = (int) rand() * N[m] / RAND_MAX;
                    }
                    int w = - 10 + (int) rand() * 60 / RAND_MAX;
                    ofs << i << " " << v << " " << w << endl;
                    edges[i][v] = true;
                }
            }
            ofs.close();
        }
    }
    return 0;
}