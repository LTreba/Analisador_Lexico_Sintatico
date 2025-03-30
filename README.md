# Analisador_Lexico_Sintatico
Analisador léxico e sintático para linguagem especificada feito em C

Instruções para execução:
Compilando:
gcc -Wall -Wno-unused-result -g -Og main.c lexico.c sintatico.c -o parser

Execução:
./parser codigo.txt


Gramática (Em BNF) aceita pelo analisador:

<program> ::= void main ‘(‘ void ‘)’ <compound_stmt>

<compound_stmt> ::= ‘{‘ <var_decl> { <stmt> } ‘}’

<var_decl> ::= [ <type_specifier> <var_decl_list> ‘;’ ]

<type_specifier> ::= int | char | readint |<type_decl_type>

<var_decl_list> ::= <variable_id> { ‘,’ <variable_id> }

<variable_id> ::= id [ ‘=’ <expr> ] | writeint |<type_decl_type>

<type_decl_type> ::= { void [intconst | charconst] id }

<stmt> ::= <compound_stmt> |
<assig_stmt> |
<cond_stmt> |
<while_stmt> |
readint ‘(‘ id ‘)’ ‘;’ |
writeint ‘(‘ <expr> ‘)’ ‘;’

<assig_stmt> ::= id ‘=’ <expr> ‘;’ | <type_decl_type>

<cond_stmt> ::= if ‘(‘ <expr> ‘)’ <stmt> [ else <stmt> ]

<while_stmt> ::= while ‘(‘ <expr> ‘)’ <stmt>

<expr> ::= <conjunction> { ‘||’ <conjunction> }

<conjunction> ::= <comparison> { ‘&&’ <comparison> }

<comparison> ::= <sum> [ <relation> <sum> ] | intconst

<relation> ::= “<” | “<=” | “==” | “!=” | “>” | “>=”

<sum> ::= <term> { (‘+’ | ‘-’) <term> }

<term> ::= <factor> { ( ‘*’ | ‘/’ ) <factor> }

<factor> ::= intconst | charconst | id | ‘(‘ <expr> ‘)’
