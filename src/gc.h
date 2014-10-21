#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
using namespace std;

namespace pl{
  class gc_commmon{
  public:
    typedef void handle(gc_common*p);
    
    virtual~gc_common(){}
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
  
  namespace gc__nomove__mark_sweep__vector_store{}
  namespace gc__nomove__mark_sweep__list_store{}
  namespace gc__move__copy_free__mark_sweep__list_store{}
}
