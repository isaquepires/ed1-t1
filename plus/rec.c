//#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int numeros;
  struct Num *prox;
} Num;

int main ()
{
  Num *n = (Num*)malloc(sizeof(Num));
  int len = sizeof(*n)/sizeof(n[0]);


  n->numeros = {5, 6, 7, 8, 9, 4, 3, 2, 1, 0};
  

  return 0;

}
