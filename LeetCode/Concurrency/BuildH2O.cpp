/**
 * @file BuildH2O.cpp
 * @author VictorTruong
 * 
 * @brief There are 2 kinds of threads: oxygen and hydrogen. Your goal is to group these threads to form water molecules.
 * @date 2022-06-25
 * @link https://leetcode.com/problems/building-h2o/ @endlink
 * 
 * 
 * There is a barrier where each thread has to wait until a complete molecule can be formed. 
 * Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods respectively, 
 * which will allow them to pass the barrier. These threads should pass the barrier in groups of 3, 
 * and they must immediately bond with each other to form a water molecule. 
 * You must guarantee that all the threads from 1 molecule bond before any other threads from the next molecule do.
 * 
 * In other words:
 *      If an oxygen thread arrives at the barrier when no hydrogen threads are present, it must wait for two hydrogen threads.
 *      If a hydrogen thread arrives at the barrier when no other threads are present, it must wait for an oxygen thread and another hydrogen thread.
 * 
 * Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.
 */

/**
 * @brief Example 1:
 * Input: water = "HOH"
 * Output: "HHO"
 * Explanation: "HOH" and "OHH" are also valid answers.
 * 
 * 
 * @brief Example 2:
 * Input: water = "OOHHHH"
 * Output: "HHOHHO"
 * Explanation: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" and "OHHOHH" are also valid answers.
 */

/*========== Use SEMAPHORE ==========*/
#include <semaphore.h>
class H2O 
{
    int countH = 0;
    sem_t semH, semO;

public:
    H2O() 
    {
        sem_init(&semH, 0, 1);
        sem_init(&semO, 0, 1);
    }

    void hydrogen(function<void()> releaseHydrogen) 
    {
        sem_wait(&semH);
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        countH++;
        if(countH >= 2) {
            countH = 0;
            sem_post(&semO);
        }
    }

    void oxygen(function<void()> releaseOxygen) 
    {
        sem_wait(&semO);
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        
        // Signal semH twice to allow thread hydrogen to run twice
        sem_post(&semH);
        sem_post(&semH);
    }
};