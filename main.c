#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <hbwmalloc.h>

void getString();
void getString_P();
void getString_HBM_P();

void getString() 
{
    printf("Hello, World!\n");
}

void getString_P()
{
    #pragma omp parallel
    {
        void *ptr = NULL;
        
        #pragma omp single
        {
            int total_threads = omp_get_num_threads();
            printf("Total threads: %d\n", total_threads);
        }

        #pragma omp critical
        {
            ptr = malloc(1024);  // Allocate 1024 bytes
        }
        
        if (ptr) {
            printf("Hello World from thread (Memory allocated)\n");
            free(ptr);  
        } else {
            printf("Hello World from thread (Memory allocation failed)\n");
        }
    }
}

void getString_HBM_P()
{
    #pragma omp parallel
    {
        void *ptr = NULL;
        
        #pragma omp single
        {
            int total_threads = omp_get_num_threads();
            printf("Total threads: %d\n", total_threads);
        }
        
        #pragma omp critical
        {
            ptr = hbw_malloc(1024);  // Allocate 1024 bytes from HBM
        }
        
        if (ptr) {
            printf("Hello World from thread (HBM memory allocated)\n");
            hbw_free(ptr);  // Free the allocated memory
        } else {
            printf("Hello World from thread (HBM memory allocation failed)\n");
        }
    }
}

int main() 
{
    
    clock_t start, end;
    double time_spent;

    // Sequential version
    printf("Sequential\n");
    start = clock();
    getString();
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %f\n\n", time_spent);

    // Parallel version without HBM
    printf("OpenMP\n");
    start = clock();
    getString_P();
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %f\n\n", time_spent);

    // Parallel version with HBM
    printf("HBM, using memkind library - hbwmalloc\n");
    start = clock();
    getString_HBM_P();
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %f\n", time_spent);

    return 0;
}
