#include <iostream>
#include<unistd.h>
#include<signal.h>
#include<cstring>
#include<string>
using namespace std;
int kill_p(int pid){
int err = kill(pid,SIGTERM);
if(err == -1){
    perror("Error");
    exit(0);
}
return 0;
}
int main(int argc,char *argv[])
{
    /*int pid = fork();
    if (pid > 0){
         cout<<"I am in parent"<<endl;
        getchar();
    }
    else if (pid == 0){
        cout<<"I am in child"<<endl;
        kill(getppid(),SIGTERM);
    }*/
    /*int pid;
    sscanf(argv[1],"%d",&pid);
    kill_p(pid);*/
    char sk[200];
    char *sk2=sk;
    int c = sprintf(sk,"%d",argc);
    write(STDOUT_FILENO,sk,c);
    char* str;
    for(int i = 0;i<argc;i++){
        //argv[i]  += " ";
        int siz = strlen(argv[i]);
        //argv[i][siz - 2] = '\0';
        write(STDOUT_FILENO,argv[i],siz);
        write(STDOUT_FILENO," ",1);
    }
return 0;
}
