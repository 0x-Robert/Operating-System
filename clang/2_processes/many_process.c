#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <wait.h> 

int main(){
    fork(); //자식 프로세스 포크 / 총 프로세스 2개 / P0, P1
    fork(); //다른 자식 프로세스 포크  / 총 프로세스 4개 / P0, P2, P1, P3 
    fork(); //다른 자식 프로세스 포크  / 총 프로세스 8개 / P0, P4, P2, P5, P1, P6, P3, P7
    printf("Hello Process! \n");
    return 0;
    //총 프로세스는 8개가 생긴다.
}
