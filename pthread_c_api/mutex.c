#include<stdio.h>
#include<pthread.h>

int sum =0;
pthread_mutex_t mutex;

void* routine(){
    for (int i=0;i<10000000;i++){
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    return 0;
};

int main(){
    pthread_t threads[8];
    pthread_mutex_init(&mutex,NULL);
    for(int i=0;i<8;i++){
        if(pthread_create(&threads[i],NULL,&routine,NULL) != 0) {
            perror("Error creating thread");
            return 1;
        }
        printf("Creating thread %d\n",i);
    }
    for(int i=0;i<8;i++){
        if(pthread_join(threads[i],NULL) != 0) {
            perror("Error joining thread");
            return 1;
        }
        printf("Thread %d finished\n",i);
    }

    printf("Sum = %d\n",sum);
    pthread_mutex_destroy(&mutex);
    return 0;
};