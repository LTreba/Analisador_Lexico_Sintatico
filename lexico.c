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

//Dicionario para o str_id
char *strAtomo[]={"ERRO","id","comentario","abre_par","fechar_par","abre_chaves","fecha_chaves","ponto_virgula","atribuicao"
                 ,"diferente","virgula","igual","maior","maior_igual","menor","menor_igual","intconst","charconst"
                 ,"soma","subtracao","multiplicacao","divisao","or","and","eos","char","else","if","int","main","readint"
                 ,"void","while","writeint"};
int contaLinha = 1;
char *entrada;

//Função chamada pelo sintatico
TInfoAtomo obter_atomo(){
    TInfoAtomo info_atomo;

    info_atomo.atomo = ERRO;

    while(*entrada == ' '|| 
          *entrada == '\n'||
          *entrada == '\r'||
          *entrada == '\t'){
        if(*entrada == '\n')
            contaLinha++;
        entrada++;
    }
switch (*entrada) {
    case 39:
        info_atomo = reconhece_charconst();
        break;
    case '(': 
        info_atomo.atomo = ABRE_PAR;
        entrada++;
        break;
    case ')': 
        info_atomo.atomo = FECHA_PAR;
        entrada++;
        break;
    case '{': 
        info_atomo.atomo = ABRE_CHAVES;
        entrada++;
        break;
    case '}': 
        info_atomo.atomo = FECHA_CHAVES;
        entrada++;
        break;
    case '/': 
        info_atomo = reconhece_comentario_divisao();
        break;
    case ';': 
        info_atomo.atomo = PONTO_VIRGULA;
        entrada++;
        break;
    case '=': 
        info_atomo = reconhece_igual();
        break;
    case '\0': 
        info_atomo.atomo = EOS;
        entrada++;
        break;
    case '!': 
        info_atomo = reconhece_diferente();
        break;
    case ',': 
        info_atomo.atomo = VIRGULA;
        entrada++;
        break;
    case '>':
        info_atomo = reconhece_maior();
        break;
    case '+':
        info_atomo.atomo = SOMA;
        entrada++;
        break;
    case '-':
        info_atomo.atomo = SUBTRACAO;
        entrada++;
        break;
    case '*':
        info_atomo.atomo = MULTIPLICACAO;
        entrada++;
        break;
    case '&':
        info_atomo = reconhece_and();
        break;
    case '0':
        info_atomo = reconhece_num();
    default:
        //ID ou palavras reservadas
        if (isalpha(*entrada) || *entrada=='_') {
            info_atomo = reconhece_id();
        }
        break;
    }
    info_atomo.linha = contaLinha;
    printa_log(info_atomo);
    return info_atomo;
}
//Printar o log da analise lexica
void printa_log(TInfoAtomo info_atm){

    if(info_atm.atomo == ERRO){
        if(info_atm.atomo == ERRO){
            printf("Erro na analise lexica");
            exit(1);
        }
    }

    printf("#   %d:%s | ", info_atm.linha,strAtomo[info_atm.atomo]);

    switch(info_atm.atomo){
        case ID:
            printf("%s", info_atm.atributo_id);
            break;
        case INTCONST:
            printf("%.0f", info_atm.atributo_num);
            break;
        case CHARCONST:
            printf("%c", info_atm.atributo_char);
            break;
        default:
            break;
    }
        
    printf("\n");

}

//OR -> ||

TInfoAtomo reconhece_or(){
    TInfoAtomo info_or;
    info_or.atomo = ERRO;
    if(*entrada=='|'){
        entrada++;
        goto q1;
    }
    return(info_or);
q1:
    if(*entrada=='|'){
        info_or.atomo = OR;
        entrada++;
    }
    return(info_or);
}

//AND -> &&

TInfoAtomo reconhece_and(){
    TInfoAtomo info_and;
    info_and.atomo = ERRO;
    if(*entrada=='&'){
        entrada++;
        goto q1;
    }
    return(info_and);
q1:
    if(*entrada=='&'){
        info_and.atomo = AND;
        entrada++;
    }
    return(info_and);
}

//MENOR -> < ou <=

TInfoAtomo reconhece_menor(){
    TInfoAtomo info_menor;
    info_menor.atomo = ERRO;
    if(*entrada=='<'){
        info_menor.atomo = MENOR;
        entrada++;
        goto q1;
    }
    return(info_menor);
q1:
    if(*entrada=='='){
        info_menor.atomo = MENOR_IGUAL;
        entrada++;
    }
    return(info_menor);
}

//MAIOR -> > ou >=

TInfoAtomo reconhece_maior(){
    TInfoAtomo info_maior;
    info_maior.atomo = ERRO;
    if(*entrada=='>'){
        info_maior.atomo = MAIOR;
        entrada++;
        goto q1;
    }
    return(info_maior);
q1:
    if(*entrada=='='){
        info_maior.atomo = MAIOR_IGUAL;
        entrada++;
    }
    return(info_maior);
}

//DIFERENTE -> !=

