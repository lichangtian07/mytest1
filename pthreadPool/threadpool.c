/*
*
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define LIST_ADD(item, list) do{			\
	item->next = NULL;						\
	item->prev = NULL;						\
	if( list != NULL) list->prev = item;	\
	list = item;							\
}while(0)


#define LIST_DEL(item, list) do{			\
	if(item->prev != NULL) item->prev->next = item->next;	\
	if(item->next != NULL) item->next->prev = item->prev;	\
	if(item == list) list=item->next;						\
	item->prev = item->next = NULL;							\
}while(0)

/* 
** 需做的工作结构
** 核心: func工作 user_data传参
*/
struct NJOB{
	void (*func)(void *args);
	void * user_data;
	
	struct NJOB *prev;
	struct NJOB *next;
};
/*
** 线程载体 
** 核心：线程id  线程池pool进程管理者    
*/
struct NWORKER{
	pthread_t		id;
	int				terminate; //任务中止标记位
	
	struct NMANAGER* pool;
	
	struct NWORKER *prev ;
	struct NWORKER *next;
};

/*
** 线城池载体
** 核心：线程链表  与 工作链表
*/
typedef struct  NMANAGER {
	
	pthread_mutex_t mtx;
	pthread_cond_t cond;
	
	struct NJOB * jobs;
	struct NWORKER * workers;
}nThreadPool;


void *thread_cb(void * arg){
	
	struct NWORKER *worker = (struct NWORKER *) arg;
	
	while(1){
		pthread_mutex_lock(&worker->pool->mtx);
		while(worker->pool->jobs == NULL){
			if(worker->terminate) break;
			pthread_cond_wait(&worker->pool->cond,  &worker->pool->mtx);
		}
		struct NJOB * job = worker->pool->jobs;
		
		if(job != NULL)
		{
			LIST_DEL(job, worker->pool->jobs);
		}
		
		pthread_mutex_unlock(&worker->pool->mtx);
		
		job->func(job);
		
	}
	
}

int nThreadPoolCreate(nThreadPool * pool , int numworkers){
	
	int  i; 
	int  ret = 0;
	
	//参数判断
	if (pool == NULL) 
		return -1;
	
	if (numworkers < 1 ) 
		numworkers = 1;

	memset(pool, 0, sizeof(nThreadPool));
	//初始化互斥锁
	pthread_mutex_t  blank_mutex = PTHREAD_MUTEX_INITIALIZER;
	memcpy(&pool->mtx, &blank_mutex, sizeof(pthread_mutex_t));
	
	//初始化条件
	pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
	memcpy(&pool->cond, &blank_cond, sizeof(pthread_cond_t));
	
	
	for ( i= 0; i < numworkers ; i++){
		
		struct NWORKER * worker =  malloc(sizeof(struct NWORKER));
		
		if(worker == NULL) {
			perror("worker  malloac failed");
			return -2;
		}
		
		memset(worker, 0, sizeof(struct NWORKER));
		
		worker->pool = pool;
		worker->terminate = 0;
		
		ret = pthread_create(&worker->id, NULL, thread_cb, worker);
		if(ret){
			perror("thread_create");
			free(worker);
	
			return 1;
		}
		
		
		LIST_ADD(worker, pool->workers);
	}
	
	return 0;
}

int nThreadPoolDestory(nThreadPool * pool){
	int  i  = 0;
	struct NWORKER * worker = NULL;
	
	
	if(pool == NULL ) 
		return -1;
	
	for( worker  =  pool->workers; worker != NULL; worker=worker->next){
		worker->terminate = 1;
	}
	
	pthread_mutex_lock(&pool->mtx);
	free(pool->workers);
	free(pool->jobs);
	pool->workers = NULL;
	pool->jobs = NULL;
	
	pthread_cond_broadcast(&pool->cond);
	pthread_mutex_unlock(&pool->mtx);
	
	
}


int nThreadPoolPushThread(nThreadPool * pool , struct NJOB * job){
	
	pthread_mutex_lock(&pool->mtx);
	
	LIST_ADD(job, pool->jobs);
	pthread_cond_signal(&pool->cond);
	
	pthread_mutex_unlock(&pool->mtx);
	
}


//debug
//1000 个任务
#define THREAD_MAX_NUM			80
#define THREAD_COUNTER_SIZE		100

//工作都一样 参数也都一样   数数
void test_counter(void * args){
	
	struct NJOB * job = (struct NJOB *)args;
	int   index = *(int *)job->user_data;
	
	printf(" thread id : %lu and index %d \n", pthread_self(), index);
	
	free(job->user_data);
	free(job);
	
}

#if 1
int main(){
	int i = 0;
	nThreadPool pool;
	
	//招人
	nThreadPoolCreate(&pool, THREAD_MAX_NUM);
	
	for(i = 0; i <THREAD_COUNTER_SIZE; i ++ ){
			struct  NJOB * job = (struct NJOB * )malloc(sizeof(struct NJOB));
			if( job == NULL)
			{
				perror("malloc job Error ");
				return 1;
			}
			job->func =  test_counter;
			job->user_data = malloc(sizeof(int));
			*(int *) job->user_data = i;
			
			//分配工作
			nThreadPoolPushThread(&pool, job);
		
	}
	
	printf("\n");
	
	nThreadPoolDestory(&pool);
	
	return 0;
}
#endif 



















