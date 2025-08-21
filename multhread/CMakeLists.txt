cmake_minimum_required(VERSION 3.14)
project(multhread)

add_executable(atomic_example atomic_example.cpp)
target_link_libraries(atomic_example PUBLIC pthread)

add_executable(memory_order memory_order.cpp)
target_link_libraries(memory_order PUBLIC pthread)

add_executable(thread_example thread_example.cpp)
target_link_libraries(thread_example PUBLIC pthread)

add_executable(pthread_example pthread_example.cpp)
target_link_libraries(pthread_example PUBLIC pthread)

add_executable(future future.cpp)
target_link_libraries(future PUBLIC pthread)

add_executable(mutex mutex.cpp)
target_link_libraries(mutex PUBLIC pthread)

add_executable(condition_varible condition_varible.cpp)
target_link_libraries(condition_varible PUBLIC pthread)

add_executable(semaphore semaphore.cpp)
target_link_libraries(semaphore PUBLIC pthread)