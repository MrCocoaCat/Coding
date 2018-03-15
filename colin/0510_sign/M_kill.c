#include<stdio.h>
#include<signal.h>
int main(int atgc,char * argv[])
{
 
kill(argv[2],argv[1]);


return 0;
}
