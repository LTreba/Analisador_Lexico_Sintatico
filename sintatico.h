/*
Grupo:
 - Lucas Trebacchetti Eiras - 10401973
 - Gustavao Matta - 10410154
*/

#ifndef SINTATICO_H
#define SINTATICO_H


void consome(TAtomo atomo);
void comeca_analise(char *entrada);

void program();
void compound_stmt();
void var_delc();
void stmt();
void type_specifier();
void var_decl_list();
void variable_id();
void expr();
void assig_stmt();
void cond_stmt();
void while_stmt();
void conjunction();
void comparison();
void relation();
void factor();
void sum();
void term();


TAtomo lookahead;


#endif