#include <stdio.h>

#define MAX 10

typedef struct
{
  int itens[MAX];
  int topo;
} Pilha;

void iniciaPilha (Pilha *p)
{
  p->topo = -1;
}

int cheia(Pilha *p)
{
  return p->topo == MAX - 1;
}

int vazia(Pilha *p)
{
  return p->topo == -1;
}

void push(Pilha *p, int valor) {
    if (cheia(p)) {
        printf("Erro: a pilha está cheia.\n");
        return;
    }
    p->itens[++(p->topo)] = valor;
}

int pop(Pilha *p) {
    if (vazia(p)) {
        printf("Erro: a pilha está vazia.\n");
        return -1; // Valor especial para indicar erro
    }
    return p->itens[(p->topo)--];
}


int peek(Pilha *p) {
    if (vazia(p)) {
        printf("Erro: a pilha está vazia.\n");
        return -1; // Valor especial para indicar erro
    }
    return p->itens[p->topo];
}

int main()
{
    Pilha p;
    iniciaPilha(&p);

    // Testando a pilha
    push(&p, 1);
    push(&p, 2);
    push(&p, 3);
    push(&p, 4);

    printf("Elemento no topo: %d\n", peek(&p)); // Deve imprimir 30

    printf("Removendo: %d\n", pop(&p));         // Deve remover e imprimir 30
    printf("Elemento no topo: %d\n", peek(&p)); // Deve imprimir 20

    pop(&p); // Remove 20
    pop(&p); // Remove 10

    // Tenta remover de uma pilha vazia
    pop(&p);

    return 0;
}

