#ifndef COMANDO_H
#define COMANDO_H

#define MAX_COMANDO 256

// -------------------------------------------------------------
// Estruturas de Dados: Comando e Fila
// -------------------------------------------------------------

typedef struct comando {
    char descricao[MAX_COMANDO];
} Comando;

typedef struct no_comando {
    Comando info;
    struct no_comando *prox;
} NoComando;

typedef struct fila_comandos {
    NoComando *inicio;
    NoComando *fim;
} FilaComandos;

// -------------------------------------------------------------
// Protótipos das Funções de Fila e Validação
// -------------------------------------------------------------

FilaComandos* criar_fila(void);

int fila_vazia(FilaComandos *f);

void enfileirar(FilaComandos *f, const char *texto_comando);

int desenfileirar(FilaComandos *f, char *buffer_destino);

void liberar_fila(FilaComandos **f);

int validar_comando(const char *comando);

#endif