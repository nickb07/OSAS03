/*
* Nicholas Boodhoo, Pamela Nonato
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int MINVAL;
int MAXVAL;
int AVERAGE;
int SIZE;

void *findMin(void *arr);
void *findAverage(void * arr);
void *findMax(void *arr);

int main(int argc, char *argv[]) {
	
	//regular, insufficient arguments
	if(argc < 3){
		fprintf(stderr, "%s", "Must have at least 2 arguments\n");
		exit(1);
	}

	//store argv in an int array so we can manipulate the values
	char *value;
	int array[argc-1];
	int index = 0;

	for(int i = 1; i < argc; i++){
		value = argv[i];
		array[index] = atoi(value);
		index++;
	}
	SIZE = sizeof(array)/sizeof(array[0]); //get the length of the array

	//create the threads variables
	pthread_t minThread;
	pthread_t aveThread;
	pthread_t maxThread;
	
	//try to create thread, if it fails, print the error and exit
	if(pthread_create(&minThread, NULL, findMin, (void*)array) != 0){
		fprintf(stderr, "%s", "pthread_create (minThread) failed\n");
		exit(1);
	}
	if(pthread_create(&aveThread, NULL, findAverage, (void*)array) != 0){
		fprintf(stderr, "%s", "pthread_create (aveThread) failed\n");
		exit(1);
	}
	if(pthread_create(&maxThread, NULL, findMax, (void*)array) != 0){
		fprintf(stderr, "%s", "pthread_create (maxThread) failed\n");
		exit(1);
	}
	
	//join the threads, if it fails, print ther error and exit
	if(pthread_join(minThread, NULL) !=0){
		fprintf(stderr, "%s", "pthread_join (minThread) failed\n");
		exit(1);
	}
	if(pthread_join(aveThread, NULL) !=0){
		fprintf(stderr, "%s", "pthread_join (aveThread) failed\n");
		exit(1);
	}
	if(pthread_join(maxThread, NULL) !=0){
		fprintf(stderr, "%s", "pthread_join (maxThread) failed\n");
		exit(1);
	}
	
	//Workers have exited, print values
	printf("The average value is %d\n", AVERAGE);
	printf("The minimum value is %d\n", MINVAL);
	printf("The maximum value is %d\n", MAXVAL);

	return 0;
}

//find the minimum value of the array
void *findMin(void *arr){

	int *newArr = (int *)arr;
	MINVAL = newArr[0];

	for(int index = 0; index < SIZE; index++){
		if (newArr[index] < MINVAL){
			MINVAL = newArr[index];
		}
	}
	pthread_exit(0);
}

//find the average value of the array
void *findAverage(void *arr){
	int *newArr = (int *)arr;
	int sum = 0;
	
	for(int i = 0; i < SIZE; i++){
		sum += newArr[i];
	}
	AVERAGE = sum/SIZE;
	pthread_exit(0);
}

//find the max value of the array
void *findMax(void *arr){
	int *newArr = (int *)arr;
	MAXVAL = newArr[0];

	for(int i = 0; i < SIZE; i++){
		if(newArr[i] > MAXVAL){
			MAXVAL = newArr[i];
		}
	}
	pthread_exit(0);
}
