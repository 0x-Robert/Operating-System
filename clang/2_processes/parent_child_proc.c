#include    <stdio.h>
#include    <unistd.h> 
#include     <wait.h>


int main()
{
    pid_t pid;
    // fork a child process
    pid = fork();
    
    if (pid < 0) { // error occurred
         fprintf(stderr, "Fork Failed");
         return 1;
    }
    else if (pid == 0) { // child process
          execlp("/bin/ls", "ls", NULL);
           printf("Line J\n"); //동작하지 않음 위의 execlp로 인해 ls로 모든게 대체됨
    }
    else { // parent process
           wait(NULL);
          printf("Child Complete");
    }
    return 0;
}