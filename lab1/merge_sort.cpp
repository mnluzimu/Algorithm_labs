#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
using namespace std;
#define MAX_SIZE 262149

#define N_SIZE 6

int n[6] = {8, 64, 512, 4096, 32768, 262144};

void merge(int a[], int b[], int l, int m, int r){
    memcpy(b + l, a + l, (r - l + 1) * sizeof(int));
    int indx1, indx2, indx;
    indx1 = l;
    indx2 = m + 1;
    indx = l;
    while(indx1 <= m && indx2 <= r){
        if(b[indx1] < b[indx2]){
            a[indx++] = b[indx1++];
        }
        else{
            a[indx++] = b[indx2++];
        }
    }
    while(indx1 <= m){
        a[indx++] = b[indx1++];
    }
    while(indx2 <= r){
        a[indx++] = b[indx2++];
    }
}

void merge_sort(int a[], int b[], int l, int r){
    if(l == r) return;
    int m = (l + r) / 2;
    merge_sort(a, b, l, m);
    merge_sort(a, b, m + 1, r);
    merge(a, b, l, m, r);
}

int a[MAX_SIZE];
int b[MAX_SIZE];


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
        merge_sort(a, b, 0, n[j] - 1);	//要计时的程序
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