TInfoAtomo reconhece_diferente(){
    TInfoAtomo info_diferente;
    info_diferente.atomo = ERRO;
    if(*entrada=='!'){
        entrada++;
        goto q1;
    }
    return(info_diferente);
q1:
    if(*entrada=='='){
        info_diferente.atomo = DIFERENTE;
        entrada++;
    }
    return(info_diferente);
}

//= ou ==
TInfoAtomo reconhece_igual(){
    TInfoAtomo info_igual;
    info_igual.atomo = ERRO;
    if(*entrada == '='){
        info_igual.atomo = ATRIBUICAO;
        entrada++;
        goto q1;
    }
    return(info_igual);
q1:
    if(*entrada=='='){
        info_igual.atomo = IGUAL;
        entrada++;
    }
    return(info_igual);
}

//COMENTARIOS // E */

TInfoAtomo reconhece_comentario_divisao(){
    TInfoAtomo info_com;
    info_com.atomo = ERRO;

    if(*entrada == '/'){
        info_com.atomo = DIVISAO;
        entrada++;
        goto q1;
    }
    return info_com;
q1:
    if(*entrada=='*'){
        entrada++;
        goto q2;
    }
    if(*entrada=='/'){
        entrada++;
        goto q4;
    }
    return(info_com);
q2:
    info_com.atomo = ERRO;
    if(*entrada!='*'){
        if(*entrada=='\n'){
            contaLinha++;
        }
        entrada++;
        goto q2;
    }else if(*entrada!='\0'){
        entrada++;
        goto q3;
    }
    return(info_com);
q3:
    if(*entrada=='/'){
        entrada++;
        goto q5;
    }else{
        if(*entrada=='\0'){
            return(info_com);
        }
        if(*entrada=='\n'){
            contaLinha++;
        }
        entrada++;
        goto q2;
    }
q4:
    info_com.atomo = ERRO;
    if(*entrada=='\n'){
        contaLinha++;
        entrada++;
        goto q5;
    }else if(*entrada!='\0'){
        entrada++;
        goto q4;
    }
    return(info_com);
q5:
    info_com.atomo = COMENTARIO;
    return(info_com);
}

// NUMERO -> 0x(hexa|digito)+

TInfoAtomo reconhece_num(){
    TInfoAtomo info_num;
    char str_num[10];
    char *ini_num;

    info_num.atomo = ERRO;

    ini_num = entrada;
//q0:
    if(*entrada == '0'){
        entrada++;
        goto q1;
    }
    return info_num;

q1:
    if(*entrada == 'x'){
        entrada++;
        goto q2;
    }
    return info_num;
q2:
    if(isdigit(*entrada) || (*entrada>=65 && *entrada<=70)){
        entrada++;
        goto q3;
    }
    return info_num;
q3:
    if(isdigit(*entrada) || (*entrada>=65 && *entrada<=70)){
        entrada++;
        goto q3;
    }
    info_num.atomo = INTCONST;
    strncpy(str_num,ini_num,entrada - ini_num);
    str_num[entrada - ini_num]='\0';
    long n = strtol(str_num, NULL, 16);
    info_num.atributo_num = (float)n;
    return info_num;
}

// IDENTIFICADOR -> LETRA_MINUSCULA(LETRA_MINUSCULA|DIGITO)*

TInfoAtomo reconhece_id(){
    TInfoAtomo info_id;
    info_id.atomo = ERRO;

    char str_id[16];
    char *ini_id;

    ini_id = entrada;

    char reservadas[][9] = {"char","else","if","int","main","readint","void","while","writeint"};

    if(isalpha(*entrada) || *entrada=='_'){
        entrada ++;
        goto q1;
    }
    return info_id;
q1:
    if(isalpha(*entrada) || *entrada=='_' || isdigit(*entrada)){
        entrada ++;
        goto q1;
    }
    //Verificacoes do conteudo de id
    strncpy(str_id,ini_id,entrada - ini_id);
    str_id[entrada - ini_id]='\0';
    if(strlen(str_id)>15){
        return(info_id);
    }
    strcpy(info_id.atributo_id,str_id);
    //Procurando possiveis palavras reservadas em ID
    int index = procura_reservada(reservadas,info_id.atributo_id);
    if(index!=-1){
        info_id.atomo = index+25;
        return(info_id);
    }
    info_id.atomo = ID;
    return info_id;
}

//charconst = 'qualquer'

TInfoAtomo reconhece_charconst(){
    //Identifica somente um char
    TInfoAtomo info_charconst;
    info_charconst.atomo = ERRO;

    char temp;

    if(*entrada==39){
        entrada++;
        goto q1;
    }
    return(info_charconst);
q1:
    if(*entrada=='\0'|| *entrada=='\n'){
        return(info_charconst);
    }
    temp = *entrada;
    entrada++;
    goto q2;
q2:
    if(*entrada==39){
        entrada++;
        info_charconst.atomo = CHARCONST;
        info_charconst.atributo_char = temp;
        return(info_charconst);
    }
    return(info_charconst);
}

int procura_reservada(char reservadas[][9], char str_id[]){
    //Itera sob vetor de palavras reservadas fazendo comparacoes
    for(int i=0;i<9;i++){
        if(strcmp(reservadas[i],str_id)==0){
            return(i);
        }
    }
    return(-1);
}