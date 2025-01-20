#include <semaphore.h>
#include <thread>
#include <vector>
#include <iostream>

/**************** sem_init *******************/
// int sem_init(sem_t *sem, int pshared, unsigned int value);
//  - sem: a pointer to the semaphore object
//  - pshared: a flag indicating whether or not the semaphore should be shared with forked processes
//    - 0: the semaphore is shared between threads of the same process
//    - non-zero: the semaphore is shared between processes
//  - value: the initial value of the semaphore
// typedef union
// {
//   char __size[__SIZEOF_SEM_T];
//   long int __align;
// } sem_t;

/**************** sem_wait *******************/
// int sem_wait(sem_t *sem);
//  - sem: a pointer to the semaphore object
// sem_wait 是一个阻塞的函数，测试所指定信号量的值，它的操作是原子的。
//  - 若 sem value > 0，则该信号量值减去 1 并立即返回。
//  - 若 sem value = 0，则阻塞直到 sem value > 0，此时立即减去 1，然后返回。
// return: 若成功返回 0，失败返回 -1，并设置 errno 为 EINTR。

/**************** sem_trywait *******************/
// int sem_trywait(sem_t *sem);
//  - sem: a pointer to the semaphore object
// sem_trywait 是非阻塞的函数，它会尝试获取获取 sem value 值
//  - 若 sem value > 0，则该信号量值减去 1 并立即返回。
//  - 若 sem value = 0，则立即返回一个错误码 EAGAIN。

/**************** sem_post *******************/
// int sem_post(sem_t *sem);
//  - sem: a pointer to the semaphore object
// sem_post 把指定的信号量 sem 的值加 1，如果有线程阻塞在该信号量上，那么会唤醒其中一个线程。

/**************** sem_getvalue *******************/
// int sem_getvalue(sem_t *sem, int *sval);
//  - sem: a pointer to the semaphore object
//  - sval: a pointer to an integer to store the value of the semaphore
// 获取信号量 sem 的当前值，把该值保存在 sval，若有 1 个或者多个线程正在调用 sem_wait 阻塞在该信号量上，该函数返回阻塞在该信号量上进程或线程个数。

/**************** sem_destroy *******************/
// int sem_destroy(sem_t *sem);
//  - sem: a pointer to the semaphore object
// 释放信号量 sem 占用的资源，但是不会释放信号量本身。成功返回 0，失败返回 -1。


int main() {
    sem_t sem;
    sem_init(&sem, 0, 1);

    int value = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread([&sem, &value](){
            sem_wait(&sem);
            value++;
            std::cout << value << std::endl;
            sem_post(&sem);
        }));
    }

    for (auto& t : threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    sem_destroy(&sem);
}