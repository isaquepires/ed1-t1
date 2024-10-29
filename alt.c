#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_NOME 10

clock_t tempo_inicio;
clock_t tempo_fim;
int m = 0;
int c = 0;
double tempo_execucao;

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

void tempo()
{
  tempo_execucao = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}


void clear()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void funcoes_texto()
{
  printf("Selecione entre as funções abaixo: \n\n");
  printf(" 1) Inserção de um nó no início da lista.\n");
  printf(" 2) Inserção de um nó no fim da lista.\n");
  printf(" 3) Inserção de um nó na posição N.\n");
  printf(" 4) Retirar um nó do início da lista.\n");
  printf(" 5) Retirar um nó no fim da lista.\n");
  printf(" 6) Retirar um nó na posição N.\n");
  printf(" 7) Procurar um nó com o campo RG (busca sequencial).\n");
  printf(" 8) Mostrar a lista na tela.\n");
  printf(" 9) Salvar a lista em um arquivo (nome,RG).\n");
  printf("10) Ler a lista de um arquivo. (nome,RG) (lista)\n");
  printf("11) Sair do sistema.\n\n");
  printf("Opção desejada: \n");
}

void funcoes_sequencial(SeqPessoa *lista, int dados);
int contar_linhas(char *nome_arquivo);
void inserir_inicio_sequencial(SeqPessoa *lista, int tamanho);
void mostrar_sequencial(SeqPessoa *lista, int tamanho);
void sequencial(FILE *arquivo, char *nome_arquivo);
EncPessoa* criar_no(char *nome, int rg);
void libera_encadeada(EncPessoa *inicio);
void inserir_inicio_encadeada(EncPessoa **inicio,  FILE *arquivo);
void mostrar_encadeada(FILE *arquivo, EncPessoa *atual);
void encadeada(FILE *arquivo);
void funcoes_encadeada(FILE *arquivo, EncPessoa *atual, EncPessoa *inicio);
void inserir_posicao_n_sequencial(SeqPessoa *lista, int tamanho);

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

void inserir_inicio_sequencial(SeqPessoa *lista, int tamanho)
{
  tempo_inicio = clock();
  m++;

  SeqPessoa novaPessoaSequencial;

  for (int i = tamanho; i > 0; i--)
  {
    lista[i] = lista[i - 1];
    m++;
  }

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", novaPessoaSequencial.nome);
  printf("Insira o RG da pessoa (até 8 dígitos): \n");
  scanf("%d", &novaPessoaSequencial.rg);
  
  lista[0] = novaPessoaSequencial;
  tamanho++;
  m++;

  tempo_fim = clock();
  m++;
  
  printf("NOME: %s, RG: %d\n", novaPessoaSequencial.nome, novaPessoaSequencial.rg);
  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
  tempo();
}

void inserir_fim_sequencial(SeqPessoa *lista, int tamanho)
{
  SeqPessoa novaPessoaSequencial;

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", novaPessoaSequencial.nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &novaPessoaSequencial.rg);
  
  lista[tamanho] = novaPessoaSequencial;
  tamanho++;
  m++;
  
  printf("NOME: %s, RG: %d\n", novaPessoaSequencial.nome, novaPessoaSequencial.rg);
  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
  tempo();
}

void inserir_posicao_n_sequencial(SeqPessoa *lista, int tamanho)
{
  int posicao;

  printf("Em que posição deseja inserir os novos dados? (0 a %d): \n", tamanho);
  scanf("%d", &posicao);
  if (posicao < 0 || posicao > tamanho) {
    printf("Posição inválida!\n");
    return;
  }

  for (int i = tamanho; i > posicao; i--) {
    lista[i] = lista[i - 1];
    m++;
  }

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", lista[posicao].nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &lista[posicao].rg); 
  tamanho++;

  mostrar_sequencial(lista, tamanho);

}

