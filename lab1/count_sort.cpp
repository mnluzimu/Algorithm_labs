#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
using namespace std;
#define MAX_SIZE 262149
#define MAX_VAL 32770
int n[6] = {8, 64, 512, 4096, 32768, 262144};
#define N_SIZE 6

void count_sort(int a[], int b[], int cnt[], int n){
    memset(cnt, 0, MAX_VAL * sizeof(int));
    for(int i = 0; i < n; i++){
        cnt[a[i]]++;
    }
    for(int i = 1; i < MAX_VAL; i++){
        cnt[i] = cnt[i] + cnt[i - 1];
    }
    memcpy(b, a, n * sizeof(int));
    for(int i = n - 1; i >= 0; i--){
        a[cnt[b[i]] - 1] = b[i];
        cnt[b[i]]--;
    }
}

int a[MAX_SIZE];
int b[MAX_SIZE];
int cnt[MAX_VAL];

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
        count_sort(a, b, cnt, n[j]);	//要计时的程序
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