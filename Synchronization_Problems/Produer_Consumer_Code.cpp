#include<bits/stdc++.h>
#include<thread>
using namespace std;

mutex mx;
const int BUFFER_SIZE=10;
counting_semaphore<BUFFER_SIZE> full_sem(BUFFER_SIZE);
counting_semaphore<BUFFER_SIZE> empty_sem(BUFFER_SIZE);

queue<int> buffer;


void producer(int id){
  do{
    empty_sem.acquire() //wait(empty)   empty-1
    mx.wait()//wait(mutex)
    //CRITICAL SECTION 
    cout<<"Producer with id : "<<id<<" doing Production"<<endl;
    mx.signal();   //signal(mutex)
    full.release();    //signal(full)   full+1  
  }while(true);
}


void consumer(int id){
  do{
    full_sem.acquire() //wait(full)    full-1
    mx.wait()//wait(mutex)
    //CRITICAL SECTION 
    cout<<"Consumer with id : "<<id<<" doing Consumption"<<endl;
    mx.signal();   //signal(mutex)
    empty.release();    //signal(empty)   empty+1  
  }while(true);
}


int main(){
  vector<thread> thread;
  
  int producer=2,consumer=4;
  
  //thread instructing for production to buffer
  for(int i=0;i<producer;i++){
    threads.push_back(thread(producer,i+1));
  }
  
  //thread instructing for consumption from buffer
  for(int i=0;i<consumer;i++){
    threads.push_back(thread(consumer,i+1));
  }
  
  
  for(auto& th : threads){
    if(th.joinable()){
      th.join();
    }
  }
  
  return 0;
}