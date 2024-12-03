#include <stdio.h>
#include <stdlib.h>

// Estrutura do tipo estudante:
typedef struct Estudante {
  int ra;
  char *nome;
} Estudante;


int main ()
{
  // isaque - stack (memória automática)
  Estudante isaque;

  isaque.ra = 2655144;
  isaque.nome = "Isaque Cortina Pires";

  printf("%d ", isaque.ra);
  printf("%s\n", isaque.nome);

  // outro - heap (memória dinâmica)
  Estudante *outro = malloc(sizeof(Estudante));

  outro->ra = 1234567;
  outro->nome = "Outro Estudante";

  printf("%d ", outro->ra);
  printf("%s\n", outro->nome);

  free(outro);
  
  return 0;
}
