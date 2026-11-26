#ifndef PET_H
#define PET_H

#include "pessoa.h" // Necessário para referenciar NoPessoa nas validações de chave estrangeira

#define MAX_STRING 100

// -------------------------------------------------------------
// Estrutura de Dados e Nó: TipoPet
// -------------------------------------------------------------

typedef struct tipo_pet {
    int codigo;                  // (*) Obrigatório e Único
    char descricao[MAX_STRING];   // (*) Obrigatório (ex: "cachorro", "gato")
} TipoPet;

typedef struct no_tipo_pet {
    TipoPet info;
    struct no_tipo_pet *ant;
    struct no_tipo_pet *prox;
} NoTipoPet;

// -------------------------------------------------------------
// Estrutura de Dados e Nó: Pet
// -------------------------------------------------------------

typedef struct pet {
    int codigo;                  // (*) Obrigatório e Único
    int codigo_pes;              // (*) Obrigatório (Chave Estrangeira -> Pessoa)
    char nome[MAX_STRING];        // (*) Obrigatório
    int codigo_tipo_pet;          // (*) Obrigatório (Chave Estrangeira -> TipoPet)
} Pet;

typedef struct no_pet {
    Pet info;
    struct no_pet *ant;
    struct no_pet *prox;
} NoPet;

// -------------------------------------------------------------
// Protótipos para TipoPet
// -------------------------------------------------------------

NoTipoPet* criar_lista_tipo_pet(void);

int inserir_tipo_pet(NoTipoPet **head, TipoPet tp);

NoTipoPet* buscar_tipo_pet_por_codigo(NoTipoPet *head, int codigo);

int remover_tipo_pet(NoTipoPet **head, int codigo, NoPet *head_pet);

void liberar_lista_tipo_pet(NoTipoPet **head);

int carregar_tipos_pet_arquivo(NoTipoPet **head, const char *filepath);

int salvar_tipos_pet_arquivo(NoTipoPet *head, const char *filepath);

// -------------------------------------------------------------
// Protótipos para Pet (com Validação de Chaves Estrangeiras)
// -------------------------------------------------------------

NoPet* criar_lista_pet(void);

int inserir_pet(NoPet **head_pet, Pet p, NoPessoa *head_pessoa, NoTipoPet *head_tipo);

NoPet* buscar_pet_por_codigo(NoPet *head, int codigo);

int atualizar_pet(NoPet *head_pet, Pet p, NoPessoa *head_pessoa, NoTipoPet *head_tipo);

int remover_pet(NoPet **head, int codigo);

int possui_pets_associados(NoPet *head_pet, int codigo_pes);

void liberar_lista_pet(NoPet **head);

int carregar_pets_arquivo(NoPet **head, const char *filepath);

int salvar_pets_arquivo(NoPet *head, const char *filepath);

#endif