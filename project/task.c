#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// TODO: ao colocar espaco ele ja conta para o proximo no caso o registro
void add_task_to_collaborator(DoublyLinkedList* list, char* nome_colaborador, char* nome_tarefa, char* data_registro, char* prazo_conclusao) {

    Node* curr = list->head;

    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {

            Task* new_task = malloc(sizeof(Task));
            new_task->nome = malloc(strlen(nome_tarefa) + 1);
            strcpy(new_task->nome, nome_tarefa);
            new_task->data_registro = malloc(strlen(data_registro) + 1);
            strcpy(new_task->data_registro, data_registro);
            new_task->prazo_conclusao = malloc(strlen(prazo_conclusao) + 1);
            strcpy(new_task->prazo_conclusao, prazo_conclusao);
            new_task->next = NULL;

            if (curr->task_queue->front == NULL) {
                curr->task_queue->front = new_task;
                curr->task_queue->rear = new_task;
            } else {
                curr->task_queue->rear->next = new_task;
                curr->task_queue->rear = new_task;
            }

            printf(COLOR_GREEN "Tarefa adicionada ao colaborador\n" COLOR_RESET);
            return;
        }

        curr = curr->next;
    }

    printf(COLOR_YELLOW "Colaborador não encontrado \n" COLOR_RESET);
}

void show_all_tasks(DoublyLinkedList* list) {
    Node* curr = list->head;

    if (curr == NULL) {
        printf(COLOR_YELLOW "A lista de colaboradores está vazia.\n" COLOR_RESET);
        return;
    }

    while (curr != NULL) {
        printf("Colaborador: %s\n", curr->nome);

        Task* task = curr->task_queue->front;

        if (task == NULL) {
            printf(COLOR_YELLOW "Nenhuma tarefa atribuída.\n" COLOR_RESET);
        } else {
            printf("Tarefas:\n");
            while (task != NULL) {
                printf("- %s\n", task->nome);
                printf("  Data de registro: %s\n", task->data_registro);
                printf("  Prazo de conclusão: %s\n", task->prazo_conclusao);
                task = task->next;
            }
        }

        curr = curr->next;
    }
}

void remove_task_from_collaborator(DoublyLinkedList* list, char* nome_colaborador, char* nome_tarefa) {
    Node* curr = list->head;

    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {
            Task* curr_task = curr->task_queue->front;
            Task* prev_task = NULL;

            while (curr_task != NULL) {
                if (strcmp(curr_task->nome, nome_tarefa) == 0) {

                    if (prev_task == NULL) {

                        curr->task_queue->front = curr_task->next;
                        if (curr_task->next == NULL) {
                            curr->task_queue->rear = NULL;
                        }
                    } else {
                        prev_task->next = curr_task->next;
                        if (curr_task->next == NULL) {
                            curr->task_queue->rear = prev_task;
                        }
                    }

                    free(curr_task->nome);
                    free(curr_task->data_registro);
                    free(curr_task->prazo_conclusao);
                    free(curr_task);
                    
                    printf(COLOR_RED "Tarefa removida do colaborador '%s'.\n" COLOR_RESET, curr->nome);
                    return;
                }

                prev_task = curr_task;
                curr_task = curr_task->next;
            }

            printf(COLOR_YELLOW "Tarefa '%s' não encontrada para o colaborador '%s'.\n" COLOR_RESET, nome_tarefa, nome_colaborador);
            return;
        }

        curr = curr->next;
    }

    printf(COLOR_YELLOW "Colaborador '%s' não encontrado.\n" COLOR_RESET, nome_colaborador);
}

void search_task(DoublyLinkedList* list, char* nome_tarefa) {
    Node* curr = list->head;
    int found = 0;

    while (curr != NULL) {
        Task* task = curr->task_queue->front;

        while (task != NULL) {
            if (strcmp(task->nome, nome_tarefa) == 0) {
                if (!found) {
                    printf(COLOR_GREEN "Tarefa encontrada:\n" COLOR_RESET);
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
        printf(COLOR_YELLOW "Nenhuma tarefa com o nome '%s' encontrada.\n" COLOR_RESET, nome_tarefa);
    }
}

void insert_fisrt_collaborator(DoublyLinkedList* list, char* nome, char* departamento, char* cargo) {
    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf(COLOR_YELLOW "Erro: Falha ao alocar memória para o novo colaborador.\n" COLOR_RESET);
        return;
    }

    if (list->head == NULL) {

        list->head = new_node;
    } else {

        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }

    list->size++;

    printf(COLOR_GREEN "Colaborador '%s' adicionado com sucesso no início da lista.\n" COLOR_RESET, nome);
}

void insert_end_collaborator(DoublyLinkedList* list, char* nome, char* departamento, char* cargo) {
    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf(COLOR_YELLOW "Erro: Falha ao alocar memória para o novo colaborador.\n" COLOR_RESET);
        return;
    }

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = new_node;
        new_node->prev = curr;
    }

    list->size++;

    printf(COLOR_GREEN "Colaborador '%s' adicionado com sucesso no final da lista.\n" COLOR_RESET, nome);
}

