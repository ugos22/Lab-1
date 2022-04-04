#include <string.h>
#include "../engine/db.h"
#include "../engine/variant.h"
#include "bench.h"



void *_write_test(void *arg)
{
	
	int i;
	double cost;
	double start,end;
	Variant sk, sv;

	char key[KSIZE + 1];
	char val[VSIZE + 1];
	char sbuf[1024];

	memset(key, 0, KSIZE + 1);
	memset(val, 0, VSIZE + 1);
	memset(sbuf, 0, 1024);

	if(!multi)	
		db = db_open(DATAS); //db opens once if multiple threads are not needed 

	start = get_ustime_sec();
	
	
	for (i = 0; i < thread_args[0].count; i++) {
		
		if (thread_args[0].r)
			_random_key(key, KSIZE);
		else
			snprintf(key, KSIZE, "key-%d", i);
		fprintf(stderr, "%d adding %s\n", i, key);
		snprintf(val, VSIZE, "val-%d", i);

		sk.length = KSIZE;
		sk.mem = key;
		sv.length = VSIZE;
		sv.mem = val;

		if(multi){
			pthread_mutex_lock(&mutex); //lock and unlock before and after db_add to avoid conflictions between the threads
		}
		
		db_add(db, &sk, &sv);
		
		if(multi){
			pthread_mutex_unlock(&mutex);
		}
		
		if ((i % 10000) == 0) {
			fprintf(stderr,"random write finished %d ops%30s\r", i,"");
			fflush(stderr);
		}

		
	}

	if(!multi)	
		db_close(db); //db closes once if multiple threads are not needed

	end = get_ustime_sec();
	cost = end -start;

	printf(LINE);
	printf("|Random-Write	(done:%ld): %.6f sec/op; %.1f writes/sec(estimated); cost:%f(sec);\n"
		,thread_args[0].count, (double)(cost / thread_args[0].count)
		,(double)(thread_args[0].count / cost)
		,cost);

		
	return 0;
}

void *_read_test(void *arg)
{
	int i;
	int ret;
	int found = 0;
	double cost;
	double start,end;
	Variant sk;
	Variant sv;
	char key[KSIZE + 1];

	if(!multi)
		db = db_open(DATAS); //db opens once if multiple threads are not needed 
	
	start = get_ustime_sec();
	
	for (i = 0; i < thread_args[1].count; i++) {
		
		memset(key, 0, KSIZE + 1);

		//if you want to test random write, use the following
		if (thread_args[1].r)
			_random_key(key, KSIZE);
		else
			snprintf(key, KSIZE, "key-%d", i);
		fprintf(stderr, "%d searching %s\n", i, key);
		sk.length = KSIZE;
		sk.mem = key;

		if(multi){
			pthread_mutex_lock(&mutex);  // lock and unlock before and after db_get
		}
		
		ret = db_get(db, &sk, &sv);
		
		if(multi){
			pthread_mutex_unlock(&mutex);  
		}
		
		if (ret) {
			//db_free_data(sv.mem);
			found++;
		} else {
			INFO("not found key#%s", 
					sk.mem);
    	}

		if ((i % 10000) == 0) {
			fprintf(stderr,"random read finished %d ops%30s\r", 
					i, 
					"");

			fflush(stderr);
		}

	}
	

	if(!multi)	
		db_close(db);   //db closes once if multiple threads are not needed

	end = get_ustime_sec();
	cost = end - start;
	printf(LINE);
	printf("|Random-Read	(done:%ld, found:%d): %.6f sec/op; %.1f reads /sec(estimated); cost:%f(sec)\n",
		thread_args[1].count, found,
		(double)(cost / thread_args[1].count),
		(double)(thread_args[1].count / cost),
		cost);
	
	return 0;	
}

