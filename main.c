/*
Grupo:
 - Lucas Trebacchetti Eiras - 10401973
 - Gustavao Matta - 10410154
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintatico.h"


void le_arquivo(char *arquivo);
void comeca_analise(char *conteudo);

char *conteudo;  


int main(int argc, char **argv){
    if(argc < 2){
        printf("Numero de argumento invalido. Use %s <nome_arquivo>\n", argv[0]);
        return -1;
    }

    char *arquivo = argv[1];

    le_arquivo(arquivo);
    printf("Conteúdo lido:\n[%s]\n", conteudo);
    comeca_analise(conteudo);
    free(conteudo);
    return 0;
}



void le_arquivo(char *arquivo){
    FILE *ler=fopen(arquivo, "r");
    if(ler==NULL){
        perror("Erro abrindo o arquivo!");
        return;
    }

    size_t tamanho_total = 0;
    size_t capacidade = 1024;
    conteudo = (char *)malloc(capacidade*sizeof(char));
    if(conteudo==NULL){
        printf("Erro ao alocar a memória\n");
        fclose(ler);
        return;
    }

    char linha[256];
    while(fgets(linha, sizeof(linha), ler)){
        size_t len = strlen(linha);
        if(tamanho_total+len+1>capacidade){
            capacidade *= 2;
            conteudo = (char*)realloc(conteudo, capacidade * sizeof(char));
            if (conteudo == NULL) {
                printf("Erro ao realocar a memoria\n");
                fclose(ler);
                return;
            }
        }
        strcpy(conteudo + tamanho_total, linha);
        tamanho_total += len;
    }
    fclose(ler);
}


void comeca_analise(char *conteudo){
    entrada = conteudo;
    //iniciar lookahead com primeiro atomo
    lookahead = obter_atomo().atomo;
    //Chama simbolo inicial da gramatica e comeca todo o processo de analise sintatica e semantica
    program();
    printf("%d linhas analisadas, programa sintaticamente correto\n", contaLinha);
}