#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <omp.h>
#include <string.h>
bool isprime(int x){
    int i;
    if (x<=1) return false;
    for (i=2;i<x;i++) {
        if (x%i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
	int schedul_type = atoi(argv[1]);
	int thread_num=atoi(argv[2]);
    int count=0;
    double start_time, end_time;

    switch (schedul_type){
    case 1:
        start_time=omp_get_wtime();
        omp_set_num_threads(thread_num);
        
            #pragma omp parallel for reduction(+:count) schedule(static)
            for (int i=1;i<=200000;i++){
                if (isprime(i)){
                    count++;
                }
            }
        
        end_time=omp_get_wtime();
        break;
    case 2:
        start_time=omp_get_wtime();
        omp_set_num_threads(thread_num);
        
            #pragma omp parallel for reduction(+:count) schedule(dynamic) 
            for (int i=1;i<=200000;i++){
                if (isprime(i)){
                    count++;
                }
            }
        
        end_time=omp_get_wtime();
        break;
    case 3:
        start_time=omp_get_wtime();
        omp_set_num_threads(thread_num);
        
            #pragma omp parallel for reduction(+:count) schedule(static,10)
            for (int i=1;i<=200000;i++){
                if (isprime(i)){
                    count++;
                }
            }
        
        end_time=omp_get_wtime();
        break;
    case 4:
        start_time=omp_get_wtime();
        omp_set_num_threads(thread_num);
        
            #pragma omp parallel for reduction(+:count) schedule(dynamic,10)
            for (int i=1;i<=200000;i++){
                if (isprime(i)){
                    count++;
                }
            }
        
        end_time=omp_get_wtime();
        break;
    default:
        printf("You put wrong number. (input num : 1~4)\n");
        break;
    }

    

    printf("Number of prime numbers: %d\n", count);
    printf("Execution time: %.2f msec\n", (end_time - start_time)*1000);

    
    
	


}
