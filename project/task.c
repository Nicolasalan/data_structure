#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

typedef struct TaskNode {
    char* nome_tarefa;
    char* data_registro;
    char* prazo_conclusao;
    struct TaskNode* next;
} TaskNode;

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    char* nome;
    char* departamento;
    char* cargo;
    TaskNode* task_queue;
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

void enqueue(Node* node, char* nome_tarefa, char* data_registro, char* prazo_conclusao) {
    TaskNode* new_task = malloc(sizeof(TaskNode));
    new_task->nome_tarefa = nome_tarefa;
    new_task->data_registro = data_registro;
    new_task->prazo_conclusao = prazo_conclusao;
    new_task->next = NULL;

    if (node->task_queue == NULL) {
        node->task_queue = new_task;
    } else {
        TaskNode* current = node->task_queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_task;
    }
}

Node* init_node(char* nome, char* departamento, char* cargo) {
    Node* new_node = malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->nome = nome;
    new_node->departamento = departamento;
    new_node->cargo = cargo;
    new_node->task_queue = NULL;
    return new_node;
}

// ========= INSERT =========
void insert_task(Node* node, char* nome_tarefa, char* data_registro, char* prazo_conclusao) {
    enqueue_task(node, nome_tarefa, data_registro, prazo_conclusao);
}

void remove_task(Node* node, char* nome_tarefa) {
    if (node->task_queue == NULL) {
        return;  // Fila vazia
    }

    TaskNode* current = node->task_queue;
    TaskNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->nome_tarefa, nome_tarefa) == 0) {
            if (prev == NULL) {
                node->task_queue = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void search_task(Node* node, char* nome_tarefa) {
    if (node->task_queue == NULL) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }

    TaskNode* current = node->task_queue;
    while (current != NULL) {
        if (strcmp(current->nome_tarefa, nome_tarefa) == 0) {
            printf("Nome da tarefa: %s\n", current->nome_tarefa);
            printf("Data de registro: %s\n", current->data_registro);
            printf("Prazo para conclusão: %s\n", current->prazo_conclusao);
            return;
        }
        current = current->next;
    }

    printf("Nenhuma tarefa encontrada com o nome: %s\n", nome_tarefa);
}

void show_all_tasks(Node* node) {
    if (node->task_queue == NULL) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }

    TaskNode* current = node->task_queue;
    while (current != NULL) {
        printf("Nome da tarefa: %s\n", current->nome_tarefa);
        printf("Data de registro: %s\n", current->data_registro);
        printf("Prazo para conclusão: %s\n\n", current->prazo_conclusao);
        current = current->next;
    }
}

int main() {
     DoublyLinkedList* list = init_list();

     // Adicionar colaborador com várias tarefas
     Node* colaborador = init_node("Nome", "Departamento", "Cargo");
     insert_task(colaborador, "Tarefa1", "2023-05-19", "2023-06-30");
     insert_task(colaborador, "Tarefa2", "2023-05-20", "2023-07-15");
     insert_task(colaborador, "Tarefa3", "2023-05-21", "2023-06-25");
     enqueue(list, colaborador);

     // Remover uma tarefa do colaborador
     remove_task(colaborador, "Tarefa2");

     // Buscar uma tarefa pelo nome
     search_task(colaborador, "Tarefa3");

     // Mostrar todas as tarefas
     show_all_tasks(colaborador);
}
