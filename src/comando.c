#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "comando.h"

// Função auxiliar interna (não precisa estar no .h, pois só o comando.c usa)
static const char* pular_espacos(const char *str) {
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }
    return str;
}

FilaComandos* criar_fila(void) {
    FilaComandos *f = (FilaComandos*) malloc(sizeof(FilaComandos));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int fila_vazia(FilaComandos *f) {
    return (f == NULL || f->inicio == NULL);
}

void enfileirar(FilaComandos *f, const char *texto_comando) {
    if (f == NULL) return;

    NoComando *novo = (NoComando*) malloc(sizeof(NoComando));
    if (novo == NULL) {
        printf("Erro de alocação de memória para comando!\n");
        return;
    }
    
    strncpy(novo->info.descricao, texto_comando, MAX_COMANDO - 1);
    novo->info.descricao[MAX_COMANDO - 1] = '\0'; // Garante o fim da string
    novo->prox = NULL;
    
    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

int desenfileirar(FilaComandos *f, char *buffer_destino) {
    if (fila_vazia(f)) {
        return 0;
    }
    
    NoComando *aux = f->inicio;
    strcpy(buffer_destino, aux->info.descricao);
    
    f->inicio = aux->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(aux);
    return 1;
}

void liberar_fila(FilaComandos **f) {
    if (f == NULL || *f == NULL) return;
    
    char lixo[MAX_COMANDO];
    while (desenfileirar(*f, lixo)); // Esvazia todos os nós
    
    free(*f);
    *f = NULL;
}

int validar_comando(const char *comando) {
    if (comando == NULL) return 0;

    const char *cmd = pular_espacos(comando);
    
    if (strncasecmp(cmd, "insert into", 11) == 0) return 1;
    if (strncasecmp(cmd, "update", 6) == 0)       return 1;
    if (strncasecmp(cmd, "delete from", 11) == 0) return 1;
    if (strncasecmp(cmd, "select", 6) == 0)       return 1;
    
    return 0;
}