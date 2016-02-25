#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { return yyparse(); }
//glob_init(); yyparse(); 
//	cout<<module.eval()->dump()<<"\n\n"; return 0; }


Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::tagval() { return "<"+tag+":"+val+">"; }
string Sym::dump() { string S = tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++) S += (*it)->dump();
	return S; }

Combinator::Combinator(string V):Sym("",V) {}
Var::Var(string V):Sym("v",V) {}
Const::Const(string V):Sym("c",V) {}

App::App(Sym*A,Sym*B):Sym("@","") { push(A); push(B); }

