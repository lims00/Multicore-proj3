#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <omp.h>
#include <stdio.h>

long num_steps = 10000000; 
double step;

void main (int argc, char *argv[]){ 
	long i; double x, pi, sum = 0.0;
	double start_time, end_time;

    int schedul_type = atoi(argv[1]);
    int chunk_size=atoi(argv[2]);
	int thread_num=atoi(argv[3]);

    
    step = 1.0/(double) num_steps;

    switch (schedul_type){
    case 1:
        start_time = omp_get_wtime();
        omp_set_num_threads(thread_num);
        {
            #pragma omp parallel for reduction(+:sum) private(x) schedule(static,chunk_size)
	        for (i=0;i< num_steps; i++){
		        x = (i+0.5)*step;
		        sum = sum + 4.0/(1.0+x*x);
            }

        }
        break;
    case 2:
        start_time = omp_get_wtime();
        omp_set_num_threads(thread_num); 
        {
            #pragma omp parallel for reduction(+:sum) private(x) schedule(dynamic,chunk_size)
	        for (i=0;i< num_steps; i++){
		        x = (i+0.5)*step;
		        sum = sum + 4.0/(1.0+x*x);
            }

        }
        break;
    case 3:
        start_time = omp_get_wtime();
        omp_set_num_threads(thread_num);
        {
            #pragma omp parallel for reduction(+:sum) private(x) schedule(guided,chunk_size) 
	        for (i=0;i< num_steps; i++){
		        x = (i+0.5)*step;
		        sum = sum + 4.0/(1.0+x*x);
            }
        }
        break;
    }
	pi = step * sum;
	end_time = omp_get_wtime();

	double timeDiff = end_time - start_time;
    printf("Execution Time : %lfms\n", timeDiff*1000);

	printf("pi=%.24lf\n",pi);
}