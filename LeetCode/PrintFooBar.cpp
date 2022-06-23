/**
 * @file PrintFooBar.cpp
 * @author VictorTruong
 * 
 * @brief Print FooBar Alternately
 * @date 2022-06-23
 * @link https://leetcode.com/problems/print-foobar-alternately/ @endlink
 * 
 * 
 * Suppose you are given the following code:
class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
 * The same instance of FooBar will be passed to two different threads:
 * thread A will call foo(), while
 * thread B will call bar().
 * Modify the given program to output "foobar" n times.
 */

/**
 * @brief Example 1
 * Input: n = 1
 * Output: "foobar"
 * Explanation: There are 2 threads being fired asynchronously. 
 * One of them calls foo(), while the other calls bar(). "foobar" is being output 1 time.
 * 
 * 
 * @brief Example 2:
 * Input: n = 2
 * Output: "foobarfoobar"
 * Explanation: "foobar" is being output 2 times.
 */


/* Solution using MUTEX */
class FooBarUseMutex {
private:
    int n;
    mutex a, b;

public:
    FooBarUseMutex(int n) {
        this->n = n;
        a.lock();
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            b.lock();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            a.unlock();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            a.lock();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            b.unlock();
        }
    }
};


/* Solution using SEMAPHORE */
#include <semaphore.h>
class FooBarUseSemaphore {
private:
    int n;
    sem_t a, b;

public:
    FooBarUseSemaphore(int n) {
        this->n = n;
        // This semaphore goes first, so set it to true
        sem_init(&a, 0, 1);
        // This semaphore goes second, so set it to false
        sem_init(&b, 0 , 0);
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            sem_wait(&a);
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            sem_post(&b);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            sem_wait(&b);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            sem_post(&a);
        }
    }
};