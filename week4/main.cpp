#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    /* Tuesday
    int pid = fork();
    write(STDOUT_FILENO,"HI1\n",4);
    if (pid > 0){
        write(STDOUT_FILENO,"HI2\n",4);
        write(STDOUT_FILENO,"I am in parent\n",15);

    }
    else if (pid == 0){
        write(STDOUT_FILENO,"HI3\n",4);
        write(STDOUT_FILENO,"I am in child\n",14);
    }
    else {
        perror("Fork Fail");
        getchar();
        }
    write(STDOUT_FILENO,"HI4\n",4);
    getchar();
    write(STDOUT_FILENO,"HI5\n",4);
 */

 /* Thursday */
 /*
int fd1 = open("file.txt",O_RDWR | O_TRUNC);
int pid = fork();
write(fd1,"ABC",3);
int fd2 = open("file.txt",O_RDWR | O_APPEND);
write(fd2,"XYZ",3);
if (pid == 0){
    int fd3 = open("file.txt",O_RDWR);
    write(fd3,"123",3);
}
else if(pid>0){
int fd3 = open("file.txt",O_RDWR);
write(fd3,"LMN",3);
}*/

 /* Task 2 */
 open("file.txt",O_TRUNC);
 int fd1 = open("file2.txt",O_RDWR | O_APPEND);
 write(fd1,"123456",6);
 int fd2 = open("file2.txt",O_RDWR | O_TRUNC);
 write(fd2,"A",1);
 write(fd1,"910",3);
    return 0;
}
