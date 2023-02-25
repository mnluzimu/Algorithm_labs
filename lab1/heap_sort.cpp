#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <algorithm>
using namespace std;
#define MAX_SIZE 262149
#define N_SIZE 6

int n[6] = {8, 64, 512, 4096, 32768, 262144};

void HeapAdjust(int a[], int s, int t){
    int w = a[s];
    int i;
    for(i = 2 * s; i <= t; i *= 2){
        if(i < t)
            i = (a[i] > a[i + 1]) ? i : i + 1;
        if(w >= a[i]) break;
        a[s] = a[i];
        s = i;
    }
    a[s] = w;
}

void HeapSort(int a[], int n){
    for(int i = n / 2; i >= 0; i--)
        HeapAdjust(a, i, n - 1);
    for(int i = n - 1; i >= 1; i--){
        swap(a[0], a[i]);
        HeapAdjust(a, 0, i - 1);
    }
}

int a[MAX_SIZE];

int main(){
    FILE* fp;
    if((fp = fopen("data.txt", "r")) == NULL){
        printf("cannot open file!\n");
    }
    for(int j = 0; j < N_SIZE; j++){
        for(int i = 0; i < n[j]; i++){
            fscanf(fp, "%d", & a[i]);
        }
        
        double run_time;
        _LARGE_INTEGER time_start;	//开始时间
        _LARGE_INTEGER time_over;	//结束时间
        double dqFreq;		//计时器频率
        LARGE_INTEGER f;	//计时器频率
        QueryPerformanceFrequency(&f);
        dqFreq=(double)f.QuadPart;
        QueryPerformanceCounter(&time_start);	//计时开始
        HeapSort(a, n[j]);	//要计时的程序
        QueryPerformanceCounter(&time_over);	//计时结束
        run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
        //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
        printf("\nrun_time: %fus\n",run_time);
        // for(int i = 0; i < n[j]; i++){
        //     printf("%d ", a[i]);
        // }
        // printf("\n\n");
    }
    return 0;
}