```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pet.h"
#include "pessoa.h"

// =============================================================
// SEÇÃO 1: MÓDULO TIPO_PET
// =============================================================

// -------------------------------------------------------------
// Inicialização e Busca
// -------------------------------------------------------------

NoTipoPet* criar_lista_tipo_pet(void) {
    return NULL;
}

NoTipoPet* buscar_tipo_pet_por_codigo(NoTipoPet *head, int codigo) {
    NoTipoPet *atual = head;

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

int inserir_tipo_pet(NoTipoPet **head, TipoPet tp) {
    if (head == NULL) {
        return 0;
    }

    // Regra de Negócio: Código único
    if (buscar_tipo_pet_por_codigo(*head, tp.codigo) != NULL) {
        printf("Erro: Ja existe um Tipo de Pet cadastrado com o codigo %d.\n", tp.codigo);
        return 0;
    }

    NoTipoPet *novo = (NoTipoPet*) malloc(sizeof(NoTipoPet));

    if (novo == NULL) {
        printf("Erro: Falha de alocacao de memoria para TipoPet.\n");
        return 0;
    }

    novo->info = tp;
    novo->prox = NULL;
    novo->ant = NULL;

    if (*head == NULL) {
        *head = novo;
    } else {
        NoTipoPet *atual = *head;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
        novo->ant = atual;
    }

    return 1;
}

int atualizar_tipo_pet(NoTipoPet *head, TipoPet tp) {
    NoTipoPet *no = buscar_tipo_pet_por_codigo(head, tp.codigo);

    if (no == NULL) {
        printf("Erro: TipoPet com codigo %d nao encontrado.\n", tp.codigo);
        return 0;
    }

    if (strlen(tp.descricao) > 0) {
        strcpy(no->info.descricao, tp.descricao);
    }

    return 1;
}

// -------------------------------------------------------------
// Integridade Referencial
// -------------------------------------------------------------

// Verifica se existe algum pet vinculado a esse tipo antes de remover
int possui_pets_com_tipo(NoPet *head_pet, int codigo_tipo_pet) {
    NoPet *atual = head_pet;

    while (atual != NULL) {
        if (atual->info.codigo_tipo_pet == codigo_tipo_pet) {
            return 1; // Encontrou pet associado
        }

        atual = atual->prox;
    }

    return 0; // Nenhum pet associado
}

int remover_tipo_pet(NoTipoPet **head, int codigo, NoPet *head_pet) {
    if (head == NULL || *head == NULL) {
        return 0;
    }

    NoTipoPet *no = buscar_tipo_pet_por_codigo(*head, codigo);

    if (no == NULL) {
        printf("Erro: TipoPet com codigo %d nao encontrado.\n", codigo);
        return 0;
    }

    // Regra de Integridade: Impedir remocao se houver pets desse tipo
    if (possui_pets_com_tipo(head_pet, codigo)) {
        printf("Erro de Integridade: Nao e possivel remover o TipoPet (%d) pois existem pet(s) cadastrados com este tipo.\n", codigo);
        return 0;
    }

    if (no->ant != NULL) {
        no->ant->prox = no->prox;
    } else {
        *head = no->prox;
    }

    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }

    free(no);

    return 1;
}

// -------------------------------------------------------------
// Exibição e Liberação de Memória
// -------------------------------------------------------------

void exibir_tipos_pet(NoTipoPet *head) {
    NoTipoPet *atual = head;

    printf("\n--- LISTA DE TIPOS DE PET ---\n");

    if (atual == NULL) {
        printf("Nenhum tipo de pet cadastrado.\n");
        return;
    }

    while (atual != NULL) {
        printf("Codigo: %d | Descricao: %s\n",
               atual->info.codigo,
               atual->info.descricao);

        atual = atual->prox;
    }

    printf("-----------------------------\n\n");
}

void liberar_lista_tipo_pet(NoTipoPet **head) {
    if (head == NULL) {
        return;
    }

    NoTipoPet *atual = *head;

    while (atual != NULL) {
        NoTipoPet *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *head = NULL;
}

// -------------------------------------------------------------
// Persistência em Arquivo
// -------------------------------------------------------------

int carregar_tipos_pet_arquivo(NoTipoPet **head, const char *filepath) {
    FILE *arq = fopen(filepath, "r");

    if (arq == NULL) {
        arq = fopen(filepath, "w");

        if (arq != NULL) {
            fclose(arq);
        }

        return 1;
    }

    TipoPet tp;
    char linha;

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%99[^\n]", &tp.codigo, tp.descricao) == 2) {
            inserir_tipo_pet(head, tp);
        }
    }

    fclose(arq);

    return 1;
}

int salvar_tipos_pet_arquivo(NoTipoPet *head, const char *filepath) {
    FILE *arq = fopen(filepath, "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s para escrita.\n", filepath);
        return 0;
    }

    NoTipoPet *atual = head;

    while (atual != NULL) {
        fprintf(arq, "%d;%s\n",
                atual->info.codigo,
                atual->info.descricao);

        atual = atual->prox;
    }

    fclose(arq);

    return 1;
}

// =============================================================
// SEÇÃO 2: MÓDULO PET
// =============================================================

// -------------------------------------------------------------
// Inicialização e Busca
// -------------------------------------------------------------

NoPet* criar_lista_pet(void) {
    return NULL;
}

NoPet* buscar_pet_por_codigo(NoPet *head, int codigo) {
    NoPet *atual = head;

    while (atual != NULL) {
        if (atual->info.codigo == codigo) {
            return atual;
        }

        atual = atual->prox;
    }

    return NULL;
}

// -------------------------------------------------------------
// Integridade Referencial
// -------------------------------------------------------------

// Utilizada no arquivo pessoa.c para evitar remocao de dona/dono com pets
int possui_pets_associados(NoPet *head_pet, int codigo_pes) {
    NoPet *atual = head_pet;

    while (atual != NULL) {
        if (atual->info.codigo_pes == codigo_pes) {
            return 1; // Encontrou pet pertencente a essa pessoa
        }

        atual = atual->prox;
    }

    return 0; // Nenhum pet encontrado para essa pessoa
}

// -------------------------------------------------------------
// Operações da Lista Duplamente Encadeada
// -------------------------------------------------------------

int inserir_pet(NoPet **head_pet, Pet p, NoPessoa *head_pessoa, NoTipoPet *head_tipo) {
    if (head_pet == NULL) {
        return 0;
    }

    // Regra de Negocio 1: Codigo de Pet unico
    if (buscar_pet_por_codigo(*head_pet, p.codigo) != NULL) {
        printf("Erro: Ja existe um Pet cadastrado com o codigo %d.\n", p.codigo);
        return 0;
    }

    // Regra de Negocio 2 (Chave Estrangeira): Valida se a pessoa dona existe
    if (buscar_pessoa_por_codigo(head_pessoa, p.codigo_pes) == NULL) {
        printf("Erro de Integridade: Pessoa com codigo %d nao existe.\n", p.codigo_pes);
        return 0;
    }

    // Regra de Negocio 3 (Chave Estrangeira): Valida se o TipoPet existe
    if (buscar_tipo_pet_por_codigo(head_tipo, p.codigo_tipo_pet) == NULL) {
        printf("Erro de Integridade: TipoPet com codigo %d nao existe.\n", p.codigo_tipo_pet);
        return 0;
    }

    NoPet *novo = (NoPet*) malloc(sizeof(NoPet));

    if (novo == NULL) {
        printf("Erro: Falha de alocacao de memoria para Pet.\n");
        return 0;
    }

    novo->info = p;
    novo->prox = NULL;
    novo->ant = NULL;

    if (*head_pet == NULL) {
        *head_pet = novo;
    } else {
        NoPet *atual = *head_pet;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
        novo->ant = atual;
    }

    return 1;
}

int atualizar_pet(NoPet *head_pet, Pet p, NoPessoa *head_pessoa, NoTipoPet *head_tipo) {
    NoPet *no = buscar_pet_por_codigo(head_pet, p.codigo);

    if (no == NULL) {
        printf("Erro: Pet com codigo %d nao encontrado.\n", p.codigo);
        return 0;
    }

    // Se alterou o dono, valida a nova chave estrangeira
    if (p.codigo_pes > 0 && p.codigo_pes != no->info.codigo_pes) {
        if (buscar_pessoa_por_codigo(head_pessoa, p.codigo_pes) == NULL) {
            printf("Erro de Integridade: Pessoa com codigo %d nao existe.\n", p.codigo_pes);
            return 0;
        }

        no->info.codigo_pes = p.codigo_pes;
    }

    // Se alterou o tipo de pet, valida a nova chave estrangeira
    if (p.codigo_tipo_pet > 0 && p.codigo_tipo_pet != no->info.codigo_tipo_pet) {
        if (buscar_tipo_pet_por_codigo(head_tipo, p.codigo_tipo_pet) == NULL) {
            printf("Erro de Integridade: TipoPet com codigo %d nao existe.\n", p.codigo_tipo_pet);
            return 0;
        }

        no->info.codigo_tipo_pet = p.codigo_tipo_pet;
    }

    if (strlen(p.nome) > 0) {
        strcpy(no->info.nome, p.nome);
    }

    return 1;
}

int remover_pet(NoPet **head, int codigo) {
    if (head == NULL || *head == NULL) {
        return 0;
    }

    NoPet *no = buscar_pet_por_codigo(*head, codigo);

    if (no == NULL) {
        printf("Erro: Pet com codigo %d nao encontrado.\n", codigo);
        return 0;
    }

    if (no->ant != NULL) {
        no->ant->prox = no->prox;
    } else {
        *head = no->prox;
    }

    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }

    free(no);

    return 1;
}

// -------------------------------------------------------------
// Exibição e Liberação de Memória
// -------------------------------------------------------------

void exibir_pets(NoPet *head) {
    NoPet *atual = head;

    printf("\n--- LISTA DE PETS ---\n");

    if (atual == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    while (atual != NULL) {
        printf("Codigo: %d | Codigo Dono: %d | Nome: %s | Codigo Tipo: %d\n",
               atual->info.codigo,
               atual->info.codigo_pes,
               atual->info.nome,
               atual->info.codigo_tipo_pet);

        atual = atual->prox;
    }

    printf("---------------------\n\n");
}

void liberar_lista_pet(NoPet **head) {
    if (head == NULL) {
        return;
    }

    NoPet *atual = *head;

    while (atual != NULL) {
        NoPet *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *head = NULL;
}

// -------------------------------------------------------------
// Persistência em Arquivo
// -------------------------------------------------------------

int carregar_pets_arquivo(NoPet **head, const char *filepath) {
    FILE *arq = fopen(filepath, "r");

    if (arq == NULL) {
        arq = fopen(filepath, "w");

        if (arq != NULL) {
            fclose(arq);
        }

        return 1;
    }

    Pet p;
    char linha;

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%d;%99[^;];%d",
                   &p.codigo,
                   &p.codigo_pes,
                   p.nome,
                   &p.codigo_tipo_pet) == 4) {

            // Insere diretamente sem re-validar chaves durante o carregamento de arquivo
            NoPet *novo = (NoPet*) malloc(sizeof(NoPet));

            if (novo != NULL) {
                novo->info = p;
                novo->prox = NULL;
                novo->ant = NULL;

                if (*head == NULL) {
                    *head = novo;
                } else {
                    NoPet *atual = *head;

                    while (atual->prox != NULL) {
                        atual = atual->prox;
                    }

                    atual->prox = novo;
                    novo->ant = atual;
                }
            }
        }
    }

    fclose(arq);

    return 1;
}

int salvar_pets_arquivo(NoPet *head, const char *filepath) {
    FILE *arq = fopen(filepath, "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s para escrita.\n", filepath);
        return 0;
    }

    NoPet *atual = head;

    while (atual != NULL) {
        fprintf(arq, "%d;%d;%s;%d\n",
                atual->info.codigo,
                atual->info.codigo_pes,
                atual->info.nome,
                atual->info.codigo_tipo_pet);

        atual = atual->prox;
    }

    fclose(arq);

    return 1;
}
```