#include <iostream>
#include<unistd.h>
#include<cstring>
#include<signal.h>
using namespace std;
bool strcheck(char* str){
   for(int i = 0; str[i] != '\0';i++){
       int ch = str[i];
       int ch_1 = str[i + 1];
       if (ch==45){
         if((ch_1 >= 33 && ch_1 <= 47 ) || (ch_1 >= 58 && ch_1 <= 126)){
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
        bool check = strcheck(token);
        if (check == false) {
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
            return "False";
        }
        else{
            if(val == 0){
                write(STDOUT_FILENO,"Divide by Zero Error\n",21);
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
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
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
    if(pid == -1){
        perror("Error fork:");
        exit(0);
    }
    if(pid > 0){
        while(true){
        char str[1000];
        close(pifd[1]);
        int c = read(pifd[0],str,1000);
        if(c == -1){
                perror("Error read from pipe:");
                exit(0);
        }
        if(c <= 2){
            int ch = write(pifd2[1],"Invalid Command\n",16);
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
                write(pifd2[1], "Complete the Command\n",21 );
            }
               else if(strcheck(token) == false){
                write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
                c = write(pifd2[1],"\n",1);
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
                  int ch = write(pifd2[1],"\n",1);
                  if(ch == -1){
                    perror("Error write in pipe: ");
                    exit(0);

                }
                }
    }}
     else if (strcmp(token,"mult")== 0){
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(pifd2[1], "Complete the Command\n",21 );
            }
               else if(strcheck(token) == false){
                write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
                int ch = write(pifd2[1],"\n",1);
                if(ch == -1){
                perror("Error in write:");
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
                  int ch = write(pifd2[1],"\n",1);
                  if(ch == -1){
                    perror("Error write in pipe child 1:");
                    exit(0);
                  }
                }
    }}
     else if (strcmp(token,"sub")==0){
            float sum;
            token = strtok(NULL," ");
                        if(token == NULL) {
                write(pifd2[1], "Complete the Command\n",21 );
            }
                else if(strcheck(token) == false){
                write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
                int ch = write(pifd2[1],"\n",1);
                if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}
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
                  write(pifd2[1],"\n",1);
              }  }
    }
     else if (strcmp(token,"div")==0){
            float sum;
            token = strtok(NULL," ");
            if(token == NULL) {
                write(pifd2[1], "Complete the Command\n",21 );
            }
            else if(strcheck(token) == false){
                write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
                int ch = write(pifd2[1],"\n",1);
                if(ch == -1){
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
                  int ch = write(pifd2[1],"\n",1);
                  if(ch == -1){
                perror("Error in write:");
                exit(0);
            }
                }
    }}
    else if(strcmp(token,"run")==0){
        token = strtok(NULL," ");
           if(token == NULL) {
                write(pifd2[1], "Complete the Command\n",21 );
            }
        else{
        char* p = token;
        p[sizeof(p) - 1] = '\0';
        char *paramlist[] = {NULL};

        int pid2 = fork();
        if(pid2 == -1){
                perror("Error in fork:");
                exit(0);
        }
        if(pid2 == 0){
            execvp(p,paramlist);
            exit(0);
        }
        else if(pid2>0){
        int ch = write(pifd2[1],"\n",1);
        if(ch == -1){
                perror("Error write in pipe:");
                exit(0);
            }}}
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
        write(STDOUT_FILENO,"Invalid Command\n",16);
        int ch = write(pifd2[1],"\n",1);
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
            int c = write(pifd[1],str2,n);
            if(c == -1){
                perror("Error write in pipe child 1:");
                exit(0);
            }
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
        }}}

    else {
        perror("Error");
        exit(0);
    }
}
