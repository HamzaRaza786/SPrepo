#include <iostream>
#include <unistd.h>
#include<stdarg.h>
using namespace std;

int main()
{
    //Tuesday
    write(-2,"Hey",3);
    if(errno == EBADF){
        cout<< "\n"<<"File error"<<endl;
        printf("%i\n",EBADF);
        perror("1");
        cout<<EINVAL;
    }
    char str[20];
    read(STDIN_FILENO,str,20);

    /*Thursday

    */
    //ADD Two nuMBER
     char a[20];
    char b[20];
    int a1;
    int b1;
    int resu;
    char res[20];
    write(STDOUT_FILENO,"Enter number ",13);
    read(STDIN_FILENO,a,10);
    sscanf(a,"%d %d",&a1,&b1);
    resu = a1 + b1;
    int s = sprintf(res,"%d",resu);
    write(STDOUT_FILENO,res,s);

    //Print Two Strings

    char s[20];
    char p[20];
    int as = read(STDIN_FILENO,s,20);
    int si = read(STDIN_FILENO,p,20);
    s[as-1] = NULL;
    char re[20];
    int siz = sprintf(re,"%s%s",s,p);
    write(STDOUT_FILENO,re,siz);
    return 0;
}
