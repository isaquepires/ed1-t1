#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10
#define TAM_NOME 10

typedef struct
{
  char nome[TAM_NOME];
  int rg;
} Pessoa;

int main()
{
  FILE *arquivo;
  int cont = 0;

  arquivo = fopen("./NomeRG10.txt", "r");

  Pessoa *lista = malloc(LINHAS*sizeof(Pessoa));

  while (fscanf(arquivo, "%9[^,],%d\n", lista[cont].nome, &lista[cont].rg) == 2)
    cont++;
  

  fclose(arquivo);

  for (int i = 0; i < cont; i++)
    printf("NOME: %s, RG: %d\n", lista[i].nome, lista[i].rg);
  
  free(lista);
  return 0;
}
