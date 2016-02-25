#ifndef _H_IKS
#define _H_IKS
													// std.includes
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
using namespace std;
													// Abstract Symbolic Type
struct Sym {
	string tag,val;									// data class/type : value
	Sym(string,string);								// T:V constructor
	Sym(string);									// token constructor
	vector<Sym*> nest; void push(Sym*);				// nest[]ed elements
	string tagval(); 								// dump object in tree form
	string dump(int depth=0); string pad(int);
	virtual Sym* eval();							// evaluate/compute object
	void track();									// track print
};

struct Const: Sym { Const(string); };				// constant a..d
struct Var: Sym { Var(string); };					// variable x..z
struct Combinator: Sym { Combinator(string); };		// combinators:
													// (base)
struct _I: Combinator { _I(string); Sym*eval(); };	// Ix = x /identity/
struct _K: Combinator { _K(string); Sym*eval(); };	// Kxy = x /constant/
struct _S: Combinator { _S(string); Sym*eval(); };	// Sxyz = (xz)(yz) /fusion/
													// (extra)
struct _T: Combinator { _T(string); Sym*eval(); };	// Txyz = xzy /permutation/
struct _Z: Combinator { _Z(string); Sym*eval(); };	// Zxyz = x(yz) /group/

struct App: Sym { App(Sym*,Sym*); Sym*eval(); };	// xy apply operation
struct LR: Sym { LR(Sym*); Sym*eval(); };			// (x) brackets

													// lexer/parser interface
extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_IKS
