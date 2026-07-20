#include <assert.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <deque>

/************************create and exit********************** */

int ret = 0;

void *print_message_function(void *ptr) {
  char *message;
  message = (char *)ptr;
  printf("%s \n", message);
  printf("pthread_self %lu\n", pthread_self());
}

void *exit_message_function(void *ptr) {
  pthread_exit(&ret);
  char *message;
  message = (char *)ptr;
  printf("%s \n", message);
}

void create_exit() {
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int iret1, iret2;

  /* Create independent threads each of which will execute function */
  iret1 = pthread_create(&thread1, NULL, print_message_function, (void *)message1);
  iret2 = pthread_create(&thread2, NULL, exit_message_function, (void *)message2);

  printf("thread1 id: %lu\n", thread1);
  printf("thread2 id: %lu\n", thread2);
  printf("ret %d\n", ret);

  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Thread 1 returns: %d\n", iret1);
  printf("Thread 2 returns: %d\n", iret2);
}

/************************schedule********************** */

struct Shared {
  pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

  std::deque<int> q;
  bool done = false;
};

void *Producer(void* arg) {
  pthread_setname_np(pthread_self(), "producer");
  auto * s = static_cast<Shared*>(arg);
  for(int i = 0; i < 5; i++) {
    pthread_mutex_lock(&s->mtx);
    s->q.push_back(i);
    pthread_cond_signal(&s->cv);
    pthread_mutex_unlock(&s->mtx);
  }
  pthread_mutex_lock(&s->mtx);
  s->done = true;
  pthread_cond_broadcast(&s->cv);
  pthread_mutex_unlock(&s->mtx);
  return nullptr;
}

void *Consumer(void* arg) {
  pthread_setname_np(pthread_self(), "consumer");
  auto * s = static_cast<Shared*>(arg);
  while(true) {
    pthread_mutex_lock(&s->mtx);
    while(s->q.empty() && !s->done) {
      pthread_cond_wait(&s->cv, &s->mtx);
    }
    if(s->q.empty() && s->done) {
      pthread_mutex_unlock(&s->mtx);
      break;
    }

    int v = s->q.front();
    s->q.pop_front();
    pthread_mutex_unlock(&s->mtx);
    printf("consumer get %d\n", v);
  }

  return nullptr;
}

void producer_consumer() {
  Shared s;
  pthread_t tp, tc;
  pthread_create(&tp, NULL, Producer, &s);
  pthread_create(&tc, NULL, Consumer, &s);

  pthread_join(tp, nullptr);
  pthread_join(tc, nullptr);
  pthread_mutex_destroy(&s.mtx);
  pthread_cond_destroy(&s.cv);
}

/************************schedule********************** */

//打印当前的线程调度策略
static int get_thread_policy(pthread_attr_t *attr) {
  int policy;
  int rs = pthread_attr_getschedpolicy(attr, &policy);
  assert(rs == 0);
  switch (policy) {
    case SCHED_FIFO:
      printf("policy= SCHED_FIFO\n");
      break;
    case SCHED_RR:
      printf("policy= SCHED_RR\n");
      break;
    case SCHED_OTHER:
      printf("policy=SCHED_OTHER\n");
      break;
    default:
      printf("policy=UNKNOWN\n");
      break;
  }
  return policy;
}

//打印当前调度策略线程的最高和最低优先级
static void show_thread_priority(pthread_attr_t *attr, int policy) {
  int priority = sched_get_priority_max(policy);
  assert(priority != -1);
  printf("max_priority=%d\n", priority);
  priority = sched_get_priority_min(policy);
  assert(priority != -1);
  printf("min_priority=%d\n", priority);
}

//打印当前线程的优先级
static int get_thread_priority(pthread_attr_t *attr) {
  struct sched_param param;
  int rs = pthread_attr_getschedparam(attr, &param);
  assert(rs == 0);
  printf("priority=%d\n", param.__sched_priority);
  return param.__sched_priority;
}

//设置线程线程的调度策略
static void set_thread_policy(pthread_attr_t *attr, int policy) {
  int rs = pthread_attr_setschedpolicy(attr, policy);
  assert(rs == 0);
  get_thread_policy(attr);
}

