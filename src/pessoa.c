#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pessoa.h"
#include "pet.h" // Para checar a integridade referencial com possui_pets_associados()

// -------------------------------------------------------------
// Inicialização e Busca
// -------------------------------------------------------------

NoPessoa* criar_lista_pessoa(void) {
    return NULL;
}

NoPessoa* buscar_pessoa_por_codigo(NoPessoa *head, int codigo) {
    NoPessoa *atual = head;

    while (atual != NULL) {
        if (atual->info.codigo == codigo) {
            return atual;
        }

        atual = atual->prox;
    }

    return NULL;
}

// -------------------------------------------------------------
// Operações da Lista Duplamente Encadeada
// -------------------------------------------------------------

// Insere uma nova pessoa no final da lista garantindo a unicidade do código
int inserir_pessoa(NoPessoa **head, Pessoa p) {
    if (head == NULL) {
        return 0;
    }

    // Regra de Negócio: O código de pessoa não pode se repetir
    if (buscar_pessoa_por_codigo(*head, p.codigo) != NULL) {
        printf("Erro: Ja existe uma pessoa cadastrada com o codigo %d.\n", p.codigo);
        return 0;
    }

    NoPessoa *novo = (NoPessoa*) malloc(sizeof(NoPessoa));

    if (novo == NULL) {
        printf("Erro: Falha de alocacao de memoria para Pessoa.\n");
        return 0;
    }

    novo->info = p;
    novo->prox = NULL;
    novo->ant = NULL;

    if (*head == NULL) {
        *head = novo;
    } else {
        NoPessoa *atual = *head;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
        novo->ant = atual;
    }

    return 1;
}

// Atualiza os dados de uma pessoa existente na lista
int atualizar_pessoa(NoPessoa *head, Pessoa p) {
    NoPessoa *no = buscar_pessoa_por_codigo(head, p.codigo);

    if (no == NULL) {
        printf("Erro: Pessoa com codigo %d nao encontrada.\n", p.codigo);
        return 0;
    }

    if (strlen(p.nome) > 0) {
        strcpy(no->info.nome, p.nome);
    }

    if (strlen(p.fone) > 0) {
        strcpy(no->info.fone, p.fone);
    }

    if (strlen(p.data_nascimento) > 0) {
        strcpy(no->info.data_nascimento, p.data_nascimento);
    }

    if (strlen(p.endereco) > 0) {
        strcpy(no->info.endereco, p.endereco);
    }

    return 1;
}

// Remove uma pessoa ajustando os ponteiros duplos e verificando vínculos
int remover_pessoa(NoPessoa **head, int codigo, NoPet *head_pet) {
    if (head == NULL || *head == NULL) {
        return 0;
    }

    NoPessoa *no = buscar_pessoa_por_codigo(*head, codigo);

    if (no == NULL) {
        printf("Erro: Pessoa com codigo %d nao encontrada.\n", codigo);
        return 0;
    }

    // Regra de Negócio: Impede remoção de dono que possui pets cadastrados
    if (possui_pets_associados(head_pet, codigo)) {
        printf("Erro de Integridade: Nao e possivel remover a pessoa (%d) pois ela possui pet(s) associado(s).\n", codigo);
        return 0;
    }

    if (no->ant != NULL) {
        no->ant->prox = no->prox;
    } else {
        *head = no->prox; // Atualiza a cabeça da lista se for o primeiro nó
    }

    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }

    free(no);

    return 1;
}

void exibir_pessoas(NoPessoa *head) {
    NoPessoa *atual = head;

    printf("\n--- LISTA DE PESSOAS ---\n");

    if (atual == NULL) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    while (atual != NULL) {
        printf("Codigo: %d | Nome: %s | Fone: %s | Nasc: %s | Endereco: %s\n",
               atual->info.codigo,
               atual->info.nome,
               atual->info.fone,
               atual->info.data_nascimento,
               atual->info.endereco);

        atual = atual->prox;
    }

    printf("------------------------\n\n");
}

void liberar_lista_pessoa(NoPessoa **head) {
    if (head == NULL) {
        return;
    }

    NoPessoa *atual = *head;

    while (atual != NULL) {
        NoPessoa *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *head = NULL;
}

// -------------------------------------------------------------
// Persistência em Arquivo (Carga Inicial e Sincronização)
// -------------------------------------------------------------

int carregar_pessoas_arquivo(NoPessoa **head, const char *filepath) {
    FILE *arq = fopen(filepath, "r");

    if (arq == NULL) {
        arq = fopen(filepath, "w"); // Cria o arquivo caso não exista na pasta data/

        if (arq != NULL) {
            fclose(arq);
        }

        return 1;
    }

    Pessoa p;
    char linha;

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        // Leitura formatada no padrão CSV (codigo;nome;fone;data_nascimento;endereco)
        if (sscanf(linha, "%d;%99[^;];%99[^;];%10[^;];%99[^\n]",
                   &p.codigo,
                   p.nome,
                   p.fone,
                   p.data_nascimento,
                   p.endereco) >= 4) {
            inserir_pessoa(head, p);
        }
    }

    fclose(arq);

    return 1;
}

int salvar_pessoas_arquivo(NoPessoa *head, const char *filepath) {
    FILE *arq = fopen(filepath, "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s para escrita.\n", filepath);
        return 0;
    }

    NoPessoa *atual = head;

    while (atual != NULL) {
        fprintf(arq, "%d;%s;%s;%s;%s\n",
                atual->info.codigo,
                atual->info.nome,
                atual->info.fone,
                atual->info.data_nascimento,
                atual->info.endereco);

        atual = atual->prox;
    }

    fclose(arq);

    return 1;
}