#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

int left[35];
int right[35];
bool left_mark[60];

void gen_left (int a, int b, int n, int begin) {
    for (int i = begin; i < begin + n; i++) {
        int tmp;
        tmp = a + (int)(b - a) * rand() / (RAND_MAX + 1);
        while (left_mark[tmp] == true) tmp = a + (int)(b - a) * rand() / (RAND_MAX + 1);
        left[i] = tmp;
        left_mark[tmp] = true;
    }
}

void gen_right (int a, int b, int n, int begin) {
    for (int i = begin; i < begin + n; i++) {
        right[i] = left[i] + (int)(b - left[i]) * rand() / (RAND_MAX + 1);
    }
}


int main() {
    for (int i = 0; i < 60; i++) {
        left_mark[i] = false;
    }
    int left_num = 10 + (int)10 * rand() / (RAND_MAX + 1);
    int right_num = 30 - left_num;
    gen_left(0, 25, left_num, 0);
    gen_right(0, 25, left_num, 0);
    gen_left(30, 50, right_num, left_num);
    gen_right(30, 50, right_num, left_num);
    std::ofstream ofs;
    ofs.open("input.txt", std::ios::out);
    for (int i = 0; i < 30; i++) {
        ofs << left[i] << " " << right[i] << std::endl;
    }
    ofs.close();
    return 0;
}