void mostrar_sequencial(SeqPessoa *lista, int tamanho)
{
  int contador;
  for (contador = 0; contador < tamanho; contador++)
    printf("NOME: %s, RG: %d\n", lista[contador].nome, lista[contador].rg);
}

void sequencial(FILE *arquivo, char *nome_arquivo)
{
  int tamanho = 0;

  int linhas = contar_linhas(nome_arquivo);
  
  SeqPessoa *lista = malloc(linhas*sizeof(SeqPessoa));

  while (fscanf(arquivo, "%9[^,],%d\n", lista[tamanho].nome, &lista[tamanho].rg) == 2)
    tamanho++;

  fclose(arquivo);

  funcoes_sequencial(lista, tamanho);

  free(lista);
}

void funcoes_sequencial(SeqPessoa *lista, int tamanho)
{
  int funcoes;
  funcoes_texto();
  scanf("%d", &funcoes);

  switch (funcoes) {
    case 1: inserir_inicio_sequencial(lista, tamanho); break;
    case 2: inserir_fim_sequencial(lista, tamanho); break;
    case 3: inserir_posicao_n_sequencial(lista, tamanho); break;
    case 4: break;
    case 5: break;
    case 6: break;
    case 7: break;
    case 8: clear(); mostrar_sequencial(lista, tamanho); break;
    case 9: break;
    case 10: break;
    case 11: printf("Saindo...\n"); exit(0);
    default: printf("Opção inválida!\n"); break;
  }
}

EncPessoa* criar_no(char *nome, int rg)
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

void inserir_inicio_encadeada(EncPessoa **inicio, FILE *arquivo)
{
  tempo_inicio = clock();
  EncPessoa *nova_pessoa = (EncPessoa*)malloc(sizeof(EncPessoa));
  
  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", nova_pessoa->nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &nova_pessoa->rg);

  nova_pessoa->prox = *inicio;
  *inicio = nova_pessoa;
  
  printf("NOME: %s, RG: %d\n", nova_pessoa->nome, nova_pessoa->rg);
  
  free(nova_pessoa);
  tempo_fim = clock();
  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
  tempo();
}

void inserir_fim_encadeada(EncPessoa **inicio)
{
  char nome[10];
  int rg;

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &rg);

  EncPessoa *novaPessoa = criar_no(nome, rg);

  if (*inicio == NULL)
    *inicio = novaPessoa;
  else
  {
    EncPessoa *atual = *inicio;
    while (atual->prox != NULL)
      atual = atual->prox;

    atual->prox = novaPessoa;
  }

  printf("NOME: %s, RG: %d\n", nome, rg);
}

void inserir_posicao_n_encadeada(EncPessoa **inicio, FILE *arquivo)
{
  char nome[10];
  int rg, posicao;

  printf("Em que posição deseja inserir os novos dados: \n");
  scanf("%d", &posicao);
  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &rg);

  EncPessoa *nova_pessoa = criar_no(nome, rg);

  if (posicao == 0) {
    nova_pessoa->prox = *inicio;
    *inicio = nova_pessoa;
    m++;
    return;
  }

  EncPessoa *atual = *inicio;
  int contador = 0;

  while (atual != NULL && contador < posicao - 1) {
    atual = atual->prox;
    contador++;
    c++;
  }

  if (atual == NULL) {
    printf("Posição inválida!\n");
    free(nova_pessoa);
    return;
  }

  nova_pessoa->prox = atual->prox;
  atual->prox = nova_pessoa;

  printf("NOME: %s, RG: %d\n", nome, rg);
  //mostrar_encadeada(arquivo, *inicio);
}

void mostrar_encadeada(FILE *arquivo, EncPessoa *atual)
{
  while (atual != NULL) {
    printf("NOME: %s, RG: %d\n", atual->nome, atual->rg);
    atual = atual->prox;
  }
}

