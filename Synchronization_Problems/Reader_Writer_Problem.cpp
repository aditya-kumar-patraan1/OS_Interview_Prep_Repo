#include <bits/stdc++.h>
#include <thread>
using namespace std;

mutex mx;
mutex wrt;
int readCount = 0;

// writer function()

void write(int id)
{
    while (true)
    {
        // locking the writer to wrt=0
        wrt.lock();

        // Critical Section
        cout << "Writer with id : " << id << " is writing data in the file" << endl;

        // signaling writer to wrt=1
        wrt.unlock();
    }
}

void read(int id){
    //locking for the reader mutex
    mx.lock();
    //increment the readerCount
    readCount++;
    if(readCount==1){   //then it is the first reader entered so lock the writer
        wrt.lock();
    }
    mx.unlock();   //unlocking the mutex of reader
    //CRITICAL SECTION FOR THE READER
    cout<<"Reader with id : "<<id<<" is performing reading operation in the file"<<endl;
    //locking the reader to exit the file and at that time no other reader is allowed to do the exit at the same time
    mx.lock();
    readCount--;   //one Reader is gone
    if(readCount==0){    //if no reader left in the file writer is allowed to do their operation in the file
        wrt.unlock();
    }
    mx.unlock();   //signaling the reader to 1
}

int main()
{
    vector<thread> threads;
    int totalReader=3,totalWriters=4;

    
    //specifying the creation of new thread for  thread(read,i+1) to instruct for reading operation
    for(int i=0;i<totalReader;i++){
        threads.push_back(thread(reader,i+1));
    }

    //specifying the creation of new thread for  thread(writer,i+1) to instruct for writing operation
    for(int i=0;i<totalWriters;i++){
        threads.push_back(thread(writer,i+1));
    }


    for(auto& th : threads){
        if(th.joinable()){
            th.join();
        }
    }
    
    return 0;
}
