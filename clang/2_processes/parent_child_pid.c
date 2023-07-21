#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

//전역 변수 설정
int value = 5;

int main(){

    pid_t pid; 
    pid = fork();

    if (pid == 0){
        //자식 프로세스
        //부모프로세스에서 fork 이후 밸류가 15가 되지만 리턴되면서 끝나기 때문에
        //최종 출력값은 5만 나온다. 
        value += 15; 
        return 0;
    }
    else if (pid > 0){
        //부모 프로세스
        wait(NULL);
        printf("Parent: value = %d\n", value);
    }
}