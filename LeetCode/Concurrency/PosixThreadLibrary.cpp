/**
 * @file PosixThreadLibrary.cpp
 * @author VictorTruong
 * 
 * @brief Fundamental of Poxis Thread library (pthread.h)
 * @date 2022-06-23
 * @link https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html @endlink
 * 
 */


/** ==================================================
 * @brief THREAD BASICS
 * 
 * Thread operation includes: thread creation, termination, synchronization (join, blocking), scheduling, data management and process interraction.
 * A thread does not maintain a list of created threads, not does it know the thread that created it.
 * All threads within a same process share the same address space.
 * 
 * Threads in a process share:
 *  Process instructions
 *  Most data
 *  Open files (descriptors)
 *  Signals & signal handlers
 *  Current working directory
 *  User and group ID
 * 
 * Each thread has its unique:
 *  Thread ID
 *  Set of registers, stack pointer
 *  Stack for local variables, return addresses.
 *  Signal mask
 *  Priority
 *  Return value: errno
 * 
 * Thread functions return '0' if OK
 */


/**
 * @brief THREAD CREATION & TERMINATION
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message_function(void* ptr) {
    char* message;
    message = (char*) ptr;
    printf("*s \n", message);
}

main() {
    pthread thread1, thread2;
    char* message1 = "Thread 1";
    char* message2 = "Thread 2";
    int iret1, iret2;

    // Create independent threads, each of which will execute function
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    // Wait for the threads complete, before main() continues. Otherwise
    // we run the risk of exit, terminating the process before all threads complete.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


/** ==================================================
 * @brief THREAD SYNCHRONIZATION - MUTEX
 * 
 * MUTEX are used to prevent data inconsistencies due to race conditions.
 * A race condition occurs when2 or more threads perform operation on the same memory area.
 * But the result of computation depends on the order in which these operations are performed.
 * 
 * MUTEX allows to serialize shared memory. Anytime a global resources is accessed by more than 1 thread,
 * the resource should have a MUTEX associated with it.
 * 
 * MUTEX can only work on threads of a single process, cannot be shared between processes as SEMAPHORE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;
void* functionC() {
    pthread_mutex_lock(&mutex1);
    counter++;
    printf("Counter value: %d\n", counter);
    pthread_mutex_unlock(&mutex1);
}
main() {
    int rc1, rc2;
    pthread_t thread1, thread2;

    // Create independent threads, each will execute functionC()
    if( (rc1 = pthread_create(&thread1, NULL, functionC, NULL)) ) {
        printf("Thread creation failed: %d \n", rc1);
    }
    if( (rc2 = pthread_create(&thread1, NULL, functionC, NULL)) ) {
        printf("Thread creation failed: %d \n", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


/**
 * @brief THREAD SYNCHRONIZATION - CONDITION VARIABLES
 * CONDITION VARIABLE is a variable of type pthread_cond_t, used with the appropriate functions for waiting and later, process continuation.
 * CONDITION VARIABLE mechanism allows threads to suspend execution and relinquish the processor until some condition is true.
 * CONDITION VARIABLE must always be associated with a MUTEX to avoid race condition created by 1 thread preparing to wait 
 * and another thread which may signal the condition before the 1st thread actually waits on it resulting a deadlock.
 * The thread will be perpetually waiting for a signal that is never sent.
 * 
 * pthread_cond_init()
 * pthread_cond_destroy()
 * pthread_cond_wait
 * pthread_cond_timedwait
 * pthread_cond_signal
 * pthread_cond_braodcast
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;
int count = 0;
#define COUNT_DONE  10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

void* functionCount1() {
    while(1) {
        pthread_mutex_lock(&condition_mutex);
        // pthread_mutex_lock() protect "count" when checking (count >= COUNT_HALT1 && count <= COUNT_HALT2)
        while(count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            // When count = 3, 4, 5, 6 
            // pthread_cond_wait() atomatically release condition_mutex
            // pthread_cond_wait(), at same time, blocks thread1 until the condition_cond is signaled from thread2
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount1: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if(count >= COUNT_DONE) 
            return NULL;
    }
}

void* functionCount2() {
    while(1) {
        pthread_mutex_lock(&condition_mutex);
        // pthread_mutex_lock() protect "count" when checking (count < COUNT_HALT1 || count > COUNT_HALT2)
        if(count < COUNT_HALT1 || count > COUNT_HALT2) {
            // When count = 0, 1, 2, 7, 8, 9, 10
            // pthread_cond_signal() atomatically waken thread1 through condition_cond
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount2: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if(count >= COUNT_DONE)
            return NULL;
    }
}

main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, functionCount1, NULL);
    pthread_create(&thread2, NULL, functionCount2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
/*
                count=0         | count=1           | count = 2         | count = 3         | count = 4         | count = 6         | count = 7
------------------------------------------------------------------------------------------------------------------------------------------------------------
Thread1         running         | running           | running           | blocked           | blocked           | blocked           | running
cond_wait()     skip            | skip              | skip              | block Thread1     | block Thread1     | block Thread1     | awaken
count++         count = 1       | count = 2         | count = 3         | blocked           | blocked           | blocked           | count = 8
------------------------------------------------------------------------------------------------------------------------------------------------------------
Thread2         running         | running           | running           | running           | running           | running           | running
cond_signal()   run & no-effect | run & no-effect   | run & no-effect   | skip              | skip              | skip              | run & wake Thread1
count++         count = 1       | count = 2         | count = 3         | count = 4         | count = 5         | count = 7         | count = 8
In this example, CONDVAR only blocks thread1 when count = [3,4,5,6] . Elsewhere, everything is random, depending on either thread1 or thread2 acquire count_mutex first.
Thread2 always ready, regardless of value of "count"
*/



/** ==================================================
 * @brief THREAD SCHEDULING
 * 
 * When this option is enabled, each thrad may have its own scheduling properties.
 * Scheduling attributes may be specified as:
 *      during thread creation
 *      by dynamically changing the attributes of a thread that is already created.
 *      by defining the effect of a mutex on the thread's scheduling when creating that mutex.
 *      by dynamically changing the scheduling of a thread during synchronization operations.
 * 
 * pthread library provides default values that are sufficient for most cases.
 */


/** ==================================================
 * @brief THREAD PITFALLS
 * 
 * Race Condition :
 * While the code may be written in the order that you wish it to eecute,
 * threads are scheduled by the OS to be executed at random.
 * It cannot be assumed that threads are executed in the order they are created.
 * Threads may be running at different speeds. This give unexpected results.
 * 
 * Thread Safe Code :
 * The threaded routine must call functions which are "thread safe".
 * This means that there are no static or global variable which other threads may clobber,
 * or read assuming single threaded operation.
 * If static or global variables are used, they must be protected by MUTEX.
 * 
 * in C, local variables are dynamically allocated on stack. 
 * Therefore, any function that does not use static data or other shared resources is thread-safe.
 * 
 * Deadlock :
 * This condition occurs when a mutex is applied, but later not "unlock".
 * This causes the program execution to halt indefinitely.
 * 1st reason is because a thread trying to lock a mutex twice.
 * 2nd reason is because of poorly-designed order of lock/unlock several mutexes. 
 */