void insert_at_collaborator(DoublyLinkedList* list, int position, char* nome, char* departamento, char* cargo) {
    if (position < 1 || position > list->size + 1) {
        printf(COLOR_YELLOW "Erro: Posição inválida para inserção.\n" COLOR_RESET);
        return;
    }

    Node* new_node = init_node(nome, departamento, cargo);

    if (new_node == NULL) {
        printf(COLOR_YELLOW "Erro: Falha ao alocar memória para o novo colaborador.\n" COLOR_RESET);
        return;
    }

    if (position == 1) {

        new_node->next = list->head;
        if (list->head != NULL) {
            list->head->prev = new_node;
        }
        list->head = new_node;
    } else {

        Node* curr = list->head;
        int count = 1;
        while (count < position - 1) {
            curr = curr->next;
            count++;
        }

        new_node->next = curr->next;
        if (curr->next != NULL) {
            curr->next->prev = new_node;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }

    list->size++;

    printf(COLOR_GREEN "Colaborador '%s' adicionado com sucesso na posição %d da lista.\n" COLOR_RESET, nome, position);
}

void show_all_records(DoublyLinkedList* list) {
    Node* curr = list->head;

    if (curr == NULL) {
        printf(COLOR_YELLOW "A lista de colaboradores está vazia.\n" COLOR_RESET);
        return;
    }

    while (curr != NULL) {
        printf("Colaborador: %s\n", curr->nome);
        printf("Departamento: %s\n", curr->departamento);
        printf("Cargo: %s\n", curr->cargo);

        Task* task = curr->task_queue->front;

        if (task == NULL) {
            printf(COLOR_YELLOW "Nenhuma tarefa atribuída.\n" COLOR_RESET);
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
                printf(COLOR_YELLOW "Nenhuma tarefa atribuída.\n" COLOR_RESET);
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

void remove_first_collaborator(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf(COLOR_YELLOW "A lista de colaboradores está vazia. Nenhum colaborador removido.\n" COLOR_RESET);
        return;
    }

    Node* removed_node = list->head;
    list->head = removed_node->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    }

    char * remove_nome = removed_node->nome;
    char * remove_departamento = removed_node->departamento;
    char * remove_cargo = removed_node->cargo;

    Task* task = removed_node->task_queue->front;
    while (task != NULL) {
        Task* next_task = task->next;
        char* remove_task = task->nome;
        char* remove_registro = task->data_registro;
        char* remove_conclusao = task->prazo_conclusao;

        task = next_task;
    }

    free(removed_node->task_queue);
    free(removed_node);

    list->size--;
    printf(COLOR_RED "Colaborador removido do início da lista.\n" COLOR_RESET);
}

void remove_last_collaborator(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf(COLOR_YELLOW "A lista de colaboradores está vazia. Nenhum colaborador removido.\n" COLOR_RESET);
        return;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        list->head = NULL;
    } else {
        prev->next = NULL;
    }

    char * remove_nome = curr->nome;
    char * remove_departamento = curr->departamento;
    char * remove_cargo = curr->cargo;

    Task* task = curr->task_queue->front;
    while (task != NULL) {
        Task* next_task = task->next;
        char* remove_task = task->nome;
        char* remove_registro = task->data_registro;
        char* remove_conclusao = task->prazo_conclusao;
        task = next_task;
    }

    free(curr->task_queue);
    free(curr);

    list->size--;
    printf(COLOR_RED "Colaborador removido do final da lista.\n" COLOR_RESET);
}

void remove_collaborator(DoublyLinkedList* list, char* nome_colaborador) {
    if (list->head == NULL) {
        printf(COLOR_YELLOW "A lista de colaboradores está vazia. Nenhum colaborador removido.\n" COLOR_RESET);
        return;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->nome, nome_colaborador) == 0) {

            if (prev == NULL) {
                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }

            if (curr->next != NULL) {
                curr->next->prev = prev;
            }

            char * remove_nome = curr->nome;
            char * remove_departamento = curr->departamento;
            char * remove_cargo = curr->cargo;

            Task* task = curr->task_queue->front;
            while (task != NULL) {
                Task* next_task = task->next;
                char* remove_task = task->nome;
                char* remove_registro = task->data_registro;
                char* remove_conclusao = task->prazo_conclusao;
                task = next_task;
            }

            free(curr->task_queue);
            free(curr);

            list->size--;
            printf(COLOR_RED "Colaborador '%s' removido da lista.\n" COLOR_RESET, nome_colaborador);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf(COLOR_YELLOW "Colaborador '%s' não encontrado na lista.\n" COLOR_RESET, nome_colaborador);
}

int readIntInput() {
    int value;
    char input[20];
    if (scanf("%19s", input) != 1) {
        return -1;
    }

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return -1;
        }
    }

    value = atoi(input);
    return value;
}

