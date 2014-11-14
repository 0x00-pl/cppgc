#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "gc.h"
#include "types.h"

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
    return c=='(' or c==')' or c==':';
  }
  vector<token> tokenlize(vector<string> lines, string filename = "no-file"){
    vector<token> ret;
    size_t ln=0;
    for(string line : lines){
      ++ln;
      const char* p= line.c_str();
      for(const char* pbeg=p; *p; ++p){
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
	  ret.push_back({token_type::str,string(beg,end),filename,ln,size_t((p-pbeg)-(end-beg))});
	}else if(_diget(*p)){
	  const char* beg=p;
	  while(_diget(*p) or ((p[0]=='e' or p[0]=='E') and _diget(p[1])))
	    ++p;
	  const char* end=p;
	  ret.push_back({token_type::number,string(beg,end),filename,ln,size_t((p-pbeg)-(end-beg))});
	  --p;
	}else if(_op(*p)){
	  ret.push_back({token_type::op,string(1,*p),filename,ln,size_t((p-pbeg))});
	}else{
	  const char* beg=p;
	  while(!_space(*p) and !_op(*p)){
	    ++p;
	  }
	  const char* end=p;
	  ret.push_back({token_type::symbol,string(beg,end),filename,ln,size_t((p-pbeg)-(end-beg))});
	  --p;
	}
      }
    }
    return move(ret);
  }
  
  void default_syntex_token_error(token t, string msg){
    cout<<"syntex error at  ln: "<<t.ln<<" ,  ch: "<<t.ch<<endl;
    cout<<"    "<<t.text<<endl;
    cout<<"    "<<msg<<endl;
  }
  void default_syntex_error(string msg){
    cout<<"    "<<msg<<endl;
  }
  /**
   * exp :: number|str|symbol|(symbol:exp|exp *)
   */
  pl::pgc make_exp(vector<token>::iterator& tokens, vector<token>::iterator end){
    pgc ret= nullptr;
    while(tokens->type==token_type::space){
      ++tokens;
    }
    if(tokens!=end){
      switch(tokens->type){
	case token_type::number:
	  ret= manage(new ptp::number(atoi(tokens->text.c_str())));
	  ++tokens;
	  return ret;
	case token_type::op:
	  switch(tokens->text[0]){
	    case '(':{
	      ptp::exp* pexp= new ptp::exp();
	      ret= manage(pexp);
	      ++tokens;
	      while(true){
		pgc item= make_exp(tokens,end);
		if(item==nullptr){
		  return ret;
		}
		if(tokens->text[0]==':'){
		  ++tokens;
		  string name= *item;
		  item= make_exp(tokens,end);
		  pexp->push(name,item);
		}else{
		  pexp->push(item);
		}
	      }
	      return ret;
	    }
	    case ')':
	      ++tokens;
	      return nullptr;
	    case ':':
	      ++tokens;
	      default_syntex_token_error(*tokens,"wtf@");
	      return nullptr;
	  }
	  return ret;
	case token_type::str: 
	  ret= manage(new ptp::str(tokens->text));
	  ++tokens;
	  return ret;
	case token_type::symbol:
	  ret= manage(new ptp::symbol(tokens->text));
	  ++tokens;
	  return ret;
      }
    }
    return ret;
  }
}
