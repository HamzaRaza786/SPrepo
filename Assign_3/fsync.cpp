#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <ctime>
using namespace std;
int copy_file(char* str)
{
    char line[2000];
    int fd = open("copy4.txt",O_RDWR | O_CREAT| O_TRUNC,S_IRWXU);
    int fd2 = open(str,O_RDWR);
    if (fd2 == -1){
        perror("Error");
        exit(0);
    }
    int c = read(fd2,line,1000);
    if(c == -1){
        perror("Error");
        exit(0);
    }
    while (c > 0){
        int ch = write(fd,line,c);
        if(ch == -1){
        perror("Error");
        exit(0);
    }
        ch = fsync(fd);
        if(ch == -1){
        perror("Error");
        exit(0);
    }
        c = read(fd2,line,1000);
        if(c == -1){
        perror("Error");
        exit(0);
    }
    }
    write(STDOUT_FILENO,"File written \n",14);
    return 0;

}
int main()
{
    time_t now = time(0);
   char* dt = ctime(&now);
   write(STDOUT_FILENO,dt,25);
   char path[200] = "file.txt";
   copy_file(path);
    now = time(0);
   char* dt_aft = ctime(&now);
   write(STDOUT_FILENO,dt_aft,25);
    return 0;
}