int main() {
    DoublyLinkedList* list = init_list();

    int choice;
    int colab;
    int task;
    int pos;
    char nome[100];
    char departamento[100];
    char cargo[100];
    char nome_tarefa[100];
    char data_registro[100];
    char prazo_conclusao[100];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Funcoes de Tarefa\n");
        printf("2. Funcoes de Colaboratores\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        choice = readIntInput();

        switch (choice) {
            case 0:
                printf("\nEncerrando o programa...\n");
                return 0;
            case 1:
                if (list->head == NULL) {
                    printf(COLOR_YELLOW "Não há colaboradores na lista. Adicione um colaborador primeiro.\n" COLOR_RESET);
                    break;
                }
                while (1) {
                    // TASK
                    printf("\n----- Menu de Tarefas -----\n");
                    printf("1. Adicionar tarefa\n");
                    printf("2. Remover tarefa\n");
                    printf("3. Mostrar todas as tarefas\n");
                    printf("4. Mostrar tarefas por colaborador\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha uma opção: ");
                    task = readIntInput();
                    printf("\n");
                    switch (task) {
                        case 0:
                            break;
                        case 1:
                            // INSERT FIRST
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Adicione um colaborador primeiro.\n" COLOR_RESET);
                                break;
                            }
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            printf("Digite o nome da Tarefa: ");
                            scanf("%s", nome_tarefa);
                            printf("Digite a Data de registro: ");
                            scanf("%s", data_registro);
                            printf("Digite o Prazo para conclusão: ");
                            scanf("%s", prazo_conclusao);
                            add_task_to_collaborator(list, strdup(nome), strdup(nome_tarefa), strdup(data_registro), strdup(prazo_conclusao));
                            break;
                        case 2:
                            // REMOVE FIRST
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não há tarefas para remover.\n" COLOR_RESET);
                                break;
                            }
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            printf("Digite o nome da Tarefa: ");
                            scanf("%s", nome_tarefa);
                            remove_task_from_collaborator(list, strdup(nome), strdup(nome_tarefa));
                            break;
                        case 3:
                            // SHOW ALL
                            show_all_tasks(list);
                            break;
                        case 4:
                            // SHOW BY COLLABORATOR
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não é possível mostrar tarefas por colaborador.\n" COLOR_RESET);
                                break;
                            }
                            printf("Digite o nome da Tarefa: ");
                            scanf("%s", nome_tarefa);
                            search_task(list, strdup(nome_tarefa));
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }
                    if (task == 0) {
                        break; 
                    }
                }
                break;
            case 2:
                while (1) {
                    // COLLABORATOR
                    printf("\n----- Menu de Colaboradores -----\n");
                    printf("1. Inserir um colaborador no início da lista\n");
                    printf("2. Inserir um colaborador no final da lista\n");
                    printf("3. Inserir um colaborador em uma posição específica da lista\n");
                    printf("4. Remover um colaborador no início da lista\n");
                    printf("5. Remover um colaborador no final da lista\n");
                    printf("6. Remover um colaborador em uma posição específica da lista\n");
                    printf("7. Buscar um colaborador pelo nome e mostrar todo registro\n");
                    printf("8. Mostrar todos os registros\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opção: ");
                    colab = readIntInput();
                    switch (colab) {
                        case 0:
                            break;
                        case 1:
                            // INSERT FIRST
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            printf("Digite o Departamento: ");
                            scanf("%s", departamento);
                            printf("Digite o Cargo: ");
                            scanf("%s", cargo);
                            insert_fisrt_collaborator(list, strdup(nome), strdup(departamento), strdup(cargo));
                            break;
                        case 2:
                            // INSERT LAST
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            printf("Digite o Departamento: ");
                            scanf("%s", departamento);
                            printf("Digite o Cargo: ");
                            scanf("%s", cargo);
                            insert_end_collaborator(list, strdup(nome), strdup(departamento), strdup(cargo));
                            break;
                        case 3:
                            // INSERT AT
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            printf("Digite o Departamento: ");
                            scanf("%s", departamento);
                            printf("Digite o Cargo: ");
                            scanf("%s", cargo);
                            printf("Digite a posição: ");
                            scanf("%d", &pos);
                            insert_at_collaborator(list, pos, strdup(nome), strdup(departamento), strdup(cargo));
                            break;
                        case 4:
                            // REMOVE FIRST
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não há colaboradores para remover.\n" COLOR_RESET);
                                break;
                            }
                            remove_first_collaborator(list);
                            break;
                        case 5: 
                            // REMOVE LAST
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não há colaboradores para remover.\n" COLOR_RESET);
                                break;
                            }
                            remove_last_collaborator(list);
                            break;
                        case 6:
                            // REMOVE AT
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não há colaboradores para remover.\n" COLOR_RESET);
                                break;
                            }
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            remove_collaborator(list, strdup(nome));
                            break;
                        case 7:
                            // SEARCH
                            if (list->head == NULL) {
                                printf(COLOR_YELLOW "Não há colaboradores na lista. Não é possível buscar por colaborador.\n" COLOR_RESET);
                                break;
                            }
                            printf("Digite o nome do Colaborator: ");
                            scanf("%s", nome);
                            search_collaborator(list, strdup(nome));
                            break;
                        case 8:
                            // SHOW ALL
                            show_all_records(list);
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;

                    if (colab == 0) {
                        break; 
                    }
                }
                break;
            }
        }
    }
    return 0;
}