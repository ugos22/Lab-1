#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h> 
#include "../engine/db.h"
#include "../engine/variant.h"
#define DATAS ("testdb")

#define KSIZE (16)
#define VSIZE (1000)

#define LINE "+-----------------------------+----------------+------------------------------+-------------------+\n"
#define LINE1 "---------------------------------------------------------------------------------------------------\n"


double get_ustime_sec(void); // WE CHANGED IT TO DOUBLE
void _random_key(char *key,int length);
pthread_mutex_t mutex; // the mutex we are going to be using
int multi; // = 1 then multithreading will be used, = 0 otherwise
void *_write_test(void *arg);
void *_read_test(void *arg);
//struct to pass arguments to threads executing _write_test or _read_test
struct data_write{
	long int count;
	int r;
};
struct data_write thread_args[2]; // first place is for write, second for read
DB* db; //we moved this pointer here so that we can open the database once to avoid multiple threads accessing the database at once