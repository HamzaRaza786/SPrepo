#include <iostream>
#include<unistd.h>
using namespace std;
struct student{
    int roll;
    char le;
    //char name[20];
};
int main()
{
    int pifd[2];
    int p = pipe(pifd);
    int pid = fork();
    if(pid == 0){
        close(pifd[0]);
        struct student a;
        a.roll = 20;
        a.le = 'H';
        write(pifd[1],&a,sizeof(a));
    }
    else if(pid>0){
        close(pifd[1]);
        struct student b;
        read(pifd[0],&b,sizeof(b));
        cout<<b.le<<endl;
        cout<<b.roll<<endl;
        int c = (int) 'b';
        cout<<c;
    }
    return 0;
}
