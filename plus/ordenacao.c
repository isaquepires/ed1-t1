#include <stdio.h>

void Ordena(int A[], int n)
{
  int i, j, min, x;

  for (i = 1; i < n; i++)
  {
    min = i;
    for (j = i + 1; j <= n; j++)
    {
      if (A[j - 1] < A[min - 1])
        min = j;

      x = A[min - 1];
      A[min - 1] = A[i - 1];
      A[i - 1] = x;
    }
  }
}

int main ()
{
  int A[9] = {1, 4, 6, 3, 2, 5, 7, 8, 0}, n = 9;

  Ordena(A, n);

   printf("Array ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

  return 0;
}
