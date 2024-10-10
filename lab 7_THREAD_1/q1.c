#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


void* print_f(void* data){
    int num=*(int*)data;
    int id = pthread_self();
    printf("(%x)Thread %d executing...\n",id,num);
    // printf("%x",id);

    // printf("%s",pthread_self);
}

int main(){

int threadID[5];
pthread_t threads[5];

for(int i=0;i<5;i++){

threadID[i]=i+1;
    if(pthread_create(&threads[i],NULL,print_f,(void*)&threadID[i])){ 
       printf("error creating thread\n");  
    }
}
for(int i=0;i<5;i++){
    if(pthread_join(threads[i],NULL)){ 
       printf("error joining thread\n");  
    }
}
pthread_exit(NULL);

return 0;
}
