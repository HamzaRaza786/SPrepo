#include <iostream>
#include<unistd.h>
#include<cstring>
#include<signal.h>
#include<list>
#include<iterator>
#include<ctime>
#include<fcntl.h>
#include<stdio.h>
#include<wait.h>
using namespace std;
struct Process{
    int pid;
    char name[200];
    int ppid;
    time_t starttime;
    bool active;
    time_t endtime;
    double elapsed_time;
};
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
            exit(0);
        }
        //token[c-1] = '\0';
        bool check = strcheck(token);
        if (check == false) {
           // write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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
            //write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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
            //write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
            return "False";
        }
        else{
            if(val == 0){
                //write(STDOUT_FILENO,"Divide by Zero Error\n",21);
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
            //write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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

int main(){
    int pifd[2];
    int pifd2[2];

    int p1 = pipe(pifd);
    if(p1 == -1){
        perror("Error pipe:");
        exit(0);
    }
    int p2 = pipe(pifd2);
    if(p1 == -1){
        perror("Error pipe:");
        exit(0);
    }
    int pid = fork();
    long time_g = time_cal();
    if(pid == -1){
        perror("Error fork:");
        exit(0);
    }

    if(pid > 0){
        list<Process> li;
        Process server = {getpid(),"Server",getppid(),time_g,true,time(0),difftime(time(0),time_g)};
        Process child = {pid,"Client",getpid(),time_g,true,time(0),difftime(time(0),time_g)};
        li.push_back(server);
        li.push_back(child);
        while(true){
        char str[1000];
        close(pifd[1]);
        int c = read(pifd[0],str,1000);
        if(c == -1){
                perror("Error read from pipe:");
                exit(0);
        }
        if(c <= 2){
            int ch = write(pifd2[1],"Invalid Command",15);
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }
        }
        else {
        char* token;
        token = strtok(str," ");
        str[c - 1] = '\0';
     if (strcmp(token,"add") == 0){
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            c = sscanf(token,"%f",&sum);
            if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            token = strtok(NULL," ");
            char* s;
               s = add(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(pifd2[1],s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{
                  c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }}
     else if (strcmp(token,"mult")== 0){
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
            }
               else if(strcheck(token) == false){
                c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            sscanf(token,"%f",&sum);
            token = strtok(NULL," ");
             char* s = mult(token,sum);
             //<<sum<<endl;
            if (strcmp(s,"False")!=0){
                int ch = write(pifd2[1],s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}

                else{
                  c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }}
     else if (strcmp(token,"sub")==0){
            float sum;
            token = strtok(NULL," ");
                        if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
            }
                else if(strcheck(token) == false){
                c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            sscanf(token,"%f",&sum);
            token = strtok(NULL," ");
             char* s = sub(token,sum);
             if (strcmp(s,"False")!=0){
                int ch = write(pifd2[1],s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}

                else{
                  c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
              }  }
    }
     else if (strcmp(token,"div")==0){
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
            }
            else if(strcheck(token) == false){
               c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
            }
            else{
            sscanf(token,"%f",&sum);
            token = strtok(NULL," ");
             char* s = div(token,sum);
            if (strcmp(s,"False")!=0){
                int ch = write(pifd2[1],s,strlen(s));
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
                else{
                 c = write(pifd2[1],"Kindly only enter numbers",26);
                if(c == -1){
                perror("Error write in pipe:");
                exit(0);
            }
                }
    }}
    else if(strcmp(token,"run")==0){
        token = strtok(NULL," ");
           if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
            }
        else{
        char* p = token;
        p[sizeof(p) - 1] = '\0';
        char *paramlist[] = {NULL};
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
            execvp(p,paramlist);
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
        //write(STDOUT_FILENO,child2.name,sizeof(child2.name));
         int ch = write(pifd2[1],"Successful\n",11);
        if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }
        }
        else{
        int ch = write(pifd2[1],"Error\n",6);
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
            list <Process> :: iterator it;
			for(it = li.begin(); it != li.end(); ++it) {
            if(it->active == 1){
            it->elapsed_time = difftime(time(0),it->starttime);
             char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
             //write(STDOUT_FILENO,pi,lpi);
            write(pifd2[1],"Process Id:",11);
            write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"Name:",5);
            write(pifd2[1],it->name,strlen(it->name));
            write(pifd2[1],"\n",1);
            //sleep(0.2);
            lpi = sprintf(pi,"%d",it->ppid);
            write(pifd2[1],"Parent's Process Id:",20);
            write(pifd2[1],pi,lpi);
            //sleep(0.2);
            write(pifd2[1],"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(pifd2[1],"Start time:",11);
            write(pifd2[1],st,strlen(st));
            //write(pifd2[1],"\n",1);
            //sleep(0.2);
            int et = 0;
            lpi = sprintf(pi,"%d",et);
            write(pifd2[1],"End time:",9);
            write(pifd2[1],"-",1);
            write(pifd2[1],"\n",1);
           // sleep(0.2);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(pifd2[1],"Elapsed time:",13);
           write(pifd2[1],pi,lpi);
            //write(pifd2[1],"@",1);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"===============================\n",33);
           // sleep(0.2);
            }
            }
            int ch = write(pifd2[1],"#",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);

                }
           }
     else if(strcmp(token,"all") == 0){
        token = strtok(NULL," ");
        if(token == NULL){
		list <Process> :: iterator it;
			for(it = li.begin(); it != li.end(); ++it) {
            if(it->active == 1){
            it->elapsed_time = difftime(time(0),it->starttime);
             char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
            write(pifd2[1],"Process Id:",11);
            write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"Name:",5);
            write(pifd2[1],it->name,strlen(it->name));
            write(pifd2[1],"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(pifd2[1],"Parent's Process Id:",20);
            write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(pifd2[1],"Start time:",11);
            write(pifd2[1],st,strlen(st));
            write(pifd2[1],"End time:",9);
            write(pifd2[1],"-",1);
            write(pifd2[1],"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(pifd2[1],"Elapsed time:",13);
           write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"===============================\n",33);
            }
            else{
		    char pi[200];
             int lpi = sprintf(pi,"%d",it->pid);
            write(pifd2[1],"Process Id:",11);
            write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"Name:",5);
            write(pifd2[1],it->name,strlen(it->name));
            write(pifd2[1],"\n",1);
            lpi = sprintf(pi,"%d",it->ppid);
            write(pifd2[1],"Parent's Process Id:",20);
            write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            char st[200];
            strcpy(st,ctime(&it ->  starttime));
            write(pifd2[1],"Start time:",11);
            write(pifd2[1],st,strlen(st));
            //int et = 0;
            //lpi = sprintf(pi,"%d",et);
            strcpy(st,ctime(&it ->  endtime));
            write(pifd2[1],"End time:",9);
            write(pifd2[1],st,strlen(st));
            write(pifd2[1],"\n",1);
            lpi = sprintf(pi,"%f",it->elapsed_time);
            pi[lpi-1] = 's';
            pi[lpi] = '\0';
           write(pifd2[1],"Elapsed time:",13);
           write(pifd2[1],pi,lpi);
            write(pifd2[1],"\n",1);
            write(pifd2[1],"===============================\n",33);
			}
     }
     int ch = write(pifd2[1],"#",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);

                }}
     else{
          int ch = write(pifd2[1],"Invalid Command",15);
     }
     }
     else{
          int ch = write(pifd2[1],"Invalid Command",15);
     }

        }
    else if(strcmp(token,"kill") == 0){
        token = strtok(NULL," ");
        if(token == NULL) {
                write(pifd2[1], "Complete the Command",20 );
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
             write(pifd2[1],"exit",4);
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
            write(pifd2[1],"Terminated Successfully",23);
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
            write(pifd2[1],"Process doesn't exist",21);
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
             write(pifd2[1],"exit",4);
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
               write(pifd2[1],"Terminated Successfully",23);}
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
            write(pifd2[1],"Process doesn't exist",21);
        }
        }}
    }

    else if(strcmp(str,"exit") == 0){
        int ch = write(pifd2[1],"exit",4);
        if(ch == -1){
        perror("Error write in pipe:");
        exit(0);
    }
        exit(0);
    }
    else{
        int ch = write(pifd2[1],"Invalid Command",15);
        if(ch == -1){
        perror("Error in write in pipe:");
        exit(0);
    }
    }}
    }}
    else if(pid == 0){
        close(pifd[0]);
        close(pifd2[1]);
        while(true){
            char str2[1000];
            int n =read(STDIN_FILENO,str2,1000);
            if(n == -1){
                perror("Error in read:");
                exit(0);
            }
            str2[n-1] = '\0';
            int cou = 0;
            int c = write(pifd[1],str2,n);
            if(c == -1){
                perror("Error write in pipe child 1:");
                exit(0);
            }

            if(strcmp(str2,"list") == 0 || strcmp(str2,"list ") == 0){
                char lstr[2000];
                int c = read(pifd2[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                write(STDOUT_FILENO,"Active Processes:\n",18);
                while(true){
                cou+=1;
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(pifd2[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }}
                }
                }

            else if(strcmp(str2,"list all") == 0 || strcmp(str2,"list all ") == 0){
                char lstr[2000];
                int c = read(pifd2[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }
                write(STDOUT_FILENO,"All Processes:\n",18);
                 while(true){
                     cou+=1;
                if(lstr[c - 1] == '#'){
                    write(STDOUT_FILENO,lstr,c-2);
                    break;
                }
                else{
                write(STDOUT_FILENO,lstr,c);
                c = read(pifd2[0],lstr,1000);
                if(c == -1){
                    perror("Error read in pipe child 1:");
                    exit(0);
                }}
                 }
            }
            else{
            char sum2[200];
            c = read(pifd2[0],sum2,1000);
            if(c == -1){
                perror("Error read in pipe child 1:");
                exit(0);
            }
            sum2[c] = '\0';
            if(strcmp(sum2,"exit") == 0){
                //cout<<"hello";
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
    }
    else {
        perror("Error");
        exit(0);
    }
}
