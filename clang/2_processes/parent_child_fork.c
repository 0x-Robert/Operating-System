#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>

int main(){

    pid_t pid; 
    pid  =  fork();
    printf("Hello, Process %d\n", pid);

    return 0;
}