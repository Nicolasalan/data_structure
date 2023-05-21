#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    char* nome;
    char* departamento;
    char* cargo;
    char* tarefas;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    int size;
} DoublyLinkedList;

DoublyLinkedList* init_list() {
     DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));
     list->head = NULL;
     list->size = 0;
     return list;
}

Node* init_node(char* nome, char* departamento, char* cargo, char* tarefas) {
    Node* new_node = malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->nome = nome;
    new_node->departamento = departamento;
    new_node->cargo = cargo;
    new_node->tarefas = tarefas;
    return new_node;
}

// ========= INSERT =========
void insert(DoublyLinkedList* list, char* nome, char* departamento, char* cargo, char* tarefas) {
     Node* new_node = init_node(nome, departamento, cargo, tarefas);
     if (list->head == NULL) {
          list->head = new_node;
          list->size++;
          printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     Node* prev = NULL;

     while (current != NULL) {
          prev = current;
          current = current->next;
     }

     prev->next = new_node;
     new_node->prev = prev;
     list->size++;
     printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
}

// ========= INSERT FIRST =========
void insert_first(DoublyLinkedList* list, char* nome, char* departamento, char* cargo, char* tarefas) {
    Node* new_node = init_node(nome, departamento, cargo, tarefas);

    if (list->head == NULL) {
        list->head = new_node;
        list->size++;
        printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
        return;
    }

    new_node->next = list->head;
    list->head->prev = new_node;
    list->head = new_node;
    list->size++;

    printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
}

// ========= INSERT AT =========
void insert_at(DoublyLinkedList* list, char* nome, char* departamento, char* cargo, char* tarefas, int index) {
     if (index < 0 || index > list->size) {
          printf(COLOR_YELLOW "Índice fora dos limites, colaborator nao inserido\n" COLOR_RESET);
          return;
     }

     if (index == 0) {
          Node* new_node = init_node(nome, departamento, cargo, tarefas);
          new_node->next = list->head;

          if (list->head != NULL)
               list->head->prev = new_node;

          list->head = new_node;
          list->size++;
          printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     for (int i = 0; i < index - 1; i++) {
          if (current == NULL) {
               printf("Invalid index\n");
               return;
          }
          current = current->next;
     }

     Node* new_node = init_node(nome, departamento, cargo, tarefas);
     new_node->prev = current;
     new_node->next = current->next;

     if (current->next != NULL)
          current->next->prev = new_node;

     current->next = new_node;
     list->size++;
     printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
}

// ========= INSERT LAST =========
void insert_last(DoublyLinkedList* list, char* nome, char* departamento, char* cargo, char* tarefas) {
     Node* new_node = init_node(nome, departamento, cargo, tarefas);

     if (list->head == NULL) {
          list->head = new_node;
          list->size++;
          printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     while (current->next != NULL) {
          current = current->next;
     }

     current->next = new_node;
     new_node->prev = current;
     list->size++;

     printf(COLOR_GREEN "Colaborador adicionado com sucesso.\n" COLOR_RESET);
}

// ========= REMOVE =========
void remove_at(DoublyLinkedList* list, int index) {
     if (index < 0 || index >= list->size) {
          printf(COLOR_YELLOW "Índice fora dos limites\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     Node* prev = NULL;

     if (index == 0) {
          list->head = current->next;
          if (list->head != NULL)
               list->head->prev = NULL;
          char* removed_nome = current->nome;
          char* removed_departamento = current->departamento;
          char* removed_cargo = current->cargo;
          char* removed_tarefas = current->tarefas;
          free(current);
          list->size--;
          printf(COLOR_RED "Remover Colaborator: %s\n", removed_nome);
          printf("\n" COLOR_RESET);
          return;
     }

     for (int i = 0; i < index; i++) {
          prev = current;
          current = current->next;
     }

     prev->next = current->next;
     if (current->next != NULL)
          current->next->prev = prev;

     char* removed_nome = current->nome;
     char* removed_departamento = current->departamento;
     char* removed_cargo = current->cargo;
     char* removed_tarefas = current->tarefas;
     free(current);
     list->size--;

     printf(COLOR_RED "Removed collaborator: %s\n", removed_nome);
     printf("\n" COLOR_RESET);
}

// ========= REMOVE FIRST =========
void remove_first(DoublyLinkedList* list) {
     if (list->head == NULL) {
          printf(COLOR_YELLOW "Lista esta Vazia\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     list->head = current->next;
     if (list->head != NULL)
          list->head->prev = NULL;

     char* removed_nome = current->nome;
     char* removed_departamento = current->departamento;
     char* removed_cargo = current->cargo;
     char* removed_tarefas = current->tarefas;

     free(current);
     list->size--;

     printf(COLOR_RED "Remover Colaborator: %s\n", removed_nome);
     printf("\n" COLOR_RESET);
}

// ========= REMOVE LAST =========
void remove_last(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf(COLOR_YELLOW "Lista esta Vazia\n" COLOR_RESET);
        return;
    }

    Node* current = list->head;
    Node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev != NULL)
        prev->next = NULL;
    else
        list->head = NULL;

    char* removed_nome = current->nome;
    char* removed_departamento = current->departamento;
    char* removed_cargo = current->cargo;
    char* removed_tarefas = current->tarefas;

    free(current);
    list->size--;

    printf(COLOR_RED "Remover Colaborator: %s\n", removed_nome);
    printf("\n" COLOR_RESET);
}

// ========= PRINT FUNCTIONS =========
void print_list(DoublyLinkedList* list) {
     if (list->head == NULL) {
          printf(COLOR_YELLOW "Lista esta Vazia\n" COLOR_RESET);
          return;
     }

     Node* current = list->head;
     printf(COLOR_GREEN "Lista de colaboradores: \n" COLOR_RESET);
     printf("\n");
     while (current != NULL) {
          printf("Nome: %s\n", current->nome);
          printf("Departamento: %s\n", current->departamento);
          printf("Cargo: %s\n", current->cargo);
          printf("Tarefas: %s\n", current->tarefas);
          printf("\n===================\n");
          current = current->next;
     }
}

// ========= SEARCH =========
void search(DoublyLinkedList* list, const char* nome) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            printf("\n");
            printf(COLOR_GREEN "Nome encontrado na lista.\n" COLOR_RESET);
            printf("Nome: %s\n", current->nome);
            printf("Departamento: %s\n", current->departamento);
            printf("Cargo: %s\n", current->cargo);
            printf("Tarefas: %s\n", current->tarefas);
            return;
        }
        current = current->next;
    }
    printf("Nome não encontrado na lista.\n");
}

int main() {
     DoublyLinkedList list;
     list.head = NULL;
     list.size = 0;

     int choice;
     int index;
     char nome[100];
     char departamento[100];
     char cargo[100];
     char tarefas[100];

     while (1) {
          
          printf("\nMenu:\n");
          printf("1. Inserir um colaborador no início da lista\n");
          printf("2. Inserir um colaborador no final da lista\n");
          printf("3. Inserir um colaborador em uma posição específica da lista\n");
          printf("4. Remover um colaborador no início da lista\n");
          printf("5. Remover um colaborador no final da lista\n");
          printf("6. Remover um colaborador em uma posição específica da lista\n");
          printf("7. Buscar um colaborador pelo nome e mostrar todo registro\n");
          printf("8. Mostrar todos os registros\n");
          printf("0. Sair\n");
          printf("Escolha uma opção: ");
          scanf("%d", &choice);

          switch (choice) {
               case 0:
                    printf("\nEncerrando o programa...\n");
                    return 0;
               case 1:
                    // INSERT FIRST
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    printf("Digite o departamento: ");
                    scanf("%s", departamento);
                    printf("Digite o cargo: ");
                    scanf("%s", cargo);
                    printf("Digite as tarefas: ");
                    scanf("%s", tarefas);
                    insert_first(&list, strdup(nome), strdup(departamento), strdup(cargo), strdup(tarefas));
                    break;
               case 2:
                    // INSERT LAST
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    printf("Digite o departamento: ");
                    scanf("%s", departamento);
                    printf("Digite o cargo: ");
                    scanf("%s", cargo);
                    printf("Digite as tarefas: ");
                    scanf("%s", tarefas);
                    insert_last(&list, strdup(nome), strdup(departamento), strdup(cargo), strdup(tarefas));
                    break;
               case 3:
                    // INSERT AT
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    printf("Digite o departamento: ");
                    scanf("%s", departamento);
                    printf("Digite o cargo: ");
                    scanf("%s", cargo);
                    printf("Digite as tarefas: ");
                    scanf("%s", tarefas);
                    printf("Digite a Posicao: ");
                    scanf("%d", &index);
                    insert_at(&list, strdup(nome), strdup(departamento), strdup(cargo), strdup(tarefas), index);
                    break;
               case 4:
                    // REMOVE FIRST
                    remove_first(&list);
                    break;
               case 5:
                    // REMOVE LAST
                    remove_last(&list);
                    break;
               case 6:
                    // REMOVE AT
                    printf("Digite a Posicao: ");
                    scanf("%d", &index);
                    remove_at(&list, index);
                    break;
               case 7:
                    // SEARCH
                    printf("Digite o nome a ser pesquisado: ");
                    scanf("%s", nome);
                    search(&list, nome);
                    break;
               case 8:
                    // PRINT LIST
                    print_list(&list);
                    break;
               default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
          }
     }
}