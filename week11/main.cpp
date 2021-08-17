#include <iostream>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;
static void signit_handler(int sig){
    if(sig == SIGUSR1){
    write(STDOUT_FILENO,"Inchild\n",8);}
}
static void signit_handler2(int sig){
     if(sig == SIGUSR2){
    write(STDOUT_FILENO,"Inparent\n",9);}
}

int main()
{
   int pid = fork();
   if(pid > 0){
    int fd = open("a.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
    if ( signal(SIGUSR2,signit_handler2) == SIG_ERR) {
      perror("signal error: ");
      return 1;
   }
    while(true){
    write(fd,"1 2",3);
    kill(pid,SIGUSR1);
    for(;;)
        pause();

    }
   }
   if(pid == 0){
        int fd = open("a.txt",O_RDWR);
        if ( signal(SIGUSR1,signit_handler) == SIG_ERR) {
      perror("signal error: ");
      return 1;
   }
        while(true){
        write(STDOUT_FILENO,"hello child\n",12);
         for(;;)
        pause();
       write(STDOUT_FILENO,"hello",5);
        char s[200];
        int a;
        int b;
        read(fd,s,3);
        sscanf(s,"%d %d",&a,&b);
        int c = sprintf(s,"%d",a+b);
        write(STDOUT_FILENO,s,c);
        kill(getppid(),SIGUSR2);
        }
   }
}
