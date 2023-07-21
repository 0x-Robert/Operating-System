#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <wait.h> 

int main(){
 
 //총 프로세스 16개 
 int i;
 pid_t pid;

 for (i=0; i < 4; i++)
    pid = fork(); 
    printf("Hello Fork! %d\n",pid);
    return 0;
}
