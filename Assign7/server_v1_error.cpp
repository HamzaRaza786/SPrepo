#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<strings.h>
#include<cstring>
#include<ctime>
#include<time.h>
#include<list>
#include<signal.h>
#include<fcntl.h>
#include<wait.h>
#include<errno.h>
#include<iostream>
#include<pthread.h>
#include<string>
#define TRUE 1
using namespace std;
char read_str[200];
int pipefd[2];
int pipefd2[2];
int msgsock;
struct Process{
    int pid;
    char name[200];
    int ppid;
    time_t starttime;
    bool active;
    time_t endtime;
    double elapsed_time;
};
struct client_han{
    int pid;
    char* cli_adr;
    int po;
    int pfd[2];
    int pfd2[2];
    int msg;
};
list<Process> li;
list<client_han> ch_li;
void write_list_active(int pifd2){
    list <Process> :: iterator it;
    for(it = li.begin(); it != li.end(); ++it) {
            if(it->active == 1){
            it->elapsed_time = difftime(time(0),it->starttime);
             char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
             //write(STDOUT_FILENO,pi,lpi);
            write(pifd2,"Process Id:",11);
            write(pifd2,pi,lpi);
            write(pifd2,"\n",1);
            write(pifd2,"Name:",5);
            write(pifd2,it->name,strlen(it->name));
            write(pifd2,"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(pifd2,"Parent's Process Id:",20);
            write(pifd2,pi,lpi);
            write(pifd2,"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(pifd2,"Start time:",11);
            write(pifd2,st,strlen(st));
            int et = 0;
            lpi = sprintf(pi,"%d",et);
            write(pifd2,"End time:",9);
            write(pifd2,"-",1);
            write(pifd2,"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(pifd2,"Elapsed time:",13);
           write(pifd2,pi,lpi);
            write(pifd2,"\n",1);
            write(pifd2,"===============================\n",33);
            }
            }
            int ch = write(pifd2,"#",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);

                }
           }
void *read_cl(void* fd){
    while(true){
        char str_t[200];
        int c = read(pipefd[0],str_t,200);
        if(c == 0){
            exit(0);
        }
        str_t[c] = '\0';
        if(strcmp("print_hello",str_t) == 0){
            int c = write(msgsock," Hello",6);
        }
        if(strcmp("list",str_t) == 0){
            write_list_active(pipefd2[1]);
        }
    }
}
void *read_conn(void *msg){
    char pi[200];
    while(true){
        write(STDOUT_FILENO,read_str,200);
        int co = read(STDIN_FILENO,read_str,200);
        if(co == -1){
            perror("Error");
        }
        read_str[co - 1] ='\0';
        if(strcmp(read_str,"conn_list") == 0){
            list <client_han> :: iterator it;
            bool exi = false;
            write(STDOUT_FILENO,"Connection list\n",16);
            write(STDOUT_FILENO,"============================\n",29);
			for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                int lpi = sprintf(pi,"%d",it->pid);
                write(STDOUT_FILENO,"Client handler's Pid: ",22);
                write(STDOUT_FILENO,pi,lpi);
                write(STDOUT_FILENO,"\n",1);
                write(STDOUT_FILENO,"Connection's IP Address: ",25);
                write(STDOUT_FILENO,it->cli_adr,strlen(it->cli_adr));
                write(STDOUT_FILENO,"\n",1);
                lpi = sprintf(pi,"%d",it->po);
                write(STDOUT_FILENO,"Port Number: ",13);
                write(STDOUT_FILENO,pi,lpi);
                write(STDOUT_FILENO,"\n",1);
                write(STDOUT_FILENO,"============================\n",29);
                exi = true;
			}
			 if(!exi){
                write(STDOUT_FILENO,"No Connected Clients\n",21);
            }
        }
        else if(strcmp("print_hello all",read_str) == 0){
            bool exi = false;
            list <client_han> :: iterator it;
            for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                write(it->pfd[1],"print_hello",11);
                exi = true;
            }
        if(!exi){
                write(STDOUT_FILENO,"No Connected Clients\n",21);
            }
        }
        else{
            char* token = strtok(read_str," ");
            bool exi = false;
            if(strcmp(token,"print_hello") == 0){
                list <client_han> :: iterator it;
                token = strtok(NULL, " ");
            for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                if(it->pid == atoi(token)){
                    write(it->pfd[1],"print_hello",11);
                    exi = true;
                }
            }
            if(!exi){
                write(STDOUT_FILENO,"PID doesn't exist in conn_list\n",31);
            }
            }
           else if(strcmp(token,"list")){
                token = strtok(NULL, " ");
                if(token == NULL){
                    list <client_han> :: iterator it;
                   for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                    write(it->pfd[1],"list",4);
                    exi = true;
                    char lstr[2000];
                int c = read(it->pfd2[0],lstr,1000);
                write(STDOUT_FILENO,"Active Processes for:",22);
                char prpid[20];
                int pidlen = sprintf(prpid,"%d",it->pid);
                write(STDOUT_FILENO,prpid,pidlen);
                write(STDOUT_FILENO,"\n",1);
                while(true){
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(it->pfd2[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                }
                }
                   }
             if(!exi){
               write(STDOUT_FILENO,"No Connected Clients\n",21);
            }
            }
                else{
                    list <client_han> :: iterator it;
                     for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                if(it->pid == atoi(token)){
                    write(it->pfd[1],"list",4);
                    exi = true;
                     char lstr[2000];
                int c = read(it->pfd2[0],lstr,1000);
                write(STDOUT_FILENO,"Active Processes for:",22);
                char prpid[20];
                int pidlen = sprintf(prpid,"%d",it->pid);
                write(STDOUT_FILENO,prpid,pidlen);
                write(STDOUT_FILENO,"\n",1);
                while(true){
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(it->pfd[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                }
                }
                   }}
             if(!exi){
               write(STDOUT_FILENO,"No Connected Clients\n",21);
            }
        }
    }
}
}}
bool child = false;
static void signal_handler(int signo){
    if(signo == SIGCHLD){
        int status;
        if(!child){
        int w = waitpid(0,&status,WNOHANG);
        write(STDOUT_FILENO,"Child Terminated\n",17);

         list <client_han> :: iterator it;
            for(it = ch_li.begin(); it != ch_li.end(); ++it) {
                if(it->pid == w){
                    close(it->msg);
                    it = ch_li.erase(it);
                }
            }
        }
        else{
            int w = waitpid(0,&status,WNOHANG);
            if(w > 0){
            list <Process> :: iterator it;
            int cpid = w;
            for(it = li.begin(); it != li.end(); ++it) {
              if(it->pid == cpid && it->active == 1){
             it->active = false;
              it->endtime = time(0);
              it->elapsed_time = difftime(it->endtime,it->starttime);
               }
            }}
        }
    }
    if(signo == SIGINT || signo == SIGKILL || signo == SIGTERM){
        list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true){
                    kill(it2->pid,SIGTERM);
               }
             }
        exit(0);
    }
}

