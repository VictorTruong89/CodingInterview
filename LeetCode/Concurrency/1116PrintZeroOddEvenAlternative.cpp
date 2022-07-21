/**
 * @file 1116PrintZeroOddEvenAlternative.cpp
 * @author Victor Truong
 * 
 * @brief Print 0-Odd-0-Even in series until it reaches a given n-number
 * @date 2022-06-24
 * @link https://leetcode.com/problems/print-zero-even-odd/ @endlink
 * 
 * 
 * You are given an instance of the class ZeroEvenOdd that has three functions: zero, even, and odd. 
 * The same instance of ZeroEvenOdd will be passed to three different threads:
 *      Thread A: calls zero() that should only output 0's.
 *      Thread B: calls even() that should only output even numbers.
 *      Thread C: calls odd() that should only output odd numbers.
 * Modify the given class to output the series "010203040506..." where the length of the series must be 2n.
 * Implement the ZeroEvenOdd class:
 *      ZeroEvenOdd(int n) Initializes the object with the number n that represents the numbers that should be printed.
 *      void zero(printNumber) Calls printNumber to output one zero.
 *      void even(printNumber) Calls printNumber to output one even number.
 *      void odd(printNumber) Calls printNumber to output one odd number.
 */

/**
 * @brief Example 1:
 * Input: n = 2
 * Output: "0102"
 * Explanation: There are three threads being fired asynchronously. One of them calls zero(), the other calls even(), and the last one calls odd().
 * 
 * 
 * @brief Example 2:
 * Input: n = 5
 * Output: "0102030405"
 */


/*========== Using MUTEX ==========*/
class ZeroEvenOdd {
private:
    int n;
    int count = 1;
    mutex lock0, lock1, lock2;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        // The order in which lock2 lock() first, before lock1 is critical, because of the printing sequence below:
        // T0: lock0.lock() >> print(0) >> lock1.unlock()                                               >> lock0.lock() >> print(0) >> lock2.unlock()
        // T1:                                            >> lock1.lock() >> print(1) >> lock0.unlock() 
        // T2:                                                                                                                                        >> lock2.lock() >> print(2) >> lock0.unlock()
        lock2.lock();
        lock1.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 0; i < n; i++) {
            lock0.lock();
            printNumber(0);
            
            // At 1st iteration, count==1 >> lock1.unlock() first
            if(count % 2 != 0) {
                lock1.unlock();
            } else {
                lock2.unlock();
            }
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i = 1; i < n; i += 2) {
            lock2.lock();
            printNumber(count++);
            lock0.unlock();
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 0; i < n; i += 2) {
            lock1.lock();
            printNumber(count++);
            lock0.unlock();
        }
    }
};


/*========== Using SEMAPHORE ==========*/
#include <semaphore.h>
class ZeroEvenOdd {
private:
    int n;
    int count = 0;
    sem_t sem0, sem1, sem2;
    bool breaker = false;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&sem0, 0, 1); // Unlock thread0 immediately
        sem_init(&sem1, 0, 0); // Lock thread1
        sem_init(&sem2, 0, 0); // Lock thread2
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(true) {
            // Wait for print(0) turn
            sem_wait(&sem0);
            
            // Terminate thread
            if(++count > n) {
                breaker = true;
                sem_post(&sem2); // Signal thread2 to terminate as breaker==true
                sem_post(&sem1); // Signal thread1 to terminate as breaker==true
                break;
            }
            
            printNumber(0);
            
            // Signal either Odd or Even thread in next step
            if(count % 2 == 0) {
                sem_post(&sem2);
            } else {
                sem_post(&sem1);
            }
        }
    }

    void even(function<void(int)> printNumber) {
        while(true) {
            sem_wait(&sem2);
            
            // Terminate this thread after count > n
            if(breaker) break;
            
            printNumber(count);
            
            // Awake thread0 again
            sem_post(&sem0);
        }
    }

    void odd(function<void(int)> printNumber) {
        while(true) {
            sem_wait(&sem1);
            
            if(breaker) break;
            
            printNumber(count);
            
            sem_post(&sem0);
        }
    }
};


/*========== Using CONDITION VARIABLE ==========*/
class ZeroEvenOdd {
private:
    int n;
    bool isZero, isOdd;
    pthread_mutex_t lock;
    pthread_cond_t condZero;
    pthread_cond_t condNonZero;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        isZero = true;
        isOdd = true;
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&condZero, NULL);
        pthread_cond_init(&condNonZero, NULL);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 0; i < n; i++) {
            pthread_mutex_lock(&lock);
            while(!isZero) {
                pthread_cond_wait(&condZero, &lock);
            }
            printNumber(0);
            isZero = false;
            
            pthread_cond_signal(&condNonZero);
            pthread_mutex_unlock(&lock);
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n; i += 2) {
            pthread_mutex_lock(&lock);
            while(isZero || isOdd) {
                pthread_cond_wait(&condNonZero, &lock);
            }
            printNumber(i);
            isZero = true;
            isOdd = !isOdd;
            
            pthread_cond_signal(&condZero);
            pthread_mutex_unlock(&lock);
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1; i <= n; i += 2) {
            pthread_mutex_lock(&lock);
            while(isZero || !isOdd) {
                pthread_cond_wait(&condNonZero, &lock);
            }
            printNumber(i);
            isZero = true;
            isOdd = !isOdd;
            pthread_cond_signal(&condZero);
            pthread_mutex_unlock(&lock);
        }
    }
};