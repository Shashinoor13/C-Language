#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


int numbers[10] ={1,2,3,4,5,6,7,8,9,10};

pthread_mutex_t lock;

void* routine(void* args){
    int start_index= *(int*)args;
    int sum =0;
    for(int i=0;i<5;i++){
        sum += numbers[start_index+i];
    }
    *(int*) args= sum;
    return args;  //returns sub_array address'es pointer here;
};

int main(){
    pthread_t threads[2];
    int* result;
    for(int i=0;i<2;i++){
        int* sub_array = malloc(sizeof(int)); //sub_array is allocated here
        *sub_array = i*5;
        pthread_create(
            &threads[i],
            NULL,
            &routine,
            sub_array //passed into the routine function from here
        );
    };
    int mainSum=0;
    for(int i=0;i<2;i++){
        int* res;
        pthread_join(
            threads[i],
            (void**)&res //sub_array's pointer is received here
        );
        mainSum += *res;
        free(res); //the memory allocated by sub_array is freed here
    };
    printf("Total Sum : %d",mainSum);
    return 0;
}