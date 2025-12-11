#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;    // Create a lock

int counter = 0;  // Shared variable

void increment(int id) {
    mtx.lock();   // Lock before accessing shared data
    cout << "Thread " << id << " is running\n";
    counter++;    // Critical section (shared resource)
    mtx.unlock(); // Unlock after done
}

int main() {
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();

    cout << "Final Counter Value: " << counter << endl;
    return 0;
}



