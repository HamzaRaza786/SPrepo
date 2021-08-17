#include <iostream>
#include <stdarg.h>
#include <unistd.h>
#include <cstring>
bool strcheck(char* str){
   for(int i = 0; str[i] != '\0';i++){
       int ch = str[i];
       int ch_1 = str[i + 1];
       if (ch==45){
         if(((ch_1 >= 33 && ch_1 <= 47 ) || (ch_1 > 59 && ch_1 <= 126)) || ch_1 == 58){
          return false;
        }
       }
       else if(((ch >= 33 && ch <= 47 )) || ((ch > 59 && ch <= 126)) || ch == 58){
          return false;
          }
   }
    return true;
}

bool semi_colon(char* str){
     for(int i = 0; str[i] != '\0';i++){
       int ch = str[i];
       if(ch == 59){
        return true;
       }
}
 return false;
}
int main(){
    char str[1000];
    char* token;
    str[0] = '0';
    int n = 2;
    int sum = 0;
    bool colon = false;
    int val;
    char res[2000];
    int len;
    write(STDOUT_FILENO,"Enter the numbers you want to add and end the numbers with a ; : ",65);
    while(str[n-2] != ';'){
    n =read(STDIN_FILENO,str,1000);
    str[n-1] = '\0';
    token = strtok(str," ");
    while(token != NULL){
        sscanf(token,"%d",&val);
        bool check = strcheck(token);
        if (check == false) {
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
            exit(0);
        }
        else if(semi_colon(token) == true){
            len = sprintf(res,"%d",sum);
            res[len] = '\n';
            write(STDOUT_FILENO,res,len + 1);
            token = strtok(NULL," ");
            sum = 0;
          }
        else{
            sum += val;
            token = strtok(NULL," ");
        }
    }}
    return 0;
}

