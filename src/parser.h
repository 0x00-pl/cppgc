#pragma once
#include <string>
#include <vector>

using namespace std;

namespace pl{
  static const string token_type_str[]={
    "number",
    "operator",
    "space",
    "str",
    "symbol"
  };
  enum class token_type: int{
    number =0,
    op     =1,
    space  =2,
    str    =3,
    symbol =4,
  };
  class token{
  public:
    token_type type;
    string text;
    string filename;
    size_t ln;
    size_t ch;
  };
  
  bool _space(char c){
    return c==' ' or c=='\n' or c=='\r' or c=='\t';
  }
  bool _diget(char c){
    return (c>='0' and c<='9') or c=='.';
  }
  bool _op(char c){
    return c=='(' or c==')';
  }
  vector<token> tokenlize(vector<string> lines, string filename = "no-file"){
    vector<token> ret;
    size_t ln=0;
    for(string line : lines){
      ++ln;
      const char* p= line.c_str();
      for(size_t ch=0; *p; ++ch,++p){
	if(_space(*p)){
	  while(_space(p[1])){
	    ++p;
	  }
	}else if(*p=='"'){
	  ++p;
	  const char* beg=p;
	  while(p[0]!='"' and p[-1]!='\\')
	    ++p;
	  const char* end=p;
	  ret.push_back({token_type::str,string(beg,end),filename,ln,ch-(end-beg)});
	}else if(_diget(*p)){
	  const char* beg=p;
	  while(_diget(*p) or ((p[0]=='e' or p[0]=='E') and _diget(p[1])))
	    ++p;
	  const char* end=p;
	  ret.push_back({token_type::number,string(beg,end),filename,ln,ch-(end-beg)});
	  --p;
	}else if(_op(*p)){
	  ret.push_back({token_type::op,string(1,*p),filename,ln,ch});
	}else{
	  const char* beg=p;
	  while(_space(*p) or _op(*p)){
	    ++p;
	  }
	  const char* end=p;
	  ret.push_back({token_type::symbol,string(beg,end),filename,ln,ch-(end-beg)});
	  --p;
	}
      }
    }
    return move(ret);
  }
}