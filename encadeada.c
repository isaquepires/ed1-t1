#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 10

typedef struct Pessoa
{
  char nome[TAM_NOME];
  int rg;
  struct Pessoa *prox;
} Pessoa;

Pessoa* nova(char *nome, int rg)
{
  Pessoa *nova_pessoa = (Pessoa*)malloc(sizeof(Pessoa));
  
  int i;
  for (i = 0; nome[i] != '\0'; i++)
    nova_pessoa->nome[i] = nome[i];

  nova_pessoa->nome[i] = '\0';
  nova_pessoa->rg = rg;
  nova_pessoa->prox = NULL;

  return nova_pessoa;
}

void libera(Pessoa *inicio) {
  Pessoa *atual = inicio;
  while (atual != NULL) {
    Pessoa *temp = atual;
    atual = atual->prox;
    free(temp);
  }
}


int main()
{
  FILE *arquivo;
  Pessoa *inicio = NULL, *ultimo = NULL;

  arquivo = fopen("./NomeRG10.txt", "r");

  char nome[TAM_NOME];
  int rg;

  while (fscanf(arquivo, "%9[^,],%d\n", nome, &rg) == 2)
  {
    Pessoa *nova_pessoa = nova(nome, rg);
  
    if (inicio == NULL)
      inicio = nova_pessoa;
    else
      ultimo->prox = nova_pessoa;

    ultimo = nova_pessoa;
  }

  fclose(arquivo);

  Pessoa *atual = inicio;
  
  while (atual != NULL) {
    printf("NOME: %s, RG: %d\n", atual->nome, atual->rg);
    atual = atual->prox;
  }

  libera(inicio);
  
  return 0;
}
