#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

typedef struct Task {
    char* nome;
    char* data_registro;
    char* prazo_conclusao;
    struct Task* next;
} Task;

typedef struct TaskQueue {
    Task* front;
    Task* rear;
    int size;
} TaskQueue;

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    char* nome;
    char* departamento;
    char* cargo;
    TaskQueue* task_queue; 
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

TaskQueue* init_queue() {
    TaskQueue* queue = malloc(sizeof(TaskQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

Node* init_node(char* nome, char* departamento, char* cargo) {
    Node* new_node = malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->nome = nome;
    new_node->departamento = departamento;
    new_node->cargo = cargo;
    new_node->task_queue = init_queue(); 
}

// ========= INSERT TASK =========
void add_task_to_collaborator(DoublyLinkedList* list, char* nome_colaborador, char* nome_tarefa, char* data_registro, char* prazo_conclusao) {
    Node* curr = list->head;

    // Procura o colaborador na lista
    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {
            // Colaborador encontrado, cria uma nova tarefa
            Task* new_task = malloc(sizeof(Task));
            new_task->nome = malloc(strlen(nome_tarefa) + 1);
            strcpy(new_task->nome, nome_tarefa);
            new_task->data_registro = malloc(strlen(data_registro) + 1);
            strcpy(new_task->data_registro, data_registro);
            new_task->prazo_conclusao = malloc(strlen(prazo_conclusao) + 1);
            strcpy(new_task->prazo_conclusao, prazo_conclusao);
            new_task->next = NULL;

            // Adiciona a nova tarefa à fila de tarefas do colaborador
            if (curr->task_queue->front == NULL) {
                curr->task_queue->front = new_task;
                curr->task_queue->rear = new_task;
            } else {
                curr->task_queue->rear->next = new_task;
                curr->task_queue->rear = new_task;
            }

            printf("Tarefa adicionada ao colaborador '%s'.\n", curr->nome);
            //printf("Tarefa: %s\n", new_task->nome);
            //printf("Data de Registro: %s\n", new_task->data_registro);
            //printf("Prazo de Conclusão: %s\n", new_task->prazo_conclusao);
            return;
        }

        curr = curr->next;
    }

    printf("Colaborador '%s' não encontrado.\n", nome_colaborador);
}

// ========= SHOW ALL TASKS =========
void show_all_tasks(DoublyLinkedList* list) {
    Node* curr = list->head;

    if (curr == NULL) {
        printf("A lista de colaboradores está vazia.\n");
        return;
    }

    while (curr != NULL) {
        printf("Colaborador: %s\n", curr->nome);

        Task* task = curr->task_queue->front;

        if (task == NULL) {
            printf("Nenhuma tarefa atribuída.\n");
        } else {
            printf("Tarefas:\n");
            while (task != NULL) {
                printf("- %s\n", task->nome);
                task = task->next;
            }
        }

        curr = curr->next;
    }
}

void remove_task_from_collaborator(DoublyLinkedList* list, char* nome_colaborador, char* nome_tarefa) {
    Node* curr = list->head;

    // Procura o colaborador na lista
    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {
            Task* curr_task = curr->task_queue->front;
            Task* prev_task = NULL;

            // Procura a tarefa na fila de tarefas do colaborador
            while (curr_task != NULL) {
                if (strcmp(curr_task->nome, nome_tarefa) == 0) {
                    // Tarefa encontrada, remove-a da fila de tarefas
                    if (prev_task == NULL) {
                        // A tarefa é a primeira da fila
                        curr->task_queue->front = curr_task->next;
                        if (curr_task->next == NULL) {
                            // A tarefa também é a última da fila
                            curr->task_queue->rear = NULL;
                        }
                    } else {
                        prev_task->next = curr_task->next;
                        if (curr_task->next == NULL) {
                            // A tarefa é a última da fila
                            curr->task_queue->rear = prev_task;
                        }
                    }

                    free(curr_task->nome);
                    free(curr_task->data_registro);
                    free(curr_task->prazo_conclusao);
                    free(curr_task);
                    
                    printf("Tarefa removida do colaborador '%s'.\n", curr->nome);
                    return;
                }

                prev_task = curr_task;
                curr_task = curr_task->next;
            }

            printf("Tarefa '%s' não encontrada para o colaborador '%s'.\n", nome_tarefa, nome_colaborador);
            return;
        }

        curr = curr->next;
    }

    printf("Colaborador '%s' não encontrado.\n", nome_colaborador);
}

void search_task(DoublyLinkedList* list, char* nome_tarefa) {
    Node* curr = list->head;
    int found = 0;

    while (curr != NULL) {
        Task* task = curr->task_queue->front;

        while (task != NULL) {
            if (strcmp(task->nome, nome_tarefa) == 0) {
                if (!found) {
                    printf("Tarefa encontrada:\n");
                    printf("Tarefa: %s\n", task->nome);
                    printf("Colaboradores:\n");
                }

                printf("- Nome: %s\n", curr->nome);
                printf("  Cargo: %s\n", curr->cargo);
                printf("  Departamento: %s\n", curr->departamento);
                found = 1;
            }

            task = task->next;
        }

        curr = curr->next;
    }

    if (!found) {
        printf("Nenhuma tarefa com o nome '%s' encontrada.\n", nome_tarefa);
    }
}

// ========================================================================================== //

// ========= INSERT =========
void insert_fisrt_collaborator(DoublyLinkedList* list, char* nome, char* departamento, char* cargo) {
    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf("Erro: Falha ao alocar memória para o novo colaborador.\n");
        return;
    }

    if (list->head == NULL) {
        // Se a lista estiver vazia, o novo nó será o único nó na lista
        list->head = new_node;
    } else {
        // Se a lista não estiver vazia, ajuste os ponteiros do novo nó e do nó cabeça
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }

    list->size++;

    printf("Colaborador '%s' adicionado com sucesso no início da lista.\n", nome);
}

