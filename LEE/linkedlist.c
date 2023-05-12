#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; // valor do no atual
    struct Node* next; // ponteiro para o proximo no
} Node;

void append(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;

    Node* last = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void removeValue(Node** head_ref, int value) {
    Node* temp = *head_ref, *prev;

    // Caso o valor esteja na primeira posição
    if (temp != NULL && temp->data == value) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // Procura o valor a ser removido
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // Caso o valor não esteja na lista
    if (temp == NULL) {
        return;
    }

    // Remove o nó que contém o valor
    prev->next = temp->next;
    free(temp);
}

void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

int size(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int search(Node* head, int value) {
    int position = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            printf("O valor %d está na posição %d da lista.\n", value, position);
            return position;
        }
        position++;
        current = current->next;
    }
    printf("O valor %d não foi encontrado na lista.\n", value);
    return -1;
}

void findMin(Node* head) {
    if (head == NULL) {
        printf("Lista vazia\n");
        return;
    }

    int min = head->data;
    Node* current = head->next;

    while (current != NULL) {
        if (current->data < min) {
            min = current->data;
        }
        current = current->next;
    }

    printf("O menor valor na lista é: %d\n", min);
}

void findMax(Node* head) {
    Node* current = head;
    int max = head->data;

    while (current != NULL) {
        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }

    printf("Maior valor: %d\n", max);
}

int main() {
    Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    removeValue(&head, 4);
    findMin(head);
    findMax(head);

    printf("Tamanho da lista: %d\n", size(head));

    printList(head);
    search(head, 3);

    return 0;
}
