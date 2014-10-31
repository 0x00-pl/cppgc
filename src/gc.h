#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <mutex>
#include <thread>
using namespace std;

namespace pl{
  class gc_common{
  public:
    typedef void handle(gc_common*p);
    int64_t flags;
    
    virtual~gc_common()= default;
    virtual void each(function<handle> f){}
    virtual operator const string&(){
      static string ret("gc_common");
      return ret;
    }
    virtual operator bool(){
      return false;
    }
    virtual bool leaf(){
      return true;
    }
  };
  
  namespace gc__nomove__mark_sweep__vector_store{
    typedef gc_common* pgc;
    vector<pgc> pool;
    vector<pgc> mark_stack;
    mutex pool_m;
    void manage(pgc p){
      pool_m.lock();
      p->flags=1;
      pool.push_back(p);
      pool_m.unlock();
    }
    void mark(pgc root){
      pool_m.lock();
      root->flags=1;
      mark_stack.push_back(root);
      int n=0;
      while(!mark_stack.empty()){
	if(++n>1000){
	  pool_m.unlock();
	  this_thread::yield();
	  pool_m.lock();
	}
	pgc cur= mark_stack.back();
	mark_stack.pop_back();
	if(cur->flags==0){
	  cur->flags=1;
	  cur->each([&](gc_common*p){mark_stack.push_back(p);});
	}
      }
      pool_m.unlock();
    }
    void sweep(){
      vector<pgc>& reuse_empty_vector= mark_stack;
      vector<pgc>& new_pool= reuse_empty_vector;
      vector<pgc> tobe_del;
      new_pool.clear();
      
      pool_m.lock();
      for(auto i : pool){
	if(i->flags!=0){
	  new_pool.push_back(i);
	}else{
	  tobe_del.push_back(i);
	}
      }
      pool.swap(new_pool);
      pool_m.unlock();
      
      for(auto i : tobe_del){
	delete i;
      }
      new_pool.clear();
    }
    void collect(pgc root){
      mark(root);
      sweep();
    }
  }
  namespace gc__nomove__mark_sweep__list_store{}
  namespace gc__move__copy_free__mark_sweep__list_store{}
  
  //typedef gc__nomove__mark_sweep__vector_store::pgc pgc;
  //void manage(pgc p)=gc__nomove__mark_sweep__vector_store::manage;
  //void collect(pgc root)=gc__nomove__mark_sweep__vector_store::collect;
}
