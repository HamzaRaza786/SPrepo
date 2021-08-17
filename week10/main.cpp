#include <iostream>
#include<unistd.h>
#include<signal.h>
#include<cstring>
#include<list>
using namespace std;

int main()
{
   /* int pid = fork();
    if(pid > 0){
        //cout<<"hello";
    }
    if(pid == 0){
        kill(getppid(),SIGTERM);
        sleep(3);
        cout<<getppid();

    }*/
    list<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);
    c.push_back(5);
    write(STDOUT_FILENO,&c,sizeof(c));


}
