#pragma once
#include <iostream>
#include <vector>
#include "src/parser.h"

using namespace std;

namespace pl{
  namespace test{
    bool parser(){
      string f1[]={
	"i(0)",
	"j(+ i 1)"
      };
      auto r= tokenlize(vector<string>(f1,f1+2));
      cout<<endl;
      for(auto i : r){
	cout<<i.text<<' ';
      }
      cout<<endl;
      cout.flush();
      return true;
    }
  }
}