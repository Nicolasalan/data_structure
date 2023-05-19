#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
     struct Node* next;
     struct Node* prev;
     int data;
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

Node* init_node(int data) {
     Node* new_node = malloc(sizeof(Node));
     new_node->data = data;
     new_node->next = NULL;
     new_node->prev = NULL;
     return new_node;
}

void insert(DoublyLinkedList* list, int data) {
     Node* new_node = init_node(data);
     if (list->head == NULL) {
          list->head = new_node;
          list->size++;
          return;
     }
     Node* current = list->head;
     Node* prev = NULL;
     while (current != NULL && current->data <= new_node->data) {
          prev = current;
          current = current->next;
     }
     if (prev == NULL) {
          new_node->next = current;
          current->prev = new_node;
          list->head = new_node;
          list->size++;
          return;
     }
     if (current == NULL) {
          prev->next = new_node;
          new_node->prev = prev;
          list->size++;
          return;
     }
     new_node->next = current;
     prev->next = new_node;
     new_node->prev = prev;
     current->prev = new_node;
     list->size++;

     return;
}

void insert_first(DoublyLinkedList* list, int data) {
     Node* new_node = init_node(data);

     if (list->head == NULL) {
          list->head = new_node;
          list->size++;
          return;
     }

     new_node->next = list->head;
     list->head->prev = new_node;
     list->head = new_node;
     list->size++;
}

void insert_at(DoublyLinkedList* list, int data, int index) {
     if (index < 0 || index > list->size) {
          printf("Invalid index\n");
          return;
     }

     if (index == 0) {
          Node* new_node = init_node(data);
          new_node->next = list->head;

          if (list->head != NULL)
               list->head->prev = new_node;

          list->head = new_node;
          list->size++;
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

     Node* new_node = init_node(data);
     new_node->prev = current;
     new_node->next = current->next;

     if (current->next != NULL)
          current->next->prev = new_node;

     current->next = new_node;
     list->size++;
}

void insert_last(DoublyLinkedList* list, int data) {
     Node* new_node = init_node(data);

     if (list->head == NULL) {
          list->head = new_node;
          list->size++;
          return;
     }

     Node* current = list->head;
     while (current->next != NULL) {
          current = current->next;
     }

     current->next = new_node;
     new_node->prev = current;
     list->size++;
}

void remove_at(DoublyLinkedList* list, int index) {
     if (index < 0 || index >= list->size) {
          printf("Index out of bounds\n");
          return;
     }

     Node* current = list->head;
     Node* prev = NULL;

     if (index == 0) {
          list->head = current->next;
          if (list->head != NULL)
               list->head->prev = NULL;
          int removed_value = current->data;
          free(current);
          list->size--;
          printf("Removed value: %d\n", removed_value);
          return;
     }

     for (int i = 0; i < index; i++) {
          prev = current;
          current = current->next;
     }

     prev->next = current->next;
     if (current->next != NULL)
          current->next->prev = prev;

     int removed_value = current->data;
     free(current);
     list->size--;

     printf("Removed value: %d\n", removed_value);
}

void remove_first(DoublyLinkedList* list) {
     if (list->head == NULL) {
          printf("List is empty\n");
          return;
     }

     Node* current = list->head;
     list->head = current->next;
     if (list->head != NULL)
          list->head->prev = NULL;

     int removed_value = current->data;
     free(current);
     list->size--;

     printf("Removed value: %d\n", removed_value);
}

void remove_last(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
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

    int removed_value = current->data;
    free(current);
    list->size--;

    printf("Removed value: %d\n", removed_value);
}

void print_list(DoublyLinkedList* list) {
     if (list->head == NULL) {
          printf("List is empty\n");
          return;
     }

     Node* current = list->head;
     printf("List elements: ");
     while (current != NULL) {
          printf("%d ", current->data);
          current = current->next;
     }
     printf("\n");
}

int main() {
     DoublyLinkedList* list = init_list();
     insert(list, 5);
     insert(list, 3);
     insert(list, 8);
     insert(list, 1);
     insert(list, 9);
     insert_at(list, 4, 4);
     //insert_last(list, 10);
     //insert_first(list, 0);
     //remove_at(list, 0);
     print_list(list);
     return 0;
}
