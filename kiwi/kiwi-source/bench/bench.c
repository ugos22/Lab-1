#include "bench.h"


void _random_key(char *key,int length) {
	int i;
	char salt[36]= "abcdefghijklmnopqrstuvwxyz0123456789";

	for (i = 0; i < length; i++)
		key[i] = salt[rand() % 36];
}

void _print_header(int count)
{
	double index_size = (double)((double)(KSIZE + 8 + 1) * count) / 1048576.0;
	double data_size = (double)((double)(VSIZE + 4) * count) / 1048576.0;

	printf("Keys:\t\t%d bytes each\n", 
			KSIZE);
	printf("Values: \t%d bytes each\n", 
			VSIZE);
	printf("Entries:\t%d\n", 
			count);
	printf("IndexSize:\t%.1f MB (estimated)\n",
			index_size);
	printf("DataSize:\t%.1f MB (estimated)\n",
			data_size);

	printf(LINE1);
}

void _print_environment()
{
	time_t now = time(NULL);

	printf("Date:\t\t%s", 
			(char*)ctime(&now));

	int num_cpus = 0;
	char cpu_type[256] = {0};
	char cache_size[256] = {0};

	FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
	if (cpuinfo) {
		char line[1024] = {0};
		while (fgets(line, sizeof(line), cpuinfo) != NULL) {
			const char* sep = strchr(line, ':');
			if (sep == NULL || strlen(sep) < 10)
				continue;

			char key[1024] = {0};
			char val[1024] = {0};
			strncpy(key, line, sep-1-line);
			strncpy(val, sep+1, strlen(sep)-1);
			if (strcmp("model name", key) == 0) {
				num_cpus++;
				strcpy(cpu_type, val);
			}
			else if (strcmp("cache size", key) == 0)
				strncpy(cache_size, val + 1, strlen(val) - 1);	
		}

		fclose(cpuinfo);
		printf("CPU:\t\t%d * %s", 
				num_cpus, 
				cpu_type);

		printf("CPUCache:\t%s\n", 
				cache_size);
	}
}


int main(int argc,char** argv)
{
	if (argc < 3 || argc > 7) { //wrong usage detection
		fprintf(stderr,"Usage: db-bench <write | read > <count> or if you want raw \n<raw> <count> <random> \n<raw> <count> <random> <num_of_read_threads> \n<raw> <count> <random> <write_perc> <read_perc> NOTE: sum of percentages must be 100\n<raw> <count> <random> <write_perc> <read_perc> <num_of_read_threads>\n");
		exit(1);
	}

	long int count = atoi(argv[2]); //second argument will always be count
	multi = 0; // default value of multi is 0
	double cost;
	double start,end;


	// thread initialization
	pthread_t* pth; //an array of the threads we need
	pthread_mutex_init(&mutex, NULL);
	//default values of read and write arguments
	thread_args[0].count = count;  
	thread_args[0].r = 0;
	thread_args[1].count = count;
	thread_args[1].r = 0;

	srand(time(NULL));
	
	if (strcmp(argv[1], "write") == 0) {

		count = atoi(argv[2]);
		_print_header(count);
		_print_environment();
		if (argc == 4)
			thread_args[0].r = 1;
		_write_test(&thread_args[0]);
	} else if (strcmp(argv[1], "read") == 0) {

		count = atoi(argv[2]);
		_print_header(count);
		_print_environment();
		if (argc == 4)
			thread_args[1].r = 1;
		
		_read_test(&thread_args[1]);
	} else if (strcmp(argv[1], "raw") == 0) { // threaded read and write
		/*
		Usage for raw is the following:
		The third argument is used to test random read and write. The values it takes are either y(yes) or n(no).
		<raw> <count> <random> (#count writes and reads)
		<raw> <count> <random> <#threads> (#count writes and number of read threads)
		<raw> <count> <random> <write%> <read%> (#count percentage of writes and reads, NOTE: sum of percentages must be 100)
		<raw> <count> <random> <write%> <read%> <#threads> (#count percentage of writes and reads including multiple read threads)
		*/
		
		int thread_num; // number of read threads
		if(argc == 5){  
			thread_num = atoi(argv[4]);
		}else if(argc == 7){
			thread_num = atoi(argv[6]);
		}else{
			thread_num = 1; // by default we need only one read thread
		}
		
		pth = malloc(sizeof(pthread_t) * (thread_num + 1)); //we dynamically allocate an array of the desired threads depending on the case specified above
		multi = 1;// = 1 so that we open db once
		start = get_ustime_sec();

		if((argc > 5 && argc < 8)){
			float Wperc = atoi(argv[4]);
			float Rperc = atoi(argv[5]); 
			thread_args[0].count = count*(Wperc/100);
			thread_args[0].r = 0;
			thread_args[1].count = count*(Rperc/100);
			thread_args[1].r = 0;

		}
		if (!(strcmp(argv[3], "y")) || !(strcmp(argv[3], "n"))){ // test random
			if(!(strcmp(argv[3], "y"))){
				thread_args[0].r = 1;
				thread_args[1].r = 1;
			}
		}else{
			fprintf(stderr, "Type y for yes or n for no\n");
			exit(1);
		}
		
		_print_header(count);
		_print_environment();
		
		db = db_open(DATAS); //open db once
		
		//	THREAD CREATION
		if (pthread_create(&pth[0], NULL, _write_test, (void *) &thread_args[0]) != 0) {
			return 1;
    	}
		for (int i = 0; i < thread_num; i++) {
        	if (pthread_create(&pth[i+1], NULL, _read_test, (void *) &thread_args[1]) != 0) {
            	return 1;
        	}
    	}
		if (pthread_join(pth[0], NULL) != 0) {
        	return 2;
    	}
    	for (int i = 0; i < thread_num; i++) {
        	if (pthread_join(pth[i+1], NULL) != 0) {
            	return 3;
        	}
    	}

		db_close(db); //close db once
		pthread_mutex_destroy(&mutex); //destroy lock
		
		end = get_ustime_sec();
		cost = end - start;

		printf(LINE);
		printf("|raw done cost:%f(sec)\n", cost);
	}

	else {
		fprintf(stderr,"Usage: db-bench <write | read > <count> or if you want raw \n<raw> <count> <random> \n<raw> <count> <random> <num_of_read_threads> \n<raw> <count> <random> <write_perc> <read_perc> NOTE: sum of percentages must be 100\n<raw> <count> <random> <write_perc> <read_perc> <num_of_read_threads>\n");
		exit(1);
	}
	return 1;
}
