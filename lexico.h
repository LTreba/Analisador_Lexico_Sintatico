/*
Grupo:
 - Lucas Trebacchetti Eiras - 10401973
 - Gustavao Matta - 10410154
*/

#ifndef LEXICO_H
#define LEXICO_H


typedef enum{
    ERRO,
    ID,
    COMENTARIO,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVES,
    FECHA_CHAVES,
    PONTO_VIRGULA,
    ATRIBUICAO,
    DIFERENTE,
    VIRGULA,
    IGUAL,
    MAIOR,
    MAIOR_IGUAL,
    MENOR,
    MENOR_IGUAL,
    INTCONST,
    CHARCONST,
    SOMA,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,
    OR,
    AND,
    EOS,
    CHAR,
    ELSE,
    IF,
    INT,
    MAIN,
    READINT,
    VOID,
    WHILE,
    WRITEINT
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_num;
    char atributo_id[16];
    char atributo_char;
}TInfoAtomo;

void printa_log(TInfoAtomo info_atm);
int procura_reservada(char reservadas[][9], char str_id[]);

TInfoAtomo obter_atomo();
TInfoAtomo reconhece_comentario_divisao();
TInfoAtomo reconhece_igual();
TInfoAtomo reconhece_num();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_diferente();
TInfoAtomo reconhece_maior();
TInfoAtomo reconhece_and();
TInfoAtomo reconhece_or();
TInfoAtomo reconhece_charconst();


extern char *strAtomo[];
extern int contaLinha;
extern char *entrada;


#endif