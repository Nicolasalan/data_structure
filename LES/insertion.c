#include <stdio.h>
#define capacity 10

void print(int list[], int n){
     for(int i = 0; i < n; i++){
          printf("%d ", list[i]);
     }
     printf("\n");
} 

int insertion_position(int list[], int value, int n){
     int idx = 0;
     if(n == capacity)
          return -1;
     while(value > list[idx] && idx < n)
          idx++;
     return idx;
}

int insert(int list[], int value, int n){
     if(n == 0){
          list[n] = value;
          return 1;
     }
     int idx = insertion_position(list, value, n);
     if(idx >= 0){
          for(int i = n; i >= idx; i--)
               list[i] = list[i - 1];
          list[idx] = value;
          return 1;
     }
     return 0;
}

int main(void) {
        int values[] = {6, 4, 7, 2, 1, 3, 9, 5, 8, 0};
        int n = 0, x;
        int list[capacity];
        printf("===== INSERT =====\n");
        for(int i = 0; i < capacity; i++){
                printf("Inserir %d\n", values[i]);
                x = insert(list, values[i], n);
                if(x > 0)
                    n++;
                    print(list, n);
     }
}