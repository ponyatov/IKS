#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::tagval() { return "<"+tag+":"+val+">"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }
void Sym::track() { cout << dump() << "\n------------------------"; }

Sym* Sym::eval() { track(); return this; }

Const::Const(string V):Sym("c",V) {}
Var::Var(string V):Sym("v",V) {}
Combinator::Combinator(string V):Sym(V,"") {}

_I::_I(string V):Combinator(V) {}
Sym* _I::eval() { track(); assert(nest.size()==1); return nest[0]; }

_K::_K(string V):Combinator(V) {}
Sym* _K::eval() { track(); assert(nest.size()==2); return nest[0]; }

_S::_S(string V):Combinator(V) {}
Sym* _S::eval() { track(); assert(nest.size()==3);
	return new App(
		new App(nest[0],nest[2]),
		new App(nest[1],nest[2])
			); }

App::App(Sym*A,Sym*B):Sym("@","@") { push(A); push(B); }
Sym* App::eval() { Sym::eval(); }

LR::LR(Sym*A):Sym("(",")") { push(A); }
Sym* LR::eval() { track(); assert(nest.size()==1); return nest[0]; }

