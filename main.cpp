#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
using namespace std;
#include "src/gc.h"
#include "src/vm.h"

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


pl::data<int>& test_inc(pl::data<int>& v, pl::table& mp){
  int& n=v;
  n++;
  return v;
}

pl::data<int>* zero(){
  return new pl::data<int>(0);
}



int main(int argc, char **argv) {
  /*vector<thread> tp;
  for(int i=0; i<1000; i++){
    tp.push_back(thread(f,i));
  }
  //this_thread::sleep_for(chrono::seconds(1));
  glock=true;
  for(thread& t : tp){
    t.join();
  }*/
  pl::table root;
  pl::data<int>* _z= zero();
  cout<<(*_z?"true":"false")<<endl;
  test_inc(*_z,root);
  cout<<(*_z?"true":"false")<<endl;
  
  std::cout << "Hello, world!" << std::endl;
  return 0;
}
