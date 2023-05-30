# Pilhas

As pilhas são uma estrutura de dados simples que segue a estratégia LIFO (Last In, First Out), em que o último elemento inserido é o primeiro a ser removido. Todas as operações de remoção e inserção são realizadas no topo da pilha. Não é possível retirar ou adicionar elementos em posições intermediárias. No entanto, vale ressaltar que as pilhas podem ser implementadas tanto de forma estática quanto dinâmica, dependendo das necessidades e recursos disponíveis. Na implementação estática, o tamanho da pilha é definido previamente e utiliza uma estrutura de dados fixa, como um array. Já na implementação dinâmica, o tamanho da pilha pode variar durante a execução e é utilizada uma estrutura de dados encadeada, em que cada elemento contém um ponteiro para o próximo elemento da pilha.

### **Estrutura simples de uma pilha**

```c
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int element) {
    if (isFull(stack)) {
        printf("Erro: Pilha cheia\n");
        return;
    }
    
    stack->top++;
    stack->data[stack->top] = element;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia\n");
        return -1; // Valor inválido para indicar erro
    }
    
    int element = stack->data[stack->top];
    stack->top--;
    return element;
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia\n");
        return -1; // Valor inválido para indicar erro
    }
    
    return stack->data[stack->top];
}
```