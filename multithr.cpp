#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<strings.h>
#include<cstring>
#include<pthread.h>
#include<errno.h>
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;
char str2[120] = "-1";
int sock;
bool wr = false;
bool fin = false;
void *read_client(void *msg){
    while(fin != true){
    int n = read(STDIN_FILENO,str2,120);
	str2[n-1] = '\0';
	int c = write(sock,str2,n);
    wr = true;
            if(c == -1){
                perror("Error write in socket");
                //fin = true;
                exit(0);

            }}
    return 0;
}
void *write_client(void *msg){
   // int c = 0;
    while(true){
    char temp[20];
    int co = read(sock,temp,1);
     if(co==0){
            write(STDOUT_FILENO,"Server Closed\n",14);
            exit(0);
        }
    if(strcmp(temp,"0") == 0){
                //write(STDOUT_FILENO,"Inlist\n",7);
                char lstr[2000];
                int c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    fin = true;
                    exit(0);

                }
                if(c==0){
                    write(STDOUT_FILENO,"Server Closed\n",14);
                    fin = true;
                    exit(0);
                }
                write(STDOUT_FILENO,"Active Processes:\n",18);
                while(true){
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                }
                }
            }
            else if(strcmp(temp,"1") == 0 ){
                char lstr[2000];
                int c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                if(c==0){
                    write(STDOUT_FILENO,"Server Closed\n",14);
                    fin = true;
                    exit(0);
                }
                write(STDOUT_FILENO,"All Processes:\n",15);
                 while(true){
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }}
                 }
            }
            else{
           // write(STDOUT_FILENO,"he\n",2);
            char sum2[200];
            int c = read(sock,sum2,1000);
            //write(STDOUT_FILENO,sum2,c);
           // printf("%d",c);
            //getchar();
            if(c == -1){
                perror("Error read in pipe child 1:");
                exit(0);
            }
            if(c==0){
                    write(STDOUT_FILENO,"Server Closed\n",14);
                    exit(0);
                }
            sum2[c] = '\0';
            if(strcmp(sum2,"exit") == 0){
                exit(0);
            }
            else{
            int ch = write(STDOUT_FILENO,sum2,c);
           // write(STDOUT_FILENO,"he\n",2);
            if(ch == -1){
                perror("Error write:");
                exit(0);
            }
            ch = write(STDOUT_FILENO,"\n",1);
            if(ch == -1){
                perror("Error write:");
                exit(0);
            }
        }
        }
        }
        return 0;
}
int main(int argc, char *argv[])
	{
    if(argc == 3){
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
    server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
	server.sin_port = htons(atoi(argv[2]));
	if (connect(sock,(struct sockaddr *) &server,sizeof(server)) < 0) {
        //
		perror("connecting stream socket");
		exit(1);
	}
	pthread_t thread1,thread2;
	int iret1,iret2;
    /*pthread_attr_t t1,t2;
    pthread_attr_t *at1,*at2;
    at1 = &t1;
    at2 = &t2;
	//while(fin != true) {
    pthread_attr_init(&t2);
    int s = pthread_attr_init(&t1);
    if (s != 0)
        handle_error_en(s, "pthread_attr_init");
    s = pthread_attr_init(&t2);
    if (s != 0)
        handle_error_en(s, "pthread_attr_init");
    s = pthread_attr_setdetachstate(&t1, PTHREAD_CREATE_DETACHED);
    if (s != 0)
        handle_error_en(s, "pthread_attr_setdetachstate");
    s = pthread_attr_setdetachstate(&t2, PTHREAD_CREATE_DETACHED);
    if (s != 0)
        handle_error_en(s, "pthread_attr_setdetachstate");
    iret1 = pthread_create( &thread1, NULL, read_client, NULL);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() 1 return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }*/
     iret2 = pthread_create( &thread2, NULL, write_client, NULL);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() 2 return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }
    pthread_detach(thread2);
	while(true){
    int n = read(STDIN_FILENO,str2,120);
	str2[n-1] = '\0';
	int c = write(sock,str2,n);
    //perror("ERROR:");
            if(c == -1){
                perror("Error write in pipe child 1:");
                exit(0);
    }
	}close(sock);
}
else if(argc < 3){
    write(STDOUT_FILENO,"Kindly write port number and IP\n",32);
    exit(0);
}
else{
    write(STDOUT_FILENO,"Kindly write only port number and IP\n",37);
    exit(0);
}}


