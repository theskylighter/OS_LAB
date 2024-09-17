#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[],char *envp[]){

    char* s= getenv("SERVER_NAME");
    printf("%s",s);

}