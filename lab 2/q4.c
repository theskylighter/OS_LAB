#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	int x1=atoi(argv[1]);
	int x2=atof(argv[2]);
	printf("%d + %d = %d \n",x1,x2,x1+x2);
	printf("%d - %d = %d \n",x1,x2,x1-x2);
	printf("%d x %d = %d \n",x1,x2,x1*x2);
	printf("%d / %d = %d \n",x1,x2,x1/x2);
	
	return 0;
}
