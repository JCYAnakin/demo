/*
        n|
     ---------
    |1   |  3 |e
--- |    -    |-----
   w|2___|__4_|
         |s
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int countNorth=0, countSouth=0, countWest=0, countEast=0;
pthread_mutex_t mutexCount;
pthread_cond_t condWest, condEast, condNorth, condSouth;
pthread_cond_t condQueueWest, condQueueEast, condQueueNorth, condQueueSouth;
int totalCars = 0;
int nowPassCars = 0;
int waitCar = 0;
void *checkDead(void* args)
{
    while(true){
        sleep(1);
        //get the mutex
        pthread_mutex_lock(&mutexCount);
        //detect deadlock
        if(waitCar >= 4)
        {
            printf("!!!!!!Dead Lock!!!!!!\n");
            pthread_cond_signal(&condEast);
        }
        //if all the cars have pass, stop detecting
        if(nowPassCars == totalCars)
        {
            return 0;
        }
        pthread_mutex_unlock(&mutexCount);
    }
    return 0;
}

void *runfuncS(void* args)
{
    //get the order number of the car
    int orderNum = *(int*)args;
    printf("S: Car %d is coming..\n",orderNum);
    
    //get the car in the same queue, add 1 to the number
    pthread_mutex_lock(&mutexCount);
    int frontInQueue = countSouth;
    countSouth++;
    pthread_mutex_unlock(&mutexCount);
    
    
    pthread_mutex_lock(&mutexCount);
    //if this car is not the first car in queue, make it wait
    if(frontInQueue!=0)
    {
        //printf("S: there are cars in front of car %d. Waiting.\n", orderNum);
        pthread_cond_wait(&condQueueSouth, &mutexCount);
        //printf("S: Car %d comes to the front of queue\n", orderNum);
    }
    pthread_mutex_unlock(&mutexCount);
    
    //if there is car waiting on the right side, make this car waiting
    pthread_mutex_lock(&mutexCount);
    if(countEast!=0)
    {
        //printf("S: Car %d waiting for right side car go..\n", orderNum);
        waitCar++;
        pthread_cond_wait(&condSouth, &mutexCount);
        waitCar--;
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    countSouth--;
    printf("S: Car %d now passing the cross..\n", orderNum);
    nowPassCars++;
    //make the left side car go, and signal for the next car in queue.
    pthread_mutex_unlock(&mutexCount);
    pthread_cond_signal(&condWest);
    pthread_cond_signal(&condQueueSouth);
    return 0;
}
void *runfuncN(void* args)
{
    //check first, check east, go, let west go, and let the car behind go.
    //get the order number of the car
    int orderNum = *(int*)args;
    printf("N: Car %d is coming..\n",orderNum);
    
    //get the car in the same queue, add 1 to the number
    pthread_mutex_lock(&mutexCount);
    int frontInQueue = countNorth;
    countNorth++;
    pthread_mutex_unlock(&mutexCount);
    
    
    pthread_mutex_lock(&mutexCount);
    //if this car is not the first car in queue, make it wait
    if(frontInQueue!=0)
    {
        //printf("N: there are cars in front of car %d. Waiting.\n", orderNum);
        pthread_cond_wait(&condQueueNorth, &mutexCount);
        //printf("N: Car %d comes to the front of queue\n", orderNum);
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    //if there is car waiting on the right side, make this car waiting
    if(countWest!=0)
    {
        //printf("N: Car %d waiting for right side car go..\n", orderNum);
        waitCar++;
        pthread_cond_wait(&condNorth, &mutexCount);
        waitCar--;
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    countNorth--;
    printf("N: Car %d now passing the cross..\n", orderNum);
    //make the left side car go, and signal for the next car in queue.
    pthread_mutex_unlock(&mutexCount);
    nowPassCars++;
    pthread_cond_signal(&condEast);
    pthread_cond_signal(&condQueueNorth);
    return 0;
}
void *runfuncE(void* args)
{
    //get the order number of the car
    int orderNum = *(int*)args;
    printf("E: Car %d is coming..\n",orderNum);
    
    //get the car in the same queue, add 1 to the number
    pthread_mutex_lock(&mutexCount);
    int frontInQueue = countEast;
    countEast++;
    pthread_mutex_unlock(&mutexCount);
    
    
    pthread_mutex_lock(&mutexCount);
    //if this car is not the first car in queue, make it wait
    if(frontInQueue!=0)
    {
        //printf("E: there are cars in front of car %d. Waiting.\n", orderNum);
        pthread_cond_wait(&condQueueEast, &mutexCount);
        //printf("N: Car %d comes to the front of queue\n", orderNum);
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    //if there is car waiting on the right side, make this car waiting
    if(countNorth!=0)
    {
        //printf("E: Car %d waiting for right side car go..\n", orderNum);
        waitCar++;
        pthread_cond_wait(&condEast, &mutexCount);
        waitCar--;
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    countEast--;
    printf("E: Car %d now passing the cross..\n", orderNum);
    nowPassCars++;
    //make the left side car go, and signal for the next car in queue.
    pthread_mutex_unlock(&mutexCount);
    pthread_cond_signal(&condSouth);
    pthread_cond_signal(&condQueueEast);
    return 0;
}
void *runfuncW(void* args)
{
    //get the order number of the car
    int orderNum = *(int*)args;
    printf("W: Car %d is coming..\n",orderNum);
    
    //get the car in the same queue, add 1 to the number
    pthread_mutex_lock(&mutexCount);
    int frontInQueue = countWest;
    countWest++;
    pthread_mutex_unlock(&mutexCount);
    
    
    pthread_mutex_lock(&mutexCount);
    //if this car is not the first car in queue, make it wait
    if(frontInQueue!=0)
    {
        //printf("W: there are cars in front of car %d. Waiting.\n", orderNum);
        pthread_cond_wait(&condQueueWest, &mutexCount);
        //printf("N: Car %d comes to the front of queue\n", orderNum);
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    //if there is car waiting on the right side, make this car waiting
    if(countSouth!=0)
    {
        //printf("W: Car %d waiting for right side car go..\n", orderNum);
        waitCar++;
        pthread_cond_wait(&condWest, &mutexCount);
        waitCar--;
    }
    pthread_mutex_unlock(&mutexCount);
    
    pthread_mutex_lock(&mutexCount);
    countWest--;
    printf("W: Car %d now passing the cross..\n", orderNum);
    nowPassCars++;
    //make the left side car go, and signal for the next car in queue.
    pthread_mutex_unlock(&mutexCount);
    pthread_cond_signal(&condNorth);
    pthread_cond_signal(&condQueueWest);
    return 0;
}

int main(int argc,char *argv[])
{
    //initialize the mutex and the condition signals
    pthread_mutex_init(&mutexCount, NULL);
    pthread_cond_init(&condEast, NULL);
    pthread_cond_init(&condSouth, NULL);
    pthread_cond_init(&condNorth, NULL);
    pthread_cond_init(&condWest, NULL);
    pthread_cond_init(&condQueueEast, NULL);
    pthread_cond_init(&condQueueNorth, NULL);
    pthread_cond_init(&condQueueSouth, NULL);
    pthread_cond_init(&condQueueWest, NULL);
    pthread_t *t;
    pthread_t check;
     //get the length of the parameters, which means the total car number
    int i = 0;
    for(i = 0; ; i++)
    {
        if(argv[1][i] == '\0')
            break;
        totalCars++;
    }
    //use “num” as the intermediate variable to record the number of cars
    int *num;
    //allocate memory for num as well as t
    num = (int*)malloc(sizeof(int)*totalCars);
    t = (pthread_t*)malloc(sizeof(pthread_t)*totalCars);
    //get num
    for(i = 0; i < totalCars; i++)
    {
        num[i] = i;
    }
    //create threads, according to the type of the threads.
    for(i = 0; i < totalCars; i++)
    {
        //the car is on the north path
        if(argv[1][i] == 'n'||argv[1][i] == 'N')
        {
            pthread_create(&t[i], NULL, runfuncN, &num[i]);
        }
        //the car is on the south path
        if(argv[1][i] == 's'||argv[1][i] == 'S')
        {
            pthread_create(&t[i], NULL, runfuncS, &num[i]);
        }
        //the car is on the west path
        if(argv[1][i] == 'w'||argv[1][i] == 'W')
        {
            pthread_create(&t[i], NULL, runfuncW, &num[i]);
        }
        //the car is on the east path
        if(argv[1][i] == 'e'||argv[1][i] == 'E')
        {
            pthread_create(&t[i], NULL, runfuncE, &num[i]);
        }
    }
    //create the thread for checking deadlocks
    pthread_create(&check, NULL, checkDead, NULL);
    //use pthread_join to “start” these threads.
    for(int i = 0; i < totalCars; i++)
    {
        pthread_join(t[i], NULL);
    }
    //use pthread_join to “start” the thread for checking deadlocks.
    pthread_join(check, NULL);

}