void insert_end_collaborator(DoublyLinkedList* list, char* nome, char* departamento, char* cargo) {
    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf("Erro: Falha ao alocar memória para o novo colaborador.\n");
        return;
    }

    if (list->head == NULL) {
        // Se a lista estiver vazia, o novo nó será o único nó na lista
        list->head = new_node;
    } else {
        // Encontre o último nó da lista
        Node* curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        // Ajuste os ponteiros do novo nó e do último nó
        curr->next = new_node;
        new_node->prev = curr;
    }

    list->size++;

    printf("Colaborador '%s' adicionado com sucesso no final da lista.\n", nome);
}

void insert_at_collaborator(DoublyLinkedList* list, int position, char* nome, char* departamento, char* cargo) {
    if (position < 1 || position > list->size + 1) {
        printf("Erro: Posição inválida para inserção.\n");
        return;
    }

    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf("Erro: Falha ao alocar memória para o novo colaborador.\n");
        return;
    }

    if (position == 1) {
        // Inserir no início da lista
        new_node->next = list->head;
        if (list->head != NULL) {
            list->head->prev = new_node;
        }
        list->head = new_node;
    } else {
        // Encontrar o nó na posição anterior à posição desejada
        Node* curr = list->head;
        int count = 1;
        while (count < position - 1) {
            curr = curr->next;
            count++;
        }

        // Ajustar os ponteiros do novo nó e dos nós adjacentes
        new_node->next = curr->next;
        if (curr->next != NULL) {
            curr->next->prev = new_node;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }

    list->size++;

    printf("Colaborador '%s' adicionado com sucesso na posição %d da lista.\n", nome, position);
}

void free_task_queue(TaskQueue* queue) {
    Task* curr = queue->front;
    Task* next;

    while (curr != NULL) {
        next = curr->next;
        free(curr->nome);
        free(curr->data_registro);
        free(curr->prazo_conclusao);
        free(curr);
        curr = next;
    }

    free(queue);
}

void free_node(Node* node) {
    if (node == NULL) {
        return;
    }
    
    free(node->nome);
    free(node->departamento);
    free(node->cargo);
    free_task_queue(node->task_queue);
    free(node);
}

