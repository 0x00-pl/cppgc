#pragma once
#include <iostream>
#include <vector>
#include "src/parser.h"

using namespace std;

namespace pl{
  namespace test{
    bool parser(){
      string f1[]={
	"((0)",
	"(+ i 1))"
      };

      auto r= tokenlize(vector<string>(f1,f1+2));
      cout<<endl;
      for(auto i : r){
	cout<<i.text<<' ';
      }
      cout<<endl;
      //test make_exp()
      auto pe= r.begin();
      auto e= make_exp(pe, r.end());
      cout<<string(*e)<<endl;
      cout.flush();
      return true;
    }
  }
}