/**
 * @file 1226DiningPhilosophers.cpp
 * @author VictorTruong
 * 
 * @brief The dining philosophers with Concurrency
 * @date 2022-06-26
 * @link https://leetcode.com/problems/the-dining-philosophers/ @endlink
 * 
 * 
 * 5 silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.
 * 
 * Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. 
 * Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. 
 * After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. 
 * A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.
 * 
 * Design a discipline of behaviour (a concurrent algorithm) such that no philosopher will starve; i.e., 
 * each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.
 * 
 * The philosophers' ids are numbered from 0 to 4 in a clockwise order. 
 * Implement the function void wantsToEat(philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork) where:
 *      philosopher is the id of the philosopher who wants to eat.
 *      pickLeftFork and pickRightFork are functions you can call to pick the corresponding forks of that philosopher.
 *      eat is a function you can call to let the philosopher eat once he has picked both forks.
 *      putLeftFork and putRightFork are functions you can call to put down the corresponding forks of that philosopher.
 *      The philosophers are assumed to be thinking as long as they are not asking to eat (the function is not being called with their number).
 * 
 * Five threads, each representing a philosopher, will simultaneously use one object of your class to simulate the process. 
 * The function may be called for the same philosopher more than once, even before the last call ends.
 */


/*========== LeetCode using MUTEX ==========*/
static const uint8_t FORKS_NUM = 5;
class DiningPhilosophers {
private:
    pthread_mutex_t forks[FORKS_NUM];
public:
    DiningPhilosophers() {
        for(int i = 0; i < FORKS_NUM; i++) {
            pthread_mutex_init(&forks[i], NULL);
        }
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        uint8_t leftForkId = (philosopher + 1) % FORKS_NUM;
        uint8_t rightForkId = philosopher;

        if(philosopher < FORKS_NUM - 1) {
            pthread_mutex_lock(&forks[rightForkId]);
            pthread_mutex_lock(&forks[leftForkId]);
        } else {
            // This prevent the circular wait condition (deadlock)
            pthread_mutex_lock(&forks[leftForkId]);
            pthread_mutex_lock(&forks[rightForkId]);
        }

        pickLeftFork();
        pickRightFork();
        eat();

        putLeftFork();
        pthread_mutex_unlock(&forks[leftForkId]);

        putRightFork();
        pthread_mutex_unlock(&forks[rightForkId]);
    }
};


/*========== General Code from GeeksForGeeks ==========*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};
sem_t mutex;
sem_t S[N];

void test(int phnum) {
    if(state[phnum] == HUNGRY && 
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
            state[phnum] = EATING;
            sleep(2);
            pritnf("Philosopher [%d] takes fork [%d] and [%d]\n", phnum+1, LEFT+1, phnum+1);
            pritnf("Philosopher [%d] is Eating\n", phnum+1);
            // sem_post(&S[phnum]) has no effect during takefork used to wake up hungry Philosophers during putfork
            sem_post(&S[phnum]);
        } 
}

void take_fork(int phnum) {
    sem_wait(&mutex);

    state[phnum] = HUNGRY;
    printf("Philosopher [%d] is Hungry\n", phnum+1);

    // Eat if neighbors are not hungry
    test(phnum);
    sem_post(&mutex);

    // If unable to eat, wait to be signalled
    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum) {
    sem_wait(&mutex);

    state[phnum] = THINKING;
    printf("Philosopher [%d] put down fork [%d] and fork [%d]\n", phnum+1, LEFT+1, phnum+1);
    printf("Philosopher [%d] is thinking.\n", phnum+1);

    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    while(true) {
        int* i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main() {
    pthread_t threadId[N];

    // Initialize the semaphore
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < n; i++)
        sem_init(&S[i], 0, 0);
    for(int i = 0; i < N; i++) {
        pthread_create(&threadId[i], NULL, philosopher, &phil[i]);
        printf("Philosopher [%d] is Thinking\n", i+1);
    }

    for(int i = 0, i < N, i++) {
        pthread_join(threadId[i], NULL);
    }
}