void schedule() {
  pthread_attr_t attr;
  struct sched_param sched;
  int rs;
  rs = pthread_attr_init(&attr);
  assert(rs == 0);

  //获取默认的线程调度策略
  printf("==    Show current configuration of priority    ==\n");
  int policy = get_thread_policy(&attr);
  show_thread_priority(&attr, policy);
  //打印当前线程的优先级
  printf("show priority of current thread\n");
  int priority = get_thread_priority(&attr);

  printf("==   Show different Scheduling method priority   ==\n");
  //获取SCHED_FIFO调度策略的最高和最低优先级
  printf("show SCHED_FIFO of priority:\n");
  show_thread_priority(&attr, SCHED_FIFO);

  //获取SCHED_RR调度策略的最高和最低优先级
  printf("show SCHED_RR of priority:\n");
  show_thread_priority(&attr, SCHED_RR);

  printf("==        Set thread policy        == \n");
  //设置线程的调度属性为SCHED_FIFO
  printf("set SCHED_FIFO policy:\n");
  set_thread_policy(&attr, SCHED_FIFO);
  priority = get_thread_priority(&attr);
  sched.__sched_priority = 99;
  pthread_attr_setschedparam(&attr, &sched);
  priority = get_thread_priority(&attr);

  //设置线程的调度属性为SCHED_RR
  printf("set SCHED_RR policy:\n");
  set_thread_policy(&attr, SCHED_RR);
  priority = get_thread_priority(&attr);
  sched.__sched_priority = 55;
  pthread_attr_setschedparam(&attr, &sched);
  priority = get_thread_priority(&attr);

  //恢复线程的调度策略
  printf("Restore current policy:\n");
  set_thread_policy(&attr, policy);

  rs = pthread_attr_destroy(&attr);
  assert(rs == 0);
}

/************************affinity********************** */
inline int set_cpu(int i) {
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(i, &mask);

  printf("thread %lu, i = %d\n", pthread_self(), i);
  if (-1 == pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask)) {
    fprintf(stderr, "pthread_setaffinity_np erro\n");
    return -1;
  }
  return 0;
}

void *fun(void *ptr) {
  char *message;
  message = (char *)ptr;
  pthread_setname_np(pthread_self(), message);
  set_cpu(0);
  while (1) {
    // printf("%s \n", message);
    // usleep(1000000);
  }
}

void setaffinity() {
  pthread_t thread1, thread2;
  char *value1 = "AAAA";
  char *value2 = "BBBB";

  pthread_attr_t attr1, attr2;
  struct sched_param sched1, sched2;
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);

  // 重要
  pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

  set_thread_policy(&attr1, SCHED_OTHER);
  sched1.__sched_priority = 10;
  pthread_attr_setschedparam(&attr1, &sched1);
  get_thread_priority(&attr1);

  set_thread_policy(&attr2, SCHED_FIFO);
  sched2.__sched_priority = 20;
  pthread_attr_setschedparam(&attr2, &sched2);
  get_thread_priority(&attr2);

  /* Create independent threads each of which will execute function */
  int rt = pthread_create(&thread2, &attr2, fun, (void *)value2);
  if(rt != 0) {
    std::cerr << "pthrad2 create failed!" << std::endl;
  }
  rt = pthread_create(&thread1, &attr1, fun, (void *)value1);
  if(rt != 0) {
    std::cerr << "pthrad1 create failed!" << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));

  pthread_join(thread2, NULL);
  pthread_join(thread1, NULL);
  
  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
}

/************************prctl********************** */
#include <sys/prctl.h>

/**
 * int prctl(int option, unsigned long arg2, ...);
 * @brief pthread底层调用的就是prctl
 * @note option:
 *           1. PR_SET_NAME/PR_GET_NAME 
 *           2. PR_SET_PDEATHSIG，父线程死了给我发某信号，用于孤儿线程清理
 *           3. PR_SET_DUMPABLE，是否允许生成core
 */
void prctl_test() {
  prctl(PR_SET_NAME, "worker", 0, 0, 0);
}

main() {
  std::cout << "============================ create and exit ============================" << std::endl;
  create_exit();
  std::cout << "============================ producer_consumer ============================" << std::endl;
  producer_consumer();
  std::cout << "============================ schelue ============================" << std::endl;
  schedule();
  std::cout << "============================ prctl_test ============================" << std::endl;
  prctl_test();
  std::cout << "============================ setaffinity ============================" << std::endl;
  setaffinity();
}
