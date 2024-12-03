#include <stdio.h>
int busca (int *lista, int elem)
{
  int i, n = 10;

  for (i = 0; i < n; i++)
  {
    if (lista[i] == elem)
      return i;
  }

  return 0;
}

int binaria (int *lista, int elem, int inicio, int fim)
{
  if (inicio > fim)
    return -1;

  int meio = (inicio + fim) / 2;

  if (lista[meio] == elem)
    return meio;  // Elemento encontrado
  else if (lista[meio] > elem)
    return binaria(lista, elem, inicio, meio - 1);  // Busca na metade esquerda
  else
    return binaria(lista, elem, meio + 1, fim);
}
int main ()
{
  int lista[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int len = sizeof(lista)/sizeof(lista[0]);
  int elemento = 8;
  int indice;
    
  indice = busca(lista, elemento);
  printf("pela sequencial: %d\n", indice);
  
  indice = binaria(lista, elemento, 0, len - 1);
  printf("pela binaria: %d\n", indice);

  return 0;
}
