#ifndef _H_IKS
#define _H_IKS

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	string tagval(); string dump();
};

struct Const: Sym { Const(string); };
struct Var: Sym { Var(string); };
struct Combinator: Sym { Combinator(string); };

struct App: Sym { App(Sym*,Sym*); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_IKS
