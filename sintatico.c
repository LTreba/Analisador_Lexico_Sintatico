/*
Grupo:
 - Lucas Trebacchetti Eiras - 10401973
 - Gustavao Matta - 10410154
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexico.h"

#include "sintatico.h"


void consome(TAtomo atomo){
    //Dicionario para erros
    char *dicionario[] = {"Erro","Identificador","Comentário","(",")","{","}",";","=","!=",",","==",">",">="
                        ,"<","<=","Número","String","+","-","*","/","||","&&","EOS","char","else","if","int"
                        ,"main","readint","void","while","writeint"};
    //Se for comentario, ignorar
    if(lookahead==COMENTARIO){
        lookahead = obter_atomo().atomo;
    }
    if(lookahead == atomo){
        lookahead = obter_atomo().atomo;
    }else{
        char *encontrado = NULL;
        char *esperado = NULL;
        for(int i=ERRO;i<=WRITEINT;i++){
            if(atomo==i){
                encontrado = dicionario[i];
            }
            if(lookahead==i){
                esperado = dicionario[i];
            }
        }
        printf("erro sintatico, esperado [%s] encontrado [%s]\n", encontrado, esperado);
        exit(1);
    }
}


void program(){
    consome(VOID);
    consome(MAIN);
    consome(ABRE_PAR);
    consome(VOID);
    consome(FECHA_PAR);
    compound_stmt();
}

void compound_stmt(){
    consome(ABRE_CHAVES);
    var_delc();
    while(lookahead == ID || lookahead == ABRE_CHAVES || lookahead == IF || lookahead == WHILE || lookahead == WRITEINT || lookahead == READINT){
        stmt();
    }
    consome(FECHA_CHAVES);
}

void var_delc(){
    if(lookahead == INT || lookahead == CHAR){
        type_specifier();
        var_decl_list();
        consome(PONTO_VIRGULA);
    }
}

void type_specifier(){
    if(lookahead==INT){
        consome(INT);
    }else{
        consome(CHAR);
    }
}

void var_decl_list(){
    variable_id();
    while(lookahead==VIRGULA){
        consome(VIRGULA);
        variable_id();
    }
}

void variable_id(){
    consome(ID);
    if(lookahead==ATRIBUICAO){
        consome(ATRIBUICAO);
        expr();
    }
}

void stmt(){
    switch(lookahead){
        case(ABRE_CHAVES):
            compound_stmt();
            break;
        case(ID):
            assig_stmt();
            break;
        case(IF):
            cond_stmt();
            break;
        case(WHILE):
            while_stmt();
            break;
        case(READINT):
            consome(READINT);
            consome(ABRE_PAR);
            consome(ID);
            consome(FECHA_PAR);
            consome(PONTO_VIRGULA);
            break;
        default:
            consome(WRITEINT);
            consome(ABRE_PAR);
            expr();
            consome(FECHA_PAR);
            consome(PONTO_VIRGULA);
            break;
    }
}

void assig_stmt(){
    consome(ID);
    consome(ATRIBUICAO);
    expr();
    consome(PONTO_VIRGULA);
}

void cond_stmt(){
    consome(IF);
    consome(ABRE_PAR);
    expr();
    consome(FECHA_PAR);
    stmt();
    if(lookahead==ELSE){
        consome(ELSE);
        stmt();
    }
}

void while_stmt(){
    consome(WHILE);
    consome(ABRE_PAR);
    expr();
    consome(FECHA_PAR);
    stmt();
}

void expr(){
    conjunction();
    while(lookahead==OR){
        consome(OR);
        conjunction();
    }
}

void conjunction(){
    comparison();
    while(lookahead==AND){
        consome(AND);
        comparison();
    }
}

void comparison(){
    sum();
    if(lookahead==MENOR || lookahead==MENOR_IGUAL || lookahead==IGUAL || lookahead==DIFERENTE || lookahead==MAIOR || lookahead==MAIOR_IGUAL){
        relation();
        sum();
    }
}

void relation(){
    switch (lookahead)
    {
    case MENOR:
        consome(MENOR);
        break;
    case MENOR_IGUAL:
        consome(MENOR_IGUAL);
        break;
    case IGUAL:
        consome(IGUAL);
        break;
    case DIFERENTE:
        consome(DIFERENTE);
        break;
    case MAIOR:
        consome(MAIOR);
        break;
    default:
        consome(MAIOR_IGUAL);
        break;
    }
}

void sum(){
    term();
    while(lookahead==SOMA || lookahead==CHAR){
        consome(lookahead);
        term();
    }
}

void term(){
    factor();
    while(lookahead==MULTIPLICACAO || lookahead==DIVISAO){
        consome(lookahead);
        factor();
    }
}

void factor(){
    switch (lookahead)
    {
    case INTCONST:
        consome(INTCONST);
        break;
    case CHARCONST:
        consome(CHARCONST);
        break;
    case ID:
        consome(ID);
        break;
    default:
        consome(ABRE_PAR);
        expr();
        consome(FECHA_PAR);
        break;
    }
}