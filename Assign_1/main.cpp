#include <iostream>
#include <stdarg.h>
#include <unistd.h>
#include <cstring>
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
int main(){
    char str[1000];
    char* token;
    int sum = 0;
    sum = 0;
    write(STDOUT_FILENO,"Enter the numbers you want to add: ",35);
    int n =read(STDIN_FILENO,str,1000);
    str[n-1] = '\0';
    token = strtok(str," ");
    int val;
    while(token != NULL){
        sscanf(token,"%d",&val);
        bool check = strcheck(token);
        if (check == false) {
            write(STDOUT_FILENO,"Kindly only enter numbers\n",27);
            exit(0);
        }
        else{
            sum += val;
            token = strtok(NULL," ");
          }
    }
    char res[2000];
    int len = sprintf(res,"%d",sum);
    write(STDOUT_FILENO,res,len);
    return 0;
}

