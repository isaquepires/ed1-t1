#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 10

typedef struct
  {
    char nome[TAM_NOME];
    int rg;
  } SeqPessoa;

typedef struct EncPessoa
  {
    char nome[TAM_NOME];
    int rg;
    struct EncPessoa *prox;
  } EncPessoa;

int contar_linhas(char *nome_arquivo)
{
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "r");
  int linhas = 0;
  char caractere;

  while ((caractere = getc(arquivo)) != EOF)
    if (caractere == '\n')
      linhas++;
  
  fclose(arquivo);

  return linhas;
}

void sequencial(FILE *arquivo, char *nome_arquivo)
{
  int cont = 0;

  int linhas = contar_linhas(nome_arquivo);
  
  SeqPessoa *lista = malloc(linhas*sizeof(SeqPessoa));

  while (fscanf(arquivo, "%9[^,],%d\n", lista[cont].nome, &lista[cont].rg) == 2)
    cont++;

  fclose(arquivo);

  for (int i = 0; i < cont; i++)
    printf("NOME: %s, RG: %d\n", lista[i].nome, lista[i].rg);
  
  free(lista);
}

EncPessoa* no(char *nome, int rg)
{
  EncPessoa *nova_pessoa = (EncPessoa*)malloc(sizeof(EncPessoa));
  
  int i;
  for (i = 0; nome[i] != '\0'; i++)
    nova_pessoa->nome[i] = nome[i];

  nova_pessoa->nome[i] = '\0';
  nova_pessoa->rg = rg;
  nova_pessoa->prox = NULL;

  return nova_pessoa;
}

void libera_encadeada(EncPessoa *inicio) {
  EncPessoa *atual = inicio;
  while (atual != NULL) {
    EncPessoa *temp = atual;
    atual = atual->prox;
    free(temp);
  }
}

void encadeada(FILE *arquivo)
{
  EncPessoa *inicio = NULL, *ultimo = NULL;
  
  char nome[TAM_NOME];
  int rg;

  while (fscanf(arquivo, "%9[^,],%d\n", nome, &rg) == 2)
  {
    EncPessoa *nova_pessoa = no(nome, rg);
  
    if (inicio == NULL)
      inicio = nova_pessoa;
    else
      ultimo->prox = nova_pessoa;

    ultimo = nova_pessoa;
  }

  fclose(arquivo);

  EncPessoa *atual = inicio;
  
  while (atual != NULL) {
    printf("NOME: %s, RG: %d\n", atual->nome, atual->rg);
    atual = atual->prox;
  }

  libera_encadeada(inicio);
}

FILE *abrir_aquivo(char *nome_arquivo)
{
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "r");
  return arquivo;
}

char* opcoes_arquivos()
{
  char *nome_arquivo;
  int numero_arquivo;
  printf("Selecione entre os arquivos abaixo: \n\n");
  printf("1) NomeRG10.txt\n2) NomeRG50.txt\n3) NomeRG100.txt\n4) NomeRG1K.txt\n5) NomeRG10K.txt\n6) NomeRG1M.txt\n7) NomeRG100M.txt\n\n");
  printf("Opção de arquivo desejado: \n");
  scanf("%d", &numero_arquivo);

  switch(numero_arquivo)
  {
  case 1:
    nome_arquivo = "NomeRG10.txt";
    break;

  case 2:
    nome_arquivo = "NomeRG50.txt";
    break;

  case 3:
    nome_arquivo = "NomeRG100.txt";
    break;

  case 4:
    nome_arquivo = "NomeRG1K.txt";
    break;

  case 5:
    nome_arquivo = "NomeRG10K.txt";
    break;

  case 6:
    nome_arquivo = "NomeRG1M.txt";
    break;

  case 7:
    nome_arquivo = "NomeRG100M.txt";
    break;
  }
  system("clear");

  return nome_arquivo;
}

int main ()
{
  char *nome_arquivo = opcoes_arquivos();
  int option;

  printf("Arquivo Escolhido: %s\n\n", nome_arquivo);
  printf("Selecione entre os tipos de lista: \n\n");
  printf("1) Lista Sequencial\t2) Lista Encadeada\n\n");
  printf("Opção de lista desejada: \n");
  scanf("%d", &option);

  switch (option)
  {
    case 1:
      system("clear");
      printf("Lista sequencial de %s:\n", nome_arquivo);
      sequencial(abrir_aquivo(nome_arquivo), nome_arquivo);
      break;
    
    case 2:
      system("clear");
      printf("Lista encadeada de %s:\n", nome_arquivo);
      encadeada(abrir_aquivo(nome_arquivo));
      break;
  }  

  return 0;
}
