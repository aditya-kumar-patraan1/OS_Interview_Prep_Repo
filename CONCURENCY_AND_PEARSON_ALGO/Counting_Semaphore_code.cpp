#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
using namespace std;

class CountingSemaphore {
private:
    int count;                      // Number of available resources
    mutex mtx;                      // Protect shared data
    condition_variable cv;          // Block/wake threads

public:
    CountingSemaphore(int value) {
        count = value;             
    }

    void wait() {                   
        unique_lock<mutex> lock(mtx);
        while (count == 0) {        
            cv.wait(lock);
        }
        count--;                   
    }

    void signal() {                
        unique_lock<mutex> lock(mtx);
        count++;              
        cv.notify_one();          
    }
};

// Shared semaphore with 3 resources
CountingSemaphore sem(3);

void worker(int id) {
    cout << "Thread " << id << " waiting for resource...\n";
    sem.wait();  // Request resource

    cout << "Thread " << id << " acquired resource.\n";
   
    cout << "Thread " << id << " releasing resource.\n";
    sem.signal(); // Release resource
}

int main() {
    vector<thread> threads;

    // Create 6 threads
    for (int i = 1; i <= 6; i++) {
        threads.push_back(thread(worker, i));
    }

    // Wait for all threads to finish
    for (auto &t : threads) {
        t.join();
    }

    return 0;
}
