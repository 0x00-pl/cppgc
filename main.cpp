#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
#include "src/gc.h"
#include "src/parser.h"

#include "test.h"

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
  pl::test::parser();
  
  /*
    token_type type;
    string text;
    string filename;
    size_t ln;
    size_t ch;*/
  pl::token t= pl::token({pl::token_type::number,"","",1,1});
  return 0;
}