void remove_first_collaborator(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("A lista de colaboradores está vazia.\n");
        return;
    }

    Node* removed_node = list->head;
    list->head = removed_node->next;

    // Verifica se a lista ficou vazia após a remoção
    if (list->head == NULL) {
        list->size = 0;
    } else {
        list->head->prev = NULL;
        list->size--;
    }

    free_node(removed_node);
    printf("Colaborador removido com sucesso.\n");
}

void show_all_records(DoublyLinkedList* list) {
    Node* curr = list->head;

    if (curr == NULL) {
        printf("A lista de colaboradores está vazia.\n");
        return;
    }

    while (curr != NULL) {
        printf("Colaborador: %s\n", curr->nome);
        printf("Departamento: %s\n", curr->departamento);
        printf("Cargo: %s\n", curr->cargo);

        Task* task = curr->task_queue->front;

        if (task == NULL) {
            printf("Nenhuma tarefa atribuída.\n");
        } else {
            printf("Tarefas:\n");
            while (task != NULL) {
                printf("- %s\n", task->nome);
                printf("  Data de Registro: %s\n", task->data_registro);
                printf("  Prazo de Conclusão: %s\n", task->prazo_conclusao);
                task = task->next;
            }
        }

        printf("\n");

        curr = curr->next;
    }
}

void search_collaborator(DoublyLinkedList* list, char* nome_colaborador) {
    Node* curr = list->head;

    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {
            printf("Colaborador: %s\n", curr->nome);
            printf("Departamento: %s\n", curr->departamento);
            printf("Cargo: %s\n", curr->cargo);

            Task* task = curr->task_queue->front;

            if (task == NULL) {
                printf("Nenhuma tarefa atribuída.\n");
            } else {
                printf("Tarefas:\n");
                while (task != NULL) {
                    printf("- %s\n", task->nome);
                    printf("  Data de Registro: %s\n", task->data_registro);
                    printf("  Prazo de Conclusão: %s\n", task->prazo_conclusao);
                    task = task->next;
                }
            }

            return;
        }

        curr = curr->next;
    }

    printf("Colaborador '%s' não encontrado.\n", nome_colaborador);
}

void remove_last_collaborator(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("A lista de colaboradores está vazia. Nenhum colaborador removido.\n");
        return;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    // Percorre até o último colaborador
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        // Remove o único colaborador da lista
        list->head = NULL;
    } else {
        // Remove o último colaborador da lista
        prev->next = NULL;
    }

    // Libera a memória alocada para o colaborador removido
    free(curr->nome);
    free(curr->departamento);
    free(curr->cargo);

    // Libera a memória alocada para as tarefas do colaborador removido
    Task* task = curr->task_queue->front;
    while (task != NULL) {
        Task* next_task = task->next;
        free(task->nome);
        free(task->data_registro);
        free(task->prazo_conclusao);
        free(task);
        task = next_task;
    }

    free(curr->task_queue);
    free(curr);

    list->size--;
    printf("Colaborador removido do final da lista.\n");
}



int main() {
    DoublyLinkedList* list = init_list();

    insert_fisrt_collaborator(list, "John Doe", "Departamento A", "Cargo A");
    insert_fisrt_collaborator(list, "Jane Smith", "Departamento B", "Cargo B");
    insert_fisrt_collaborator(list, "Mark Johnson", "Departamento C", "Cargo C");
    insert_end_collaborator(list, "Mary Williams", "Departamento D", "Cargo D");
    //insert_at_collaborator(list, 6, "James Brown", "Departamento E", "Cargo E");

    //remove_first_collaborator(list);

    add_task_to_collaborator(list, "John Doe", "Tarefa 1", "2023-05-21", "2023-05-28");
    add_task_to_collaborator(list, "Jane Smith", "Tarefa 2", "2023-05-21", "2023-05-28");
    add_task_to_collaborator(list, "Mark Johnson", "Tarefa 3", "2023-05-21", "2023-05-28");

    //show_all_records(list);

    search_collaborator(list, "John Doe");

    remove_last_collaborator(list);

    //remove_task_from_collaborator(list, "Jane Smith", "Tarefa 2");

    //show_all_tasks(list);

    //search_task(list, "Tarefa 1");

    return 0;

}
