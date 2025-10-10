#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex forks[NUM_PHILOSOPHERS];

void philosopher_life(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // 1. THINK
        cout << "Philosopher " << id << " is thinking." << endl;

        // 2. EAT
        cout << "Philosopher " << id << " is hungry." << endl;

        // Critical Section
        // The last philosopher (id 4) picks up the right fork first.
        if (id == NUM_PHILOSOPHERS - 1) {
            forks[right_fork].lock();
            forks[left_fork].lock();
        }
        // Everyone else picks up the left fork first.
        else {
            forks[left_fork].lock();
            forks[right_fork].lock();
        }

        cout << "Philosopher " << id << " is EATING." << endl;
    
        // IMPORTANT: Put down the forks when done.
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = thread(philosopher_life, i);
    }

    // Wait for all threads to finish (they run forever)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        if(philosophers[i].joinable()){
            philosophers[i].join();
    }

    return 0;
}