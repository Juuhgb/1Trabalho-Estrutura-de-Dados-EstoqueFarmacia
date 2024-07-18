#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct lista{
    Medicamento *m;
    Lista *prox;
};

/* Cria um novo medicamento */
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade){
    Medicamento *novo = (Medicamento*)malloc(sizeof(Medicamento));

    strcpy(novo->nome, nome);
    novo->codigo = codigo;
    novo->valor = valor;
    for(int i = 0; i < 3;i++){
        novo->data[i] = data_de_validade[i];
    }

    return novo;
}

Lista *CriaLista(){
    return NULL;
}

/* Insere um medicamento em uma lista */
Lista *InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *m){
    Lista *novo = (Lista*)malloc(sizeof(Lista));

    fprintf(fp, "MEDICAMENTO %s %d ADICIONADO\n", m->nome, m->codigo);
    if(novo == NULL){printf("Erro ao criar lista"); exit(1);}

    novo->m = m;
    novo->prox = l;
    return novo;
}

/* Retira um medicamento de uma determinada lista */
Lista *RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento){
    Lista *ant = NULL;
    Lista *p = l;

    while(p != NULL && p->m->codigo != id_medicamento){
        ant = p;
        p = p->prox;
    }
    if(p == NULL){
        fprintf(fp, "MEDICAMENTO RETIRA NAO ENCONTRADO\n");
        return l;
    }
    if(ant == NULL){
        l = p-> prox;
    }
    else{
        ant->prox = p->prox;
    }

    fprintf(fp, "MEDICAMENTO %s %d RETIRADO\n", p->m->nome, id_medicamento);

    free(p->m);
    free(p);

    return l;
}

/* Verifica se um medicamento esta presente em uma determinada lista */
int VerificaListaMedicamento(FILE *fp, Lista *l, int
id_medicamento){
    for(Lista *aux =l; aux != NULL; aux = aux->prox){
        if(aux->m->codigo == id_medicamento){
            fprintf(fp, "MEDICAMENTO ENCONTRADO %s %d %d %.1f %d %d %d", aux->m->nome, aux->m->codigo, aux->m->codigo, aux->m->valor, aux->m->data[0], aux->m->data[1], aux->m->data[2]);
            return 0;
        }
    }
    return 1;
}

/* Verifica se existe um medicamento vencido em uma determinada lista */
void VerificaListaValidade(FILE *fp, Lista *l, int *data){
    int validos = 1;
    for(Lista *aux = l; aux != NULL; aux = aux->prox){
        if(aux->m->data[2] < data[2]){
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", aux->m->nome, aux->m->codigo);
            validos = 0;
        }
        else if(aux->m->data[2] == data[2] && aux->m->data[1] < data[1]){
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", aux->m->nome, aux->m->codigo);
            validos = 0;
        }
        else if(aux->m->data[2] == data[2] && aux->m->data[1] == data[1] && aux->m->data[0] < data[0]){
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", aux->m->nome, aux->m->codigo);
            validos = 0;
        }
    }
    if(validos == 1){
        fprintf(fp, "MEDICAMENTO VENCIDO NAO ENCOTRADO NA LISTA\n");
    }
}

/* Imprime todos os medicamentos de uma lista */
void ImprimeListaMedicamentos(FILE *fp, Lista *p){
    for(Lista *aux = p; aux != NULL; aux = aux->prox){
        fprintf(fp, "%s %d %.1f %d %d %d\n", aux->m->nome, aux->m->codigo, aux->m->valor, aux->m->data[0], aux->m->data[1], aux->m->data[2]);
    }
}

/* Ordena Lista pelo valor do medicamento */
Lista *OrdenaListaValor(Lista *p){
    for(Lista *i = p; i != NULL; i = i->prox){
        for(Lista *j = p; j != NULL; j = j->prox){
            if(i->m->valor < j->m->valor){
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
            }
        }
    }
    return p;
}

/* Ordena Lista pela data de vencimento do medicamento */
Lista *OrdenaListaVencimento(Lista *p){
    for(Lista *i = p; i != NULL; i = i->prox){
        for(Lista *j = p; j != NULL; j = j -> prox){
            if(i->m->data[2] < j->m->data[2]){
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
        }   
            else if(i->m->data[2] == j->m->data[2] && i->m->data[1] < j->m->data[1]){
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
        }
            else if(i->m->data[2] == j->m->data[2] && i->m->data[1] == j->m->data[1] && i->m->data[0] < j->m->data[0]){
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
            }
        }
    }
    return p;
}

void liberarLista(Lista *lst){
    Lista *aux;
    Lista *p = lst;
    while(p != NULL){
        aux = p->prox;
        free(p->m);
        free(p);
        p = aux;
    }
}

void atualizaPreco(FILE *fp, Lista *l, int id, float preco){
    int encontrou = 1;
    for(Lista *aux = l; aux != NULL; aux = aux->prox){
        if(aux->m->codigo == id){
            aux->m->valor = preco;
            fprintf(fp, "PRECO ATUALIZADO %s %d %.1f\n", aux->m->nome, aux->m->codigo, aux->m->valor);
            encontrou = 0;
            break;
        }
    }
    if(encontrou){
        fprintf(fp, "MEDICAMENTO PARA ATUALIZAR PRECO NAO ENCONTRADO");
    }
}