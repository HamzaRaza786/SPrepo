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
using namespace std;

int main(int argc, char *argv[])
	{
    if(argc == 3){
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];
	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Connect socket using name specified by command line. */
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
    //write(STDOUT_FILENO,"Hello\n",6);
	while(1) {
	char str2[120];
	int n = read(STDIN_FILENO,str2,120);
	str2[n-1] = '\0';
	int c = write(sock,str2,n);
            if(c == -1){
                perror("Error write in pipe child 1:");
                exit(0);}
    char* t = strtok(str2," ");
	if(strcmp(str2,"list") == 0){
                char lstr[2000];
                int c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
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
                }}
                }
                }
            else if(strcmp(str2,"listall") == 0 ){
                char lstr[2000];
                int c = read(sock,lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                write(STDOUT_FILENO,"All Processes:\n",18);
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
            //write(STDOUT_FILENO,"he\n",2);
            char sum2[200];
            c = read(sock,sum2,1000);
            if(c == -1){
                perror("Error read in pipe child 1:");
                exit(0);
            }
            sum2[c] = '\0';
            if(strcmp(sum2,"exit") == 0){
                exit(0);
            }
            else{
            int ch = write(STDOUT_FILENO,sum2,c);
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
	close(sock);
}
else if(argc < 3){
    write(STDOUT_FILENO,"Kindly write port number and IP\n",32);
    exit(0);
}
else{
    write(STDOUT_FILENO,"Kindly write only port number and IP\n",37);
    exit(0);
}}
