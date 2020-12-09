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
	
	struct NJOB * jobs; //需要完成的工作
	struct NWORKER * workers; //线程池载体,即线程池链表的item线程
}nThreadPool;

/*
** 一般线程毁掉函数
** genrnal thread callback
** 1 所有线程池的线程都回掉此函数
** 2 线程回调，要做好退出线程的逻辑
** 3 线程回调，过程注意加速
** 
*/
void *thread_cb(void * arg){
	
	struct NWORKER *worker = (struct NWORKER *) arg;
	
	while(1){
		pthread_mutex_lock(&worker->pool->mtx);
		while( worker->pool->jobs == NULL){
			/*
			** terminte标志1 终止一切工作 
			*/
			if(worker->terminate) 
			{
				break;
			}
			/*
			** 等待条件的触发 
			** 1 触发后发现工作列表是空的接着等待
			** 2 触发后发现工作列表存在工作，即最近的while判断
			*/
			pthread_cond_wait(&worker->pool->cond,  &worker->pool->mtx);
		}
		/*
		**收到终止信号就退出线程，就不管工作做没做完
		*/
		if(worker->terminate)
		{
			pthread_mutex_unlock(&worker->pool->mtx);
			break;
		}
		
		struct NJOB * job = worker->pool->jobs;
		/*
		** 此处比较巧妙： 
		** 1 先把线程的工作从线程中的工作列表去掉
		** 2 解锁
		** 3 再做完这个工作
		*/
		if(job != NULL)
		{
			LIST_DEL(job, worker->pool->jobs);
		}
		
		pthread_mutex_unlock(&worker->pool->mtx);
		
		job->func(job);
		
	}
	
}

/*
**  创建线程池的函数
**  1 线程池的互斥锁，每个线程载体处理线程池里的参数（共同参数）
**    特别是线程池里的工作jobs列表。
**  2 线程池的触发条件，触发线程载体工作的条件参数。
**  3 线程池的载体列表（list中item的个数），同时创建线程，挂载回调函数
**    即线程统一的回调接口。
**
*/
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
	
	/*
	** 分配线程池需要的线程载体
	*/
	for ( i= 0; i < numworkers ; i++){
		
		struct NWORKER * worker =  malloc(sizeof(struct NWORKER));
		
		if(worker == NULL) {
			perror("worker  malloac failed");
			return -2;
		}
		
		memset(worker, 0, sizeof(struct NWORKER));
		
	    /*
		** 此处注意
		** 线程池的线程会回指到线程池。
		*/
		worker->pool = pool;
		worker->terminate = 0;
		
		ret = pthread_create(&worker->id, NULL, thread_cb, worker);
		if(ret){
			perror("thread_create error ");
			free(worker);
	
			return 1;
		}
		
		
		LIST_ADD(worker, pool->workers);
	}
	
	return 0;
}
/*
**  线程池销毁函数
**  1 先将线程载体的任务停止位设置1 停止所有线程的任务
**  2 加锁
*** 3 处理线程池里的所有woker 线程列表载体的
**  4 处理线程池里的所有jobs  工作列表
*/
int nThreadPoolDestory(nThreadPool * pool){
	int  i  = 0;
	struct NWORKER * worker = NULL;
	struct NWORKER * next_worker = NULL;
	struct NJOB * 	 job  = NULL;
	struct NJOB * 	 next_job  = NULL;
	 
	if(pool == NULL ) 
		return -1;
	
	for( worker  =  pool->workers; worker != NULL; worker=worker->next){
		worker->terminate = 1;
	}
	
	pthread_mutex_lock(&pool->mtx);
	worker=pool->workers;
	job=pool->jobs;
	pool->workers = NULL;
	pool->jobs = NULL;
	printf("nThreadPoolDestory ############### 1\n");
	/*唤醒所有线程*/
	pthread_cond_broadcast(&pool->cond);
	printf("nThreadPoolDestory ############### 2\n");
	pthread_mutex_unlock(&pool->mtx);
	
	for(next_worker=worker; next_worker!=NULL; next_worker=next_worker->next)
	{
		if(pthread_join(next_worker->id,NULL)!= 0 ){
			printf("pthread_join error \n");
		}
	}
	/*
	** 一点不能浪费
	** 回收剩余的线程载体链表（thread item链表）中的内存 
	*/
	if(worker)
	{
		
		printf("pool->workers is existed \n");
		next_worker  =  worker->next;
		while( worker != NULL ){
			free(worker);
			worker=next_worker;
			if(worker)
			{
				next_worker=worker->next;
			}
		}
	}
	else
	{
		printf("pool->workers is NULL \n");
	}
	/*
	** 一点不能浪费
	** 回收剩余的工作链表（job链表）中的内存 
	*/
	if(job)
	{
		printf("pool->jobs is existed \n");
		job = job;
		next_job  =  job->next;
		while( job != NULL ){
			free(job);
			job=next_job;
			if(job)
			{
				next_job=job->next;
			}
		}
	}
	else
	{
		printf("pool->jobs is NULL \n");
	}
	
	//pthread_mutex_lock(&pool->mtx);
	//pthread_mutex_destroy(&pool->mtx);
    //pthread_cond_destroy(&pool->cond);
	//free(pool);
}

/*
** 线程池pool初始化
** 1 将获得的工作放到线程池的工作列表（jobs）
** 2 并且使用线程池的条件参数，通知线程载体列表中的线程可以开始完成工作了
**  
*/
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

//工作都一样 参数也都一样  数数
void test_counter(void * args){
	
	struct NJOB * job = (struct NJOB *)args;
	int   index = 0 ;
	
	if( job!= NULL)
	{
		index = *(int *)job->user_data;
		printf(" thread id : %lu and index %d \n", pthread_self(), index);
		
		free(job->user_data);
		free(job);
	}
	else
	{
		printf("job is null maybe free in nThreadPoolDestory \n");
	}
	
}

#if 1
int main(){
	int i = 0;
	nThreadPool pool;
	
	//招人
	nThreadPoolCreate(&pool, THREAD_MAX_NUM);
	
	/*
	** 提供各种工作或任务给线程池
	** 1 将工作（或任务）挂载到线程池的job列表上。
	*/
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



















