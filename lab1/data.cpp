#include<cstdlib>
#include<cstdio>
#include<time.h>

int main(){
    FILE* fp;
    if((fp = fopen("data.txt", "w")) == NULL){
        printf("cannot open file!\n");
    }
    printf("%d\n", RAND_MAX);
    srand((unsigned int)time(NULL));
    for(int i = 0; i < 262144 + 5; i++){//262144=2^18
        int ran = rand();
        fprintf(fp, "%d\n", ran);
    }
    return 0;
}
