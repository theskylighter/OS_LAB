#include<stdio.h>

int main(int arg,char *argc[]){

    printf("Hello, welcome to Linux C Programming\n");
    printf("No. of arguments ot the main program : %d\n",arg);
    for(int i=0;i<arg;i++){
        printf("Argument No. %d : %s\n",i,argc[i]);
    }
}