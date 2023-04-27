#include <stdio.h>
#include <stdlib.h>

#define tam_hash 7

typedef struct Celula {
    int valor;
    struct Celula* proximo;
} Celula;

typedef struct {
    Celula* inicio;
} Lista;

typedef struct {
    Lista* table[tam_hash];
} Hash;

Hash* start_hash() {
    Hash* hash = malloc(sizeof(Hash));
    for(int i = 0; i < tam_hash; i++) {
        Lista* lista = malloc(sizeof(Lista));
        lista->inicio = NULL;
        hash->table[i] = lista;
    }
    return hash;
}

void inserir_hash(Hash* hash, int valor) {
    int indice = valor % tam_hash;
    Celula* nova_celula = malloc(sizeof(Celula));
    nova_celula->valor = valor;
    nova_celula->proximo = hash->table[indice]->inicio;
    hash->table[indice]->inicio = nova_celula;
}

void remover_hash(Hash* hash, int valor) {
    int indice = valor % tam_hash;
    Celula* atual = hash->table[indice]->inicio;
    Celula* anterior = NULL;
    while(atual != NULL) {
        if(atual->valor == valor) {
            if(anterior == NULL) {
                hash->table[indice]->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void imprimir(Hash* hash) {
     printf("---------------------\n");
    for(int i = 0; i < tam_hash; i++) {
        printf("%d -> ", i);
        Celula* atual = hash->table[i]->inicio;
        while(atual != NULL) {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("---------------------\n");
}

int main(void) {
    int valores[] = {190, 322, 172, 89, 13, 4, 769, 61, 15, 76, 97, 28, 80, 76, 88};
	int tam = sizeof(valores) / sizeof(int);
	Hash* hash = start_hash();
	for(int i = 0; i < tam; i++){
		inserir_hash(hash, valores[i]);
	}
	imprimir(hash);
	for(int i = 5; i < 10; i++){
		remover_hash(hash, valores[i]);
	}
	imprimir(hash);	
	for(int i = 3; i < 7; i++){
		inserir_hash(hash, valores[i]);
	}
	imprimir(hash);
	for(int i = 10; i < 15; i++){
		remover_hash(hash, valores[i]);
	}
	imprimir(hash);	
  return 0;
}