#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
using namespace std;

int main()
{
    /*Tuesday
    char *ptr[500];
    //strcpy(ptr[0],"ABC");
   // ptr[0] = "ABC";
    //char *ptr1 = "ABC";
    //printf("%d",strcmp(ptr[0],ptr1));

    //char buff[500];
    //strcpy(buff[0],"ABC");
    //strcmp(buff[0],"ABC");

    int fd = open("a.txt",O_RDWR | O_CREAT | O_APPEND,S_IRWXO);
    write(fd,"123",3);
    //strcpy(ptr[0],"ABC");
    getchar();*/


    /*Thursday*/

   /* int fd = open("a.txt",O_RDWR | O_CREAT | O_TRUNC,S_IRWXO);
    fork();
    write(fd,"Hello",5);
    close(fd);*/



    /*int fd = open("af.txt",O_RDONLY | O_CREAT);
    int err = write(fd,"HELLO",5);
    if (err == -1){
        perror("Error");
    }*/

    /*int fd = open("a.txt",O_RDWR);
    getchar();
    int err = write(fd,"Hello",5);
    if (err == -1){
        perror("Error");
    }
    write(fd,"HI",2);*/

    /*int fd = open("af.txt",O_RDONLY);
    int err = write(fd, "hello",5);
     if (err == -1){
        perror("Error");
    }*/
    int fd = open("a.txt",O_RDWR | O_SYNC);
    if (fd == -1){
        perror("Error");
        printf("%d\n",errno);
        printf("%d\n",EACCES);
     }
     getchar();
    int err = write(fd, "hello",5);
     if (err == -1){
        perror("Error");
     }

    /* char *ptr;
     &ptr = "20";
     int fd = open(ptr,O_RDONLY);
      if (fd == -1){
        perror("Error");
        printf("%d\n",errno);
        printf("%d\n",EACCES);
     }*/
    return 0;
}
