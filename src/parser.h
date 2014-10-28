#pragma once
#include <string>

using namespace std;

namespace pl{
  static const string token_type[]={
    "number",
    "operator",
    "space",
    "str",
    "symbol"
  };
  class token_type_refback{
  public:
    const int number =0;
    const int op     =1;
    const int space  =2;
    const int str    =3;
    const int symbol =4;
  };
  class token{
  public:
    string text;
    string* type;
    string filename;
    size_t ln;
    size_t ch;
  };
  
  vector<token> tokenlize(vector<string> lines, string filename = "no-file"){
    size_t ln=0;
    for(string line : lines){
      ++ln;
      const char* pt= line.c_str();
      
      
    }/*
    size_t ln;
    size_t ch;
    while(pt!='\0'){
      space
      if(*pt);
    }*/
  }
}