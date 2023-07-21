#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
    wait(NULL);
    // LINE A
    } else {
    pid = fork();
    
    if (pid == 0) {
    // LINE B
    } else {
    wait(NULL);
    // LINE C
    }
    }
    // LINE D
}