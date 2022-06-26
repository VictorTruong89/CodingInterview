/**
 * @file PrintTextInOrderConcurrency.cpp
 * @author VictorTruong
 * 
 * @brief Execute print in multi-thread in a specific order
 * @date 2022-06-23
 * @link https://leetcode.com/problems/print-in-order/ @endlink
 * 
 * 
 * The same instance of Foo will be passed to three different threads. 
 * Thread A call first(), thread B call second(), and thread C call third(). 
 * Design a mechanism and modify the program to ensure that 
 * second() is executed after first(), and third() is executed after second().
 * 
 * Note:
 * We do not know how threads will be scheduled in the operating system, 
 * even though the numbers in the input seem to imply the ordering. 
 * The input format you see is mainly to ensure our tests' comprehensiveness.
 */

/**
 * @brief Example 1:
 * Input: nums = [1,2,3]
 * Output: "firstsecondthird"
 * Explanation: There are three threads being fired asynchronously. 
 * The input [1,2,3] means thread A calls first(), thread B calls second(), 
 * and thread C calls third(). "firstsecondthird" is the correct output.
 * 
 * 
 * @brief Example 2:
 * Input: nums = [1,3,2]
 * Output: "firstsecondthird"
 * Explanation: The input [1,3,2] means thread A calls first(), 
 * thread B calls third(), and thread C calls second(). 
 * "firstsecondthird" is the correct output.
 */


/* Solution using MUTEX */
class FooUseMutex {
public:
    mutex a, b;
    
    FooUseMutex() {
        a.lock();
        b.lock();
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        a.unlock();
    }

    void second(function<void()> printSecond) {
        // printSecond() outputs "second". Do not change or remove this line.
        a.lock();
        printSecond();
        b.unlock();
    }

    void third(function<void()> printThird) {
        // printThird() outputs "third". Do not change or remove this line.
        b.lock();
        printThird();
        b.unlock();
    }
};


/* Solution using SEMAPHORE */
#include <semaphore.h>
class FooUseSemaphore {
public:
    sem_t secondSem, thirdSem;
    
    FooUseSemaphore() {
        sem_init(&secondSem, 0, 0);
        sem_init(&thirdSem, 0, 0);
    }
    
    ~FooUseSemaphore() {
        sem_destroy(&secondSem);
        sem_destroy(&thirdSem);
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&secondSem);
    }

    void second(function<void()> printSecond) {
        // printSecond() outputs "second". Do not change or remove this line.
        sem_wait(&secondSem);
        printSecond();
        sem_post(&thirdSem);
    }

    void third(function<void()> printThird) {
        // printThird() outputs "third". Do not change or remove this line.
        sem_wait(&thirdSem);
        printThird();
    }
};