#include <iostream>
#include <unistd.h>
#include<signal.h>
#include<wait.h>
using namespace std;
static void signal_handler(int sig){
if(sig == SIGCHLD){
    write(STDOUT_FILENO,"Child Terminated\n",17);
    int sta;
    int pid = waitpid(0,&sta,WNOHANG|WUNTRACED);
    char s[200];
    int c = sprintf(s,"%d",pid);
    write(STDOUT_FILENO,s,c);

    }
}

int main()
{
    int pifd[2];
    pipe(pifd);
    char str[200];
   while(true){
    char *paramlist[] = {NULL};
    int pid = fork();
    if(pid==0){
        char s[200];
        read(pifd[0],s,200);
        execvp(s,paramlist);
    }
    else if(pid>0){
    int c =read(STDIN_FILENO,str,100);
    str[c-1] = '\0';
    write(pifd[1],str,c);
    if (signal(SIGCHLD,signal_handler) == SIG_ERR) {
      perror("signal error: ");
      return 1;
    }
    for(;;)
        pause;
    }
    }
return 0;
}