void encadeada(FILE *arquivo)
{
  EncPessoa *inicio = NULL, *ultimo = NULL;
  
  char nome[TAM_NOME];
  int rg;

  while (fscanf(arquivo, "%9[^,],%d\n", nome, &rg) == 2)
  {
    EncPessoa *nova_pessoa = criar_no(nome, rg);
  
    if (inicio == NULL)
      inicio = nova_pessoa;
    else
      ultimo->prox = nova_pessoa;

    ultimo = nova_pessoa;
  }

  fclose(arquivo);

  EncPessoa *atual = inicio;
    
  funcoes_encadeada(arquivo, atual, inicio);

  libera_encadeada(inicio);
}

void funcoes_encadeada(FILE *arquivo, EncPessoa *atual, EncPessoa *inicio)
{
  int funcoes;
  funcoes_texto();
  scanf("%d", &funcoes);
  //EncPessoa *inicio = NULL;

  switch (funcoes) {
    case 1: inserir_inicio_encadeada(&inicio, arquivo); break;
    case 2: inserir_fim_encadeada(&inicio); break;
    case 3: inserir_posicao_n_encadeada(&inicio, arquivo); break;
    case 4: break;
    case 5: break;
    case 6: break;
    case 7: break;
    case 8: clear(); mostrar_encadeada(arquivo, atual); break;
    case 9: break;
    case 10: break;
    case 11: printf("Saindo...\n"); exit(0);
    default: printf("Opção inválida!\n"); break;
  }
}

FILE *abrir_aquivo(char *nome_arquivo)
{
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "r");
  return arquivo;
}

char* opcoes_arquivos()
{
  char *nome_arquivo = NULL;
  int numero_arquivo;
  printf("Selecione entre os arquivos abaixo: \n\n");
  printf("1) NomeRG10.txt\n2) NomeRG50.txt\n3) NomeRG100.txt\n4) NomeRG1K.txt\n5) NomeRG10K.txt\n6) NomeRG1M.txt\n7) NomeRG100M.txt\n8) Sair do sistema\n\n");
  printf("Opção de arquivo desejado: \n");
  scanf("%d", &numero_arquivo);

  /* Limpando o input buffer para evitar
  os erros com o uso de caracteres extras */
  //while (getchar() != '\n');

  switch (numero_arquivo)
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
    case 8:
      printf("Saindo...\n");
      exit(0);
    default:
      printf("Opção inválida!\n");
      exit(1);
  }
  
  clear();

  return nome_arquivo;
}

int main(int argc, char *argv[]) {
  char *nome_arquivo = NULL;
  char *tipo_lista = argv[1];

  if (argc == 1)
  {
    printf("Não há argumentos, é preciso especificar o tipo de lista!\n");
    printf("Uso: programa [ sequencial(e*) | encadeada(e*) ].\n");
    return 1;
  }
  else if (argc > 2)
  {
    printf("Há argumentos demais, use apenas um argumento por vez!\n");
    printf("Uso: programa [ sequencial(e*) | encadeada(e*) ].\n");
    return 1;
  }
    
  /* Selecionando o primeiro caractere do argumento */
  switch (tipo_lista[0])
  {
    /* Para a lista sequencial */
    case 's':
      clear();
      printf("Lista SEQUENCIAL\n");
      nome_arquivo = opcoes_arquivos();
      printf("Lista SEQUENCIAL de %s...\n", nome_arquivo);
      sequencial(abrir_aquivo(nome_arquivo), nome_arquivo);
      break;
    /* Para a lista encadeada */
    case 'e':
      clear();
      printf("Lista ENCADEADA\n");
      nome_arquivo = opcoes_arquivos();
      printf("Lista ENCADEADA de %s...\n", nome_arquivo);
      encadeada(abrir_aquivo(nome_arquivo));
      break;
    /* Para qualquer outro argumento */
    default:
      printf("Argumentos inválido!\n");
      printf("Uso: programa [ sequencial(e*) | encadeada(e*) ].\n");
      return 1;
  }

  return 0;
}

