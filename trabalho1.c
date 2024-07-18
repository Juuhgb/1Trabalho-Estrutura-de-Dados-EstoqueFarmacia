#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp = fopen("entrada.txt", "r");
    FILE *saida = fopen("saida.txt", "w");

    Lista *lst = CriaLista();
    
    Medicamento *med = NULL;

    if(fp == NULL || saida == NULL){
        printf("Erro na abertura dos arquivos");
        return 1;
    }   

    char str[50];

    char nome[50];
    int codigo;
    float valor;
    int data[3];

    while(fscanf(fp, "%s", str) != EOF){
        if(strcmp(str, "MEDICAMENTO") == 0){
            fscanf(fp, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);
            med = CriaMedicamento(nome, codigo, valor, data);
            lst = InsereListaMedicamento(saida, lst, med);
        }
        else if(strcmp(str, "RETIRA") == 0){
            fscanf(fp, "%d", &codigo);
            lst = RetiraListaMedicamento(saida, lst, codigo);
        }
        else if(strcmp(str, "IMPRIME_LISTA") == 0){
            ImprimeListaMedicamentos(saida, lst);
        }
        else if(strcmp(str, "ATUALIZA_PRECO") == 0){
            fscanf(fp, "%d %f", &codigo, &valor);
            atualizaPreco(saida, lst, codigo, valor);
        }
        else if(strcmp(str, "VERIFICA_VALIDADE") == 0){
            fscanf(fp, "%d %d %d", &data[0], &data[1], &data[2]);
            VerificaListaValidade(saida, lst, data);
        }
        else if(strcmp(str, "ORDENA_LISTA_VALIDADE") == 0){
            lst = OrdenaListaVencimento(lst);
        }
        else if(strcmp(str, "VERIFICA_LISTA") == 0){
            fscanf(fp, "%d", &codigo);
            int verifica = VerificaListaMedicamento(saida, lst, codigo);
            if(verifica){
                fprintf(saida, "MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
            }
        }
        else if(strcmp(str, "ORDENA_LISTA_VALOR") == 0){
            lst = OrdenaListaValor(lst);
        }
        else if(strcmp(str, "IMPRIME_LISTA") == 0){
            ImprimeListaMedicamentos(saida, lst);
        }
        else if(strcmp(str, "FIM") == 0){
            liberarLista(lst);

        }
    }

    fclose(fp);
    fclose(saida);
    return 0;
}