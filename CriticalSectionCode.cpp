#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// A shared variable that will be accessed by multiple threads
int shared_counter = 0;

// The function containing the critical section
void increment_counter() {
    for (int i = 0; i < 100000; ++i) {
        // --- CRITICAL SECTION START ---
        shared_counter++; // This is a race condition!
        // --- CRITICAL SECTION END ---
    }
}

int main() {
    // Create a vector to hold our threads
    vector<thread> threads;

    // Create 10 threads, each running the increment_counter function
    for (int i = 0; i < 10; ++i) {
        threads.push_back(thread(increment_counter));
    }

    // Wait for all threads to finish their execution
    for (auto& th : threads) {
        th.join();
    }

    std::cout << "--- Unprotected Critical Section ---" << std::endl;
    std::cout << "Expected counter value: 1000000" << std::endl;
    std::cout << "Actual counter value:   " << shared_counter << std::endl;
    std::cout << "The result is incorrect because of the race condition." << std::endl;

    return 0;
}