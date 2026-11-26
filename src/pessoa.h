#ifndef PESSOA_H
#define PESSOA_H

#define MAX_STRING 100
#define MAX_DATE 11 // Formato "dd/mm/yyyy\0"

// Forward declaration (declaração antecipada) da struct no_pet
// Evita dependência circular de inclusão entre pessoa.h e pet.h
struct no_pet;

// -------------------------------------------------------------
// Estrutura de Dados da Pessoa
// -------------------------------------------------------------

typedef struct pessoa {
    int codigo;                     // (*) Obrigatório e Único
    char nome[MAX_STRING];           // (*) Obrigatório
    char fone[MAX_STRING];           // Opcional
    char data_nascimento[MAX_DATE];  // (*) Obrigatório (dd/mm/yyyy)
    char endereco[MAX_STRING];       // Opcional
} Pessoa;

// -------------------------------------------------------------
// Nó da Lista Duplamente Encadeada de Pessoas
// -------------------------------------------------------------

typedef struct no_pessoa {
    Pessoa info;
    struct no_pessoa *ant;
    struct no_pessoa *prox;
} NoPessoa;

// -------------------------------------------------------------
// Protótipos das Funções da Lista Duplamente Encadeada
// -------------------------------------------------------------

NoPessoa* criar_lista_pessoa(void);

int inserir_pessoa(NoPessoa **head, Pessoa p);

NoPessoa* buscar_pessoa_por_codigo(NoPessoa *head, int codigo);

int atualizar_pessoa(NoPessoa *head, Pessoa p);

int remover_pessoa(NoPessoa **head, int codigo, struct no_pet *head_pet);

void exibir_pessoas(NoPessoa *head);

void liberar_lista_pessoa(NoPessoa **head);

// -------------------------------------------------------------
// Protótipos das Funções de Persistência em Arquivo
// -------------------------------------------------------------

int carregar_pessoas_arquivo(NoPessoa **head, const char *filepath);

int salvar_pessoas_arquivo(NoPessoa *head, const char *filepath);

#endif