time_t time_cal(){
time_t now = time(0);
//char* dt = ctime(&now);
return now;
}
bool strcheck(char* str){
   for(int i = 0; str[i] != '\0';i++){
       int ch = str[i];
       int ch_1 = str[i + 1];
       if (ch==45){
        if(ch_1 == '\0'){
        return false;
       }
         else if((ch_1 >= 33 && ch_1 <= 47 ) || (ch_1 >= 58 && ch_1 <= 126)){
          return false;
       }}
       else if((ch >= 33 && ch <= 47 ) || (ch >= 58 && ch <= 126)){
          return false;
          }
   }
    return true;
}
char* add(char* token,float sum){
    int val;
    while(token != NULL){
        int c = sscanf(token,"%d",&val);
        if(c == -1){
            perror("Error sscanf");
            perror("Error sscanf");
            exit(0);
        }
        bool check = strcheck(token);
        if (check == false) {
            return "False";
        }
        else{
            sum += val;
            token = strtok(NULL," ");
          }
    }
    char* s;
    int c = sprintf(s,"%f",sum);
    s[c-1] = '\0';
    return s;
}
char* sub(char* token,float sum){
    int val;
    while(token != NULL){
        int c = sscanf(token,"%d",&val);
        if(c == -1){
            perror("Error sscanf");
            exit(0);
        }
        bool check = strcheck(token);
        if (check == false) {
            return "False";
        }
        else{
            sum -= val;
            token = strtok(NULL," ");
          }
    }
    char* s;
    int c = sprintf(s,"%f",sum);
    s[c-1] = '\0';
    return s;
}
char* div(char* token,float sum){
    int val;
    while(token != NULL){
        int c = sscanf(token,"%d",&val);
        if(c == -1){
            perror("Error sscanf");
            exit(0);
        }
        bool check = strcheck(token);
        if (check == false) {
            return "False";
        }
        else{
            if(val == 0){
                return "False";
            }
            else{
            sum = sum/val;
            token = strtok(NULL," ");}
          }
    }
    char* s;
    int c = sprintf(s,"%f",sum);
    s[c-1] = '\0';
    return s;
}
char* mult(char* token,float sum){
    int val;
    while(token != NULL){
         int c = sscanf(token,"%d",&val);
        if(c == -1){
            perror("Error sscanf");
            exit(0);
        }
       bool check = strcheck(token);
        if (check == false) {
            return "False";
        }
        else{
            sum *= val;
            token = strtok(NULL," ");
          }
    }
    char* s;
    int c = sprintf(s,"%f",sum);
    s[c-1] = '\0';
    return s;
}
int main(void)
{
	int sock, length;
	struct sockaddr_in server,cli;
	//int msgsock;
	char buf[1024];
	int rval;
	int i;

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Name socket using wildcards */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(1500);
	if (bind(sock, (struct sockaddr *) &server, sizeof(server))) {
		perror("binding stream socket");
		exit(1);
	}
	/* Find out assigned port number and print it out */
	length = sizeof(server);
	if (getsockname(sock, (struct sockaddr *) &server, (socklen_t*) &length)) {
		perror("getting socket name");
		exit(1);
	}
	printf("Socket has port #%d\n", ntohs(server.sin_port));
	fflush(stdout);
    signal(SIGCHLD,signal_handler);
    signal(SIGINT,signal_handler);
    signal(SIGKILL,signal_handler);
    signal(SIGTERM,signal_handler);
	/* Start accepting connections */

     socklen_t clilen = sizeof(cli);
     //int clilen;
	listen(sock, 5);
	do {
        long time_g = time_cal();
        //list<Process> li;
        Process server = {getpid(),"Server",getppid(),time_g,true,time(0),difftime(time(0),time_g)};
		msgsock = accept(sock, (struct sockaddr *) &cli, &clilen);
        if(pipe(pipefd) < 0){
            perror("Error in pipe:");
        }
		int pid = fork();
		if(pid>0){
        pthread_t thread1;
	int iret1;
    iret1 = pthread_create( &thread1, NULL, read_conn, NULL);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }
     pthread_detach(thread1);
        close(pipefd[0]);
        close(pipefd2[1]);
        client_han p;
        p.pid = pid;
        p.cli_adr = inet_ntoa(cli.sin_addr);
        p.po = ntohs(cli.sin_port);
        p.pfd[0] = pipefd[0];
        p.pfd[1] = pipefd[1];
        p.pfd2[0] = pipefd2[0];
        p.pfd2[1] = pipefd2[1];
        p.msg = msgsock;
        //printf("%d\n",ntohs(p.po));
        //printf("server: got connection from %s port %d\n",inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        ch_li.push_back(p);
        int status;
         waitpid(0,&status,WNOHANG);
		}
		if(pid==0){
        close(pipefd[1]);
        close(pipefd2[0]);
        int ppid = getppid();
        pthread_t thread2;
        int iret2;
        iret2 = pthread_create( &thread2, NULL, read_cl, NULL);
        if(iret2)
        {
         fprintf(stderr,"Error - pthread_create() child return code: %d\n",iret2);
         exit(EXIT_FAILURE);
        }
     pthread_detach(thread2);

   //  socklen_t clilen = sizeof(cli);
		if (msgsock == -1)
			perror("accept");
		else do {
        child = true;
       /* int ppid2 = kill(ppid,0);
        if(ppid2!=0){
           list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true){
                    kill(it2->pid,SIGTERM);
               }
             }
        exit(0);
        }*/
			bzero(buf, sizeof(buf));
			if ((rval = read(msgsock, buf, 1024)) < 0){
                write(STDOUT_FILENO,buf,rval);
				perror("reading stream message");
				}
			if (rval == 0){
				printf("Ending connection\n");
				list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true){
                    kill(it2->pid,SIGTERM);
               }
             }
        exit(0);
				}

			else{

            if(rval <= 2){
                write(msgsock,"2",1);
        int ch = write(msgsock,"Invalid Command",15);
        if(ch == -1){
        perror("Error in write in pipe:");
        exit(1);
            }}
            else{
            char* token  = strtok(buf," ");
            if (strcmp(token,"add") == 0){
            write(msgsock,"2",1);
            float sum;
            //write(STDOUT_FILENO,buf,rval);
            token = strtok(NULL," ");
            if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            if(sscanf(token,"%f",&sum) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            token = strtok(NULL," ");
            char* s;
               s = add(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(msgsock,s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{

                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }
    }
    else if (strcmp(token,"mult")== 0){
            write(msgsock,"2",1);
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            if(sscanf(token,"%f",&sum) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            token = strtok(NULL," ");
            char* s;
               s = mult(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(msgsock,s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{

                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }}
    else if (strcmp(token,"sub")==0){
            write(msgsock,"2",1);
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            if(sscanf(token,"%f",&sum) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            token = strtok(NULL," ");
            char* s;
               s = sub(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(msgsock,s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{

                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }
    }
    else if (strcmp(token,"div")==0){
            write(msgsock,"2",1);
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            if(sscanf(token,"%f",&sum) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            token = strtok(NULL," ");
            char* s;
               s = div(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(msgsock,s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{

                if(write(msgsock,"Kindly only enter numbers",26) == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }}
    else if(strcmp(token,"run")==0){
        write(msgsock,"2",1);
        token = strtok(NULL," ");
           if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
            }
        else{
        char* p = token;
        char *paramlist[] = {p,NULL};
        int pifd3[2];
        int p1 = pipe2(pifd3,O_CLOEXEC);
        int pid2 = fork();
        time_t time_g2 = time_cal();
        if(pid2 == -1){
                perror("Error in fork:");
                exit(0);
        }
        if(pid2 == 0){
            close(pifd3[0]);
            if(execvp(p,paramlist) < 0){
                perror("Error");
            }
            write(pifd3[1],"Terminate",9);
            exit(0);
        }
        else if(pid2>0){
        close(pifd3[1]);
        char res[200];
        int reslen = read(pifd3[0],res,200);
        if(reslen==0){
        Process child2;
        child2.pid = pid2;
        char* temp = p;
        strcpy(child2.name, temp);
        child2.ppid = getpid();
        child2.starttime = time_g2;
        child2.active = true;
        child2.endtime = time(0);
        child2.elapsed_time = difftime(time(0),time_g2);
        li.push_back(child2);
         int ch = write(msgsock,"Successful",10);
        if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }
        }
        else{
        int ch = write(msgsock,"Error\n",6);
        if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }
        }}
    }
    }
	else if(strcmp(token,"list") == 0){
        token = strtok(NULL," ");
           if(token == NULL) {
            write(msgsock,"0",1);
            list <Process> :: iterator it;
			for(it = li.begin(); it != li.end(); ++it) {
            if(it->active == 1){
            it->elapsed_time = difftime(time(0),it->starttime);
             char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
            write(msgsock,"Process Id:",11);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"Name:",5);
            write(msgsock,it->name,strlen(it->name));
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(msgsock,"Parent's Process Id:",20);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(msgsock,"Start time:",11);
            write(msgsock,st,strlen(st));
            int et = 0;
            lpi = sprintf(pi,"%d",et);
            write(msgsock,"End time:",9);
            write(msgsock,"-",1);
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(msgsock,"Elapsed time:",13);
           write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"===============================\n",33);
            }
            }
            int ch = write(msgsock,"#",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);

                }
           }
     else if(strcmp(token,"all") == 0){
       write(msgsock,"1",1);
        token = strtok(NULL," ");
        if(token == NULL){
       // write(STDOUT_FILENO,"hi",2);
		list <Process> :: iterator it;
			for(it = li.begin(); it != li.end(); ++it) {
           //
            if(it->active == 1){
            // write(STDOUT_FILENO,"h1",2);
            it->elapsed_time = difftime(time(0),it->starttime);
             char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
            write(msgsock,"Process Id:",11);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"Name:",5);
            write(msgsock,it->name,strlen(it->name));
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(msgsock,"Parent's Process Id:",20);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(msgsock,"Start time:",11);
            write(msgsock,st,strlen(st));
            int et = 0;
            lpi = sprintf(pi,"%d",et);
            write(msgsock,"End time:",9);
            write(msgsock,"-",1);
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(msgsock,"Elapsed time:",13);
           write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"===============================\n",33);
            }
            else{
            // write(STDOUT_FILENO,"h",1);
		    char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
             write(msgsock,"Process Id:",11);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"Name:",5);
            write(msgsock,it->name,strlen(it->name));
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(msgsock,"Parent's Process Id:",20);
            write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(msgsock,"Start time:",11);
            write(msgsock,st,strlen(st));
            strcpy(st,ctime(&it ->  endtime));
            write(msgsock,"End time:",9);
            write(msgsock,st,strlen(st));
            write(msgsock,"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(msgsock,"Elapsed time:",13);
           write(msgsock,pi,lpi);
            write(msgsock,"\n",1);
            write(msgsock,"===============================\n",33);
			}
     }
     // write(STDOUT_FILENO,"h3",2);
     int ch = write(msgsock,"#",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);
        }
        }
        else{
            write(msgsock,"2",1);
            //write(STDOUT_FILENO,"he",2);
            write(msgsock,"Invalid Command",15);
        }
        }
        else{
            write(msgsock,"2",1);
            //write(STDOUT_FILENO,"he",2);
            write(msgsock,"Invalid Command",15);
        }
        }
    else if(strcmp(token,"kill") == 0){
        write(msgsock,"2",1);
        token = strtok(NULL," ");
        if(token == NULL) {
                write(msgsock, "Complete the Command",20 );
        }
        else{
        bool find=false;
        if(strcheck(token) == 0){
            list <Process> :: iterator it;
            int status;
            for(it = li.begin(); it != li.end(); ++it) {
            if(strcmp(it->name,token) == 0 && it->active == true){
             if(strcmp(it->name,"Server") == 0){
                  list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true && strcmp(it2->name,"Server") != 0 && strcmp(it2->name,"Client") != 0){
                    kill(it2->pid,SIGTERM);
               }
             }
             write(msgsock,"exit",4);
             exit(0);
             }
              find = true;
              int k = kill(it->pid,SIGTERM);
              if(k==-1){
                perror("Error in kill");
                find = false;
              }
              else{
              it->active = false;
              it->endtime = time(0);
              it->elapsed_time = difftime(it->endtime,it->starttime);
            if (strcmp(it->name,"Client") != 0){
             int w = waitpid(it-> pid,&status, WUNTRACED | WCONTINUED);
             if(w==-1){
                perror("Error in wait");
                find = false;
              }
              else{
            write(msgsock,"Terminated Successfully",23);
               }}
            else{
                 list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true && strcmp(it2->name,"Server") != 0 ){
                    kill(it2->pid,SIGTERM);
               }
              }
              exit(0);
               }
               }
              break;
        }
        }
        if(find == false){
            write(msgsock,"Process doesn't exist",21);
        }
        }
        else{
            list <Process> :: iterator it;
            int status;
            int cpid;
            sscanf(token,"%d",&cpid);
            for(it = li.begin(); it != li.end(); ++it) {
              if(it->pid == cpid && it->active == 1){
                if(strcmp(it->name,"Server") == 0){
                  list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true && strcmp(it2->name,"Server") != 0 && strcmp(it2->name,"Client") != 0){
                    kill(it2->pid,SIGTERM);
               }
             }
             write(msgsock,"exit",4);
             exit(0);
             }
              find = true;
              int k = kill(it->pid,SIGTERM);
              if(k==-1){
                perror("Error in kill");
                find = false;
              }
              else{
             it->active = false;
              it->endtime = time(0);
              it->elapsed_time = difftime(it->endtime,it->starttime);
             if (strcmp(it->name,"Client") != 0){
             int w = waitpid(it-> pid,&status, WUNTRACED | WCONTINUED);
             if(w==-1){
                perror("Error in wait");
                find = false;
              }
              else{
               write(msgsock,"Terminated Successfully",23);}
               }
               else{
                list <Process> :: iterator it2;
            for(it2 = li.begin(); it2 != li.end(); ++it2) {
               if(it2->active == true && strcmp(it2->name,"Server") != 0 ){
                    kill(it2->pid,SIGTERM);
               }
              }
              exit(0);
               }
               }
              break;
        }
        }
        if(find == false){
            write(msgsock,"Process doesn't exist",21);
        }
        }}
    }
    else if(strcmp(buf,"exit") == 0){
        write(msgsock,"2",1);
       // write(STDOUT_FILENO,"h1",2);
        int ch = write(msgsock,"exit",4);
        if(ch == -1){
        perror("Error write in pipe:");
        exit(1);
    }
        exit(0);
    }
      else{
        write(msgsock,"2",1);
        int ch = write(msgsock,"Invalid Command",15);
        if(ch == -1){
        perror("Error in write in pipe:");
        exit(1);
    }
    }
		}}} while (rval != 0);
		close(msgsock);}
	} while (TRUE);
}


