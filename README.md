# 🐾 MiniRegistro em C

**Processador de Comandos SQL-like com Filas, Listas e Árvores**

Projeto desenvolvido para a disciplina de **Estrutura de Dados**, do curso de Engenharia da Computação do Instituto Federal do Ceará (IFCE) – Campus Fortaleza.

Alunos responsáveis:
- Carlos Yan Matos Ferreira
- Guilherme Alves Fonseca

O sistema consiste em um minigerenciador de banco de dados desenvolvido em linguagem C para cadastro e controle de **Pessoas**, **Tipos de Pets** e **Pets**. O processamento é realizado por meio de scripts de comandos inspirados em SQL, utilizando uma arquitetura baseada em filas, listas duplamente encadeadas, tabelas hash e árvores binárias.

---

## 📌 Funcionalidades Principais

### Persistência de Dados
- Carga inicial dos arquivos de dados para **listas duplamente encadeadas** ao iniciar a aplicação.
- Salvamento automático dos dados ao encerrar a aplicação.

### Ingestão e Validação de Scripts
- Leitura de scripts SQL-like (`INSERT`, `UPDATE`, `DELETE` e `SELECT`) por meio de arquivos ou terminal.
- Filtragem de comandos sintaticamente e semanticamente válidos.

### Processamento Orientado a Filas

O processamento dos comandos ocorre em três etapas:

1. Inserção na **Fila Geral de Comandos**.
2. Validação e triagem para **Filas Específicas de Operação** (`Pessoa`, `Tipo_Pet` e `Pet`).
3. Execução ordenada das operações sobre as listas duplamente encadeadas.

### Integridade Referencial e Validações em O(1)

- **Unicidade de códigos:** cada registro deve possuir um código único.
- **Validação de chaves estrangeiras:** os códigos `codigo_pes` e `codigo_tipo_pet` devem corresponder a registros existentes.
- **Restrição de remoção:** não permite remover proprietários que possuam pets associados sem o devido tratamento.
- **Tabela Hash:** indexação dos códigos para consultas e verificações rápidas, com complexidade média O(1).

### Ordenação com Árvore Binária de Busca (BST)

- Consultas do tipo `SELECT ... ORDER BY nome` constroem uma árvore binária de busca (BST) a partir dos registros armazenados na lista.
- O percurso *in-order* da árvore permite exibir os resultados em ordem alfabética.

---

## 📁 Estrutura do Projeto

A aplicação está organizada de maneira modular, separando as declarações em arquivos de cabeçalho (`.h`) e suas respectivas implementações (`.c`).

```text
.
├── src/
│   ├── main.c              # Ponto de entrada, carga, fluxo principal e encerramento
│   ├── pessoa.h / .c      # Entidade Pessoa, lista duplamente encadeada e arquivos
│   ├── pet.h / .c         # Entidades Tipo_Pet e Pet, integridade e listas
│   ├── comando.h / .c     # Parser, validação de sintaxe e filas de operação
│   ├── arvore.h / .c      # Árvore Binária de Busca (BST) para exibição ordenada
│   └── hash.h / .c        # Tabela Hash para indexação rápida e validação de chaves
│
├── data/                   # Arquivos de dados persistidos (.txt ou .dat)
├── script.sql              # Exemplo de script de comandos SQL-like
├── Makefile                # Automação da compilação
├── .gitignore              # Arquivos ignorados pelo Git (*.o, binários, .vscode/)
└── README.md               # Documentação do projeto
```