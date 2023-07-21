#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(){

    pid_t pid, pid1;
    pid = fork();

    if (pid == 0){ //child process
        pid1 = getpid(); 
        printf("A - child: pid >> 0  %d\n",pid); // A pid가 0
        printf("B - child: pid1 >> child = %d\n",pid1); //B pid가 child pid 
    }
    else if (pid > 0) { //parent process 
        wait(NULL);
        pid1 = getpid();
        printf("C - parent: pid >> child = %d\n",pid); //C pid가 child pid 
        printf("D - parent: pid1 >> parent = %d\n",pid1); //D 부모 pid
        //wait(NULL);
    }
    return 0;
}