#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
using namespace std;

mutex Mstdout;
bool glock=false;

void f(int n){
  int count=0;
  this_thread::sleep_for(chrono::seconds(1));
  /*Mstdout.lock();
  cout<<"beg "<<n<<endl;
  Mstdout.unlock();*/
  while(!glock){ count++; 
    //this_thread::yield(); 
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  Mstdout.lock();
  cout<<"end "<<n<<" : "<<count<<endl;
  Mstdout.unlock();
}


int main(int argc, char **argv) {
  
  std::cout << "Hello, world!" << std::endl;
  return 0;
}
