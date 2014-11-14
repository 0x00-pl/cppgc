#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "gc.h"
#include "number.h"

namespace pl{
  namespace ptp{
    class number :public gc_common{
    public:
      number(pl::number v):val(v){}
      pl::number val;
      virtual operator string(){
	return str(val);
      }
      virtual operator bool(){
	return (bool)val;
      }
    };
    class str :public gc_common{
    public:
      string s;
      str(string _s):s(_s){}
      virtual operator string(){
	return string("\"")+s+"\"";
      }
      virtual operator bool(){
	return !s.empty();
      }
    };
    class symbol :public gc_common{
    public:
      string s;
      symbol(string _s):s(_s){}
      virtual operator string(){
	return s;
      }
      virtual operator bool(){
	return !s.empty();
      }
    };
    class exp :public gc_common{
    public:
      vector<pgc> e;
      map<string,size_t>* nametab;
      exp():nametab(nullptr){}
      ~exp(){delete nametab;}
      void push(pgc v){
	e.push_back(v);
      }
      void push(string name, pgc v){
	if(nametab==nullptr){
	  nametab= new map<string,size_t>();
	}
	(*nametab)[name]= e.size();
	push(v);
      }
      pgc get(size_t index){
	return e[index];
      }
      pgc get(string name){
	if(nametab==nullptr){return nullptr;}
	if(nametab->find(name)==nametab->end()){return nullptr;}
	return get((*nametab)[name]);
      }
      virtual void each(function<handle> f){
	for(auto i : e){
	  i->each(f);
	}
      }
      virtual operator string(){
	static string ret("(");
	map<size_t,string> nametab_refback;
	if(nametab!=nullptr){
	  for(const auto& i : *nametab){
	    nametab_refback[i.second]= i.first;
	  }
	}
	for(size_t i=0; i<e.size(); ++i){
	  if(nametab_refback.find(i)!=nametab_refback.end()){
	    ret+= nametab_refback[i]+ ":";
	  }
	  ret+= string(*e[i])+" ";
	}
	return ret+")";
      }
      virtual operator bool(){
	return !e.empty();
      }
      virtual bool leaf(){
	return false;
      }
    };
  }
}