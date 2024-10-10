// Write a program where 2 threads are created and each thread prints information like
// (Name, Hall No., employee ID ,branch).
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


typedef struct employee
{
    char name[50];
    int hallno;
    int employeeID;
    char branch[50];
}employee;

void* print_details(void* data){
    employee *temp = (employee*) data;
    printf(" Name = %s, Hall No. = %x, employee ID = %x,branch = %s \n",temp->name, temp->hallno, temp->employeeID, temp->branch );
}


int main(){

    employee n1= {"shivam", 1,0001,"AIDE"};
    employee n2= {"shalvin", 2,0002,"CSE"};
pthread_t th1,th2;

if(pthread_create(&th1,NULL,print_details,(void*) &n1)){
    printf("error creating thread\n");

}
if(pthread_create(&th2,NULL,print_details,(void*) &n2)){
    printf("error creating thread\n");
}
if(pthread_join(th1,NULL)){
    printf("error joining thread\n");
}
if(pthread_join(th2,NULL)){
    printf("error joining thread\n");
}

pthread_exit(NULL);
return 0;

}