#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
using namespace std;
int add(char* str,int sum){
    int a;
    //("Hello");
    //cout << "Hello" << endl;
    char* tok = strtok(str," ");
    //cout<<tok<<endl;
    while(tok != NULL){
        sscanf(tok,"%d",&a);
        sum+=a;
        tok = strtok(NULL," ");
    }
    return sum;
    //cout << "Hello" << endl;
   // return sum;

}


int main()
{
   // int fd = open("file.txt",O_RDWR | O_CREAT|O_TRUNC,S_IRWXO);
    int pifd[2];
    int p = pipe(pifd);

    int pifd2[2];
    int p2 = pipe(pifd2);
    int pid = fork();

    //cout << pid << endl;
   if(pid > 0){
        char s[200];
        char s2[200];
        close(pifd[0]);
        close(pifd2[1]);
        write(STDOUT_FILENO,"Enter Numbers  ",15);
        int c = read(STDIN_FILENO,s,100);
        //cout<<c;
        if(c == -1){
            perror("Error");
        }
        write(pifd[1],s,c);
        c = read(pifd2[0],s2,100);
        write(STDOUT_FILENO,s2,c);
        }
    else if(pid == 0){
    char chi[200];
    int sum = 0;
    //write(STDOUT_FILENO,"h",1);
    close(pifd[1]);
    close(pifd2[0]);
    int c = read(pifd[0],chi,1000);
    chi[c - 1]='\0';
        //chi[c - 1] = '\0';
    //int a;
    //("Hello");
    //cout << chi << endl;
/*char*    token = strtok(chi," ");
    int val;
    while(token != NULL){
        sscanf(token,"%d",&val);
            sum += val;
            token = strtok(NULL," ");

    }*/sum = add(chi,sum);
        //c = read(pifd[,chi,1);
        //cout << chi << endl;
        //
    //cout<<sum<<endl;
    //cout<<"hello";
    char stsum[200];
    int a,b;
    //int co = sscanf(chi,"%d %d",a,b);
    int l = sprintf(stsum,"%d",sum);
    if (l == -1){
        perror("Error");
        exit(0);
    }
    //cout << stsum;
   write(pifd2[1],stsum,l);
    }
    /*else{
        perror("Error");
        exit(0);
    }*/
    return 0;
}
