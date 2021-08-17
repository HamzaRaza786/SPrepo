#include <iostream>
#include<fstream>
#include <fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<err.h>
using namespace std;

int copy_file(char str[])
{
    char line[52];
    int fd = open("copy.txt",O_RDWR | O_CREAT,S_IRWXO);
    int fd2 = open(str,O_RDWR);
    if (fd2 == -1){
        perror("Error");
        exit(0);
    }
    int c = read(fd2,line,50);
    while (c > 0){
        write(fd,line,c);
        c = read(fd2,line,50);
    }
    return 0;

}

int main()
{
    /* Tuesday

    int i =0;
    char s[50];
    int filedes = open("e.txt",O_RDWR | O_CREAT);
    if (filedes == -1){
        perror("Error: ");
        exit(0);
    }
    /*int c =read(filedes,s,50);
    while(c > 0){
    write(STDOUT_FILENO,s,c);
    c = read(filedes,s,50);
    }*/

    /*Thursday
    write(filedes,"ABCD",4);
    if(errno != 0){
        perror("Error: ");
    }*/

    /* Assignment */
    copy_file("/home/hamza/file.txt");

    return 0;
}
