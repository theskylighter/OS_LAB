#include <omp.h>
#include <stdio.h>
int tid;
//#pragma omp threadprivate(tid)
int main() {
	int numt,i;
	#pragma omp parallel default (shared) num_threads(2)
	{	
	tid=omp_get_thread_num();
	printf("Hi, I'm thread number %d!\n",tid);
    }
	#pragma omp parallel for num_threads(2)
	for(i = 0;i < 10;i++) {
		printf("\nThread number %d, executing iteration %d...",omp_get_thread_num(),i);		
	}
//	#pragma omp parallel num_threads(2)
//	printf("\nHere also TID is %d",tid);
	return 0;
}
