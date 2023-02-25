#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <time.h>

#include <windows.h>

using namespace std;
#define MAX_SIZE 262149
#define N_SIZE 6

int n[6] = {8, 64, 512, 4096, 32768, 262144};

int partition(int a[], int i, int r, int pivot){
    int l = i - 1;
    do{
        while(a[++l] < pivot);
        while(r >= i && a[--r] > pivot);
        swap(a[l], a[r]);
    }while(l < r);
    swap(a[l], a[r]);
    return l;
}

void QuickSort(int a[], int i, int j){
    int pivotIndex = (i + j) / 2;
    swap(a[pivotIndex], a[j]);
    int k = partition(a, i, j, a[j]);
    swap(a[k], a[j]);
    if(k - i > 1) QuickSort(a, i, k - 1);
    if(j - k > 1) QuickSort(a, k + 1, j);
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
        QuickSort(a, 0, n[j] - 1);	//要计时的程序
        QueryPerformanceCounter(&time_over);	//计时结束
        run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
        //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
        printf("\nrun_time: %fus\n",run_time);

        // for(int i = 0; i < n[j]; i++){
        //     printf("%d ", a[i]);
        // }
    }
    return 0;
}