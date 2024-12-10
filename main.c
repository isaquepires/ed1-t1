#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Para lidar um limite máximo de tamanho do nome da pessoa */
#define TAM_NOME 10

/* Definindo as variáveis de tempo */
clock_t tempo_inicio;
clock_t tempo_fim;
double tempo_execucao;

int m = 0; // lidando com movimentações
int c = 0; // lidando com comparações

/* Definindo tipo para a lista sequencial */
typedef struct
{
  char nome[TAM_NOME];
  int rg;
} SeqPessoa;

/* Definindo tipo para a lista encadeada */
typedef struct EncPessoa
{
  char nome[TAM_NOME];
  int rg;
  struct EncPessoa *prox;
} EncPessoa;

/* Calcula e mostra o tempo de execução */
void tempo()
{ 
  tempo_execucao = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}

/* Limpando a tela, windows e linux (unix) */
void clear()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

/* Somente para exibir o texto presente no enunciado do trabalho */
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
}

void funcoes_texto_trabalho2()
{
  printf(" 8) Procurar um nó com o campo RG (busca binária).\n");
  printf(" 9) Selection Sort.\n");
  printf(" 10) Insertion-Sort\n");
  printf(" 11) Bubble-Sort\n");
  printf(" 12) Shell-Sort\n");
  printf(" 13) Quick-Sort\n");
  printf(" 14) Merge-Sort\n");
  printf(" 15) Mostrar a lista na tela.\n");
  printf(" 16) Salvar a lista em um arquivo (nome,RG).\n");
  printf(" 17) Ler a lista de um arquivo. (nome,RG) (lista)\n");
  printf(" 18) Sair do sistema.\n\n");
  printf("Opção desejada: \n");
  
}

/* Declarando o protótipo das duas funções de lista principais */
void funcoes_sequencial(SeqPessoa *lista, int *tamanho);
void funcoes_encadeada(FILE *arquivo, EncPessoa *atual, EncPessoa *inicio);

/* Para contar quantas linhas um determinado arquivo tem */
int contar_linhas(char *nome_arquivo)
{
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "r");
  m++;
  int linhas = 0;
  char caractere;
  
  /* enquanto não encontrar o fim do arquivo */
  while ((caractere = getc(arquivo)) != EOF)
  {
    c++;

    /* contando linhas a cada nova quebra de linha */
    if (caractere == '\n')
    {
      linhas++;
      c++;
    }
  }
  fclose(arquivo);

  return linhas;
}

/* Exibindo numeros de comparações e movimentações */
void numeros()
{
  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
}

/* -------------------- LISTA SEQUENCIAL - INICIO -------------------------- */

/* Sequencial - inserção de um nó no início da lista */
void inserir_inicio_sequencial(SeqPessoa *lista, int *tamanho)
{
  int i, posicao = 0;
  tempo_inicio = clock();
  m++;

  /* nova instância de pessoa */
  SeqPessoa novaPessoaSequencial;

  /* percorrendo do final para o início */
  for (i = *tamanho; i > 0; i--)
  {
    c++;

    /* deslocando os elementos para a 'direita' */
    lista[i] = lista[i - 1];
    m++;
  }
  
  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", novaPessoaSequencial.nome);
  printf("Insira o RG da pessoa (até 8 dígitos): \n");
  scanf("%d", &novaPessoaSequencial.rg);
  
  /* inserindo no início da lista */
  lista[posicao] = novaPessoaSequencial;
  m++;
  (*tamanho)++;

  tempo_fim = clock();
  printf("\nNOME: %s, RG: %d\n", novaPessoaSequencial.nome, novaPessoaSequencial.rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - inserção de um nó no fim da lista */
void inserir_fim_sequencial(SeqPessoa *lista, int *tamanho)
{
  int posicao = *tamanho;
  m++;
  tempo_inicio = clock();
  m++;
  SeqPessoa novaPessoaSequencial;

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", novaPessoaSequencial.nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &novaPessoaSequencial.rg);
  
  /* nova instância de pessoa no fim da lista */
  lista[*tamanho] = novaPessoaSequencial;
  m++;
  (*tamanho)++;
    
  tempo_fim = clock();
  m++;
  printf("\nNOME: %s, RG: %d\n", novaPessoaSequencial.nome, novaPessoaSequencial.rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - inserção de um nó na posição N */
void inserir_posicao_n_sequencial(SeqPessoa *lista, int *tamanho)
{
  int posicao;
  tempo_inicio = clock();
  m++;
  
  /* leitura de posição desejada para inserção */
  printf("Em que posição deseja inserir os novos dados? (0 a %d): \n", *tamanho);
  scanf("%d", &posicao);
  
  /* verificando se está dentro dos limites da lista */
  if (posicao < 0 || posicao > *tamanho)
  {
    c++;
    printf("Posição inválida!\n");
    return;
  }

  /* deslocando elementos para a 'direita' */
  for (int i = *tamanho; i > posicao; i--) 
  {
    c++;
    lista[i] = lista[i - 1];
    m++;
  }
  
  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", lista[posicao].nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &lista[posicao].rg);

  (*tamanho)++;
  
  tempo_fim = clock();
  m++;
  printf("\nNOME: %s, RG: %d\n", lista[posicao].nome, lista[posicao].rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - retirar nó do início da lista sequencial */
void retirar_no_inicio_sequencial(SeqPessoa *lista, int *tamanho)
{

  int posicao = 0;
  tempo_inicio = clock();
  m++;

  printf("\nNOME: %s, RG: %d\n", lista[posicao].nome, lista[posicao].rg);
  
  if (*tamanho == 0)
  {
    printf("A lista já está vazia.\n");
    c++;
    return;
  }
  
  /* Move todos os elementos para a esquerda */
  for (int i = 0; i < *tamanho - 1; i++)
  {
    c++;
    lista[i] = lista[i + 1];
    m++;
  }

  (*tamanho)--;

  tempo_fim = clock();
  m++;
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - Retirar nó do fim da lista sequencial */
void retirar_no_fim_sequencial(SeqPessoa *lista, int *tamanho)
{
  int posicao = *tamanho - 1;
  m++;

  tempo_inicio = clock();
  m++;

  if (*tamanho == 0)
  {
    printf("A lista já está vazia.\n");
    c++;
    return;
  }

  (*tamanho)--;
 
  tempo_fim = clock();
  m++;

  printf("\nNOME: %s, RG: %d\n", lista[*tamanho].nome, lista[*tamanho].rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - retirar nó na posição n da lista sequencial */
void retirar_no_posicao_n_sequencial(SeqPessoa *lista, int *tamanho)
{
  int posicao;
  tempo_inicio = clock();
  m++;

  printf("Em que posição deseja retirar o dado? (0 a %d): \n", *tamanho - 1);
  scanf("%d", &posicao);

  printf("\nNOME: %s, RG: %d\n", lista[posicao].nome, lista[posicao].rg);
  
  /* verifica entre os limites da lista */
  if (posicao < 0 || posicao >= *tamanho)
  {
    printf("Posição inválida!\n");
    c++;
    return;
  }

  tempo_inicio = clock();
  m++;
  
  /* remove o elemento na posição especificada */
  for (int i = posicao; i < *tamanho - 1; i++)
  {
    c++;

    /* move o próximo elemento para a posição atual */
    lista[i] = lista[i + 1];
    m++;
  }

  (*tamanho)--;

  tempo_fim = clock();
  m++;
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Sequencial - procurar nó com campo RG na lista Sequencial (Pesquisa Pequencial) */
void procurar_no_rg_sequencial(SeqPessoa *lista, int tamanho)
{

  int rg, posicao = 0;
  printf("Insira o RG que deseja procurar: \n");
  scanf("%d", &rg);
    
  tempo_inicio = clock();
  m++;
  
  /* percorrendo cada elemento da lista */
  for (int i = 0; i < tamanho; i++)
  {
    c++;
    posicao = i;
    m++;

    /* verifica se o rg atual é o rg procurado */
    if (lista[i].rg == rg)
    {
      c++;
      printf("Pessoa encontrada: NOME: %s, RG: %d\n", lista[i].nome, lista[i].rg);
      tempo_fim = clock();
      m++;
      numeros();
      printf("posição na lista: %d\n", posicao);
      tempo();
      return;
    }
  }
  
  tempo_fim = clock();
  m++;
  printf("RG %d não encontrado na lista.\n", rg);
  numeros();
  tempo();
}

/* Sequencial - Pesquisa Binária - Recursividade */
int busca_binaria_recursiva(SeqPessoa *lista, int inicio, int fim, int rg, int *c, int *m)
{
  /* contando ponteiro de movimentações */
  (*m)++;
    
  /* para no caso do inicio ultrapassar, não encontrou o rg procurado */
  if (inicio > fim)
  {
    /* contando ponteiro de comparações */
    (*c)++;
    return -1;
  }
    
  /* procura indice do meio da lista */
  int meio = inicio + (fim - inicio) / 2;
  (*c)++;
  (*m)++;

  /* verifica se o RG do meio é o procurado */
  if (lista[meio].rg == rg)
  {
    (*c)++;
    return meio;
  }

  /* se o RG procurado for menor, procura na metade esquerda */
  if (lista[meio].rg > rg)
  {
    (*c)++;
    return busca_binaria_recursiva(lista, inicio, meio - 1, rg, c, m);
  }

  /* senão, procura na metade direita */
  return busca_binaria_recursiva(lista, meio + 1, fim, rg, c, m);
}

/* Sequencial - procurar nó com campo RG na lista Sequencial (Pesquisa Binária) */
void procurar_no_rg_binaria(SeqPessoa *lista, int tamanho)
{
  int rg;
  printf("Insira o RG que deseja procurar: \n");
  scanf("%d", &rg);

  int c = 0, m = 0;

  tempo_inicio = clock();
  
  /* buscando rg recursivamente na lista contabilizando c e m */
  int posicao = busca_binaria_recursiva(lista, 0, tamanho - 1, rg, &c, &m);
  
  tempo_fim = clock();

  if (posicao != -1)
    printf("Pessoa encontrada: NOME: %s, RG: %d\n", lista[posicao].nome, lista[posicao].rg);
  else
  {
    printf("RG %d não encontrado na lista.\n", rg);
    exit(0);
  }

  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* SELECTION SORT - SEQUENCIAL */
void selection_sort(SeqPessoa *lista, int tamanho)
{
  int menor_rg;

  tempo_inicio = clock();
  
  /* percorre a lista para colocar os RGs em ordem */
  for (int i = 0; i < tamanho - 1; i++)
  {
    c++;

    /* assume que o menor elemento está na posição i */
    menor_rg = i;
    m++;
    
    /* procura o menor elemento no a partindo de i até o fim */
    for (int j = i + 1; j < tamanho; j++)
    {
      c++;

      /* verifica se o rg atual é menor que o menor encontrado, caso sim troca*/
      if (lista[j].rg < lista[menor_rg].rg)
      {
        c++;
        menor_rg = j;
        m++;
      }
    }
        
    /* se o menor_rg mudou, troca os elementos para colocar o menor na posição i */
    if (menor_rg != i)
    {
      c++;
      SeqPessoa temp = lista[i];
      lista[i] = lista[menor_rg];
      lista[menor_rg] = temp;
      m += 3;
    }
  }

  tempo_fim = clock();
  numeros();
  tempo();
}

/* INSERTION SORT - SEQUENCIAL */
void insertion_sort_sequencial(SeqPessoa *lista, int tamanho)
{
  tempo_inicio = clock();

  /* percorre a lista toda ordenando */
  for (int i = 1; i < tamanho; i++)
  {
    c++;

    /* rg a ser inserido na posição correta */
    SeqPessoa chave = lista[i];
    m++;

    int j = i - 1;
    m++;

    /* desloca os elementos maiores que chave para a direita */
    while (j >= 0 && lista[j].rg > chave.rg)
    {
      c++;

      lista[j + 1] = lista[j];
      m++;
      
      j--;
    }

    /* insere o elemento na posição correta */
    lista[j + 1] = chave;
    m++;
  }

  tempo_fim = clock();
  numeros();
  tempo();
}

/* BUBBLE SORT - SEQUENCIAL */
void bubble_sort_sequencial(SeqPessoa *lista, int tamanho)
{
  int trocou, i, j;
  tempo_inicio = clock();

  /* percorrendo desde o inicio da lista ate o seu fim */
  for (j = 0; j < tamanho - 1; j++)
  {
    c++;

    /* flag para verificar se houve troca */
    trocou = 0;

    /* passa comparando os elementos adjacentes */
    for (i = 0; i < tamanho - 1 - j; i++)
    {
      c++;
      
      /* se o rg atual for maior que o próximo havera troca entre eles */
      if (lista[i].rg > lista[i + 1].rg)
      {
        c++;
        SeqPessoa temp = lista[i];
        lista[i] = lista[i + 1];
        lista[i + 1] = temp;
        m+=3;

        /* marcando que houve troca */
        trocou = 1;
      }
    }
    
    /* se não houve troca, a lista já está ordenada */
    if (!trocou)
    {
      c++;
      break;
    }
  }

  tempo_fim = clock();
  numeros();
  tempo();
}

/* SHELL SORT - SEQUENCIAL */
void shell_sort_sequencial(SeqPessoa *lista, int tamanho)
{
  int h, i, j;
  SeqPessoa chave;

  tempo_inicio = clock();

  /* inicializa o intervalo como a metade do tamanho da lista */
  for (h = tamanho / 2; h > 0; h /= 2)
  {
    c++;

    /* faz o Insertion Sort para cada intervalo */
    for (i = h; i < tamanho; i++)
    {
      c++;

      chave = lista[i];
      m++;

      j = i;
      m++;

      /* move os elementos para a posição correta dentro do intervalo */
      while (j >= h && lista[j - h].rg > chave.rg)
      {
        c++;

        lista[j] = lista[j - h];
        m++;

        j -= h;
        m++;
      }

      lista[j] = chave;
      m++;
    }
  }

  tempo_fim = clock();
  numeros();
  tempo();
}

/* QUICK SORT - SEQUENCIAL - dividir, manipular e definir o pivo */
int dividir(SeqPessoa *lista, int inicio, int fim,  int *c, int *m)
{
  /* define o ultimo rg da lista como pivo */
  SeqPessoa pivo = lista[fim];
  SeqPessoa temp;
  int i = inicio, j;
  
  /* j parte percorrendo a lista */
  for (j = inicio; j < fim; j++)
  {
    (*c)++;
    
    /* compara o rg do elemento atual com o do pivo */
    if (lista[j].rg <= pivo.rg)
    {
      (*c)++;
        
      /* realiza a troca */
      temp = lista[i];
      lista[i] = lista[j];
      lista[j] = temp;
      (*m) += 3;
      
      /* o indice avanca */ 
      i += 1;
    }
  }
  
  /* quando chegar no fim da lista realiza a troca do pivo */
  temp = lista[i];
  lista[i] = lista[fim];
  lista[fim] = temp;
  (*m) += 3;

  return i;
}

/* QUICK SORT - SEQUENCIAL - ordenar recursivamente a lista */
void quicksort(SeqPessoa *lista, int inicio, int fim,  int *c, int *m)
{
  int pivo;

  /* verifica se a sublista tem mais de um rg */
  if (inicio < fim)
  {
    /* divide a lista em duas indicando o pivo */
    pivo = dividir(lista, inicio, fim, c, m);

    /* ordena sublista da esquerda */
    quicksort(lista, inicio, pivo - 1, c, m);

    /* ordena sublista da direita */
    quicksort(lista, pivo + 1, fim, c, m);
  }
}

/* QUICK SORT - SEQUENCIAL - para manipular tempo e contabilizar c e m */
void quick_sort_sequencial(SeqPessoa *lista, int tamanho)
{
  int c = 0, m = 0;
  tempo_inicio = clock();
    
  /* realiza o quicksort na lista contabilizando c e m */
  quicksort(lista, 0, tamanho - 1, &c, &m);

  tempo_fim = clock();
  printf("Número de comparações: %d\n", c);
  printf("Número de movimentações: %d\n", m);
  tempo();
}

/* Sequencial - Mostrar a lista na tela */
void mostrar_sequencial(SeqPessoa *lista, int tamanho)
{
  int contador;

  /* percorrendo e exibindo a lista inteira */
  for (contador = 0; contador < tamanho; contador++)
    printf("NOME: %s, RG: %d\n", lista[contador].nome, lista[contador].rg);
}

/* Sequencial - salvar lista sequencial em um arquivo */
void salvar_lista_sequencial(SeqPessoa *lista, int tamanho)
{
  FILE *arquivo;
  arquivo = fopen("sequencial.txt", "w");
    
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  
  /* percorre cada elemento da lista */
  for (int i = 0; i < tamanho; i++)
    fprintf(arquivo, "%s,%d\n", lista[i].nome, lista[i].rg);
    
  fclose(arquivo);
  printf("Lista salva com sucesso como 'sequencial.txt!'\n");
}

/* Sequencial - Ler a lista de um arquivo e colocar na lista */
void ler_lista_sequencial(SeqPessoa *lista, int *tamanho)
{
  /* Zerando o tamanho da lista */
  *tamanho = 0;
  FILE *arquivo = fopen("sequencial.txt", "r");
  
  /* lendo linhas que contém nomes (até 10 caracteres) e rg (8 caracteres) após a vírgula */
  while (fscanf(arquivo, "%9[^,],%d\n", lista[*tamanho].nome, &lista[*tamanho].rg) == 2)
    (*tamanho)++;

  fclose(arquivo);

  return;
}

/* Sequencial - Preparar inicializando os tipos de dados e "lendo" os arquivos */
void sequencial(FILE *arquivo, char *nome_arquivo)
{
  int tamanho = 0;
  
  /* Definindo a quantidade de linhas do arquivo para alocar memória suficiente */
  int linhas = contar_linhas(nome_arquivo);
  
  /* alocando memória suficiente para a lista baseado na quantidade de linhas */
  SeqPessoa *lista = malloc(linhas*sizeof(SeqPessoa));

  /* lendo linhas que contém nomes (até 10 caracteres) e rg (8 caracteres) após a vírgula */
  while (fscanf(arquivo, "%9[^,],%d\n", lista[tamanho].nome, &lista[tamanho].rg) == 2)
    tamanho++;

  fclose(arquivo);

  funcoes_sequencial(lista, &tamanho);

  free(lista);
}

/* Sequencial - Para o caso de decidir de qual função usar */
void funcoes_sequencial(SeqPessoa *lista, int *tamanho)
{
  int funcoes;
  while (1)
  {
    /* zerando movimentações e comparações */
    m = 0;
    c = 0;
    
    /* exibindo o menu do texto */
    funcoes_texto();
    funcoes_texto_trabalho2();

    scanf("%d", &funcoes);

    switch (funcoes)
    {
      case 1: inserir_inicio_sequencial(lista, tamanho); break;
      case 2: inserir_fim_sequencial(lista, tamanho); break;
      case 3: inserir_posicao_n_sequencial(lista, tamanho); break;
      case 4: retirar_no_inicio_sequencial(lista, tamanho); break;
      case 5: retirar_no_fim_sequencial(lista, tamanho); break;
      case 6: retirar_no_posicao_n_sequencial(lista, tamanho); break;
      case 7: procurar_no_rg_sequencial(lista, *tamanho); break;
      case 8: procurar_no_rg_binaria(lista, *tamanho); break;
      case 9: selection_sort(lista, *tamanho); break;
      case 10: insertion_sort_sequencial(lista, *tamanho); break;
      case 11: bubble_sort_sequencial(lista, *tamanho); break;
      case 12: shell_sort_sequencial(lista, *tamanho); break;
      case 13: quick_sort_sequencial(lista, *tamanho); break;
      case 14: break;
      case 15: clear(); mostrar_sequencial(lista, *tamanho); break;
      case 16: salvar_lista_sequencial(lista, *tamanho); break;
      case 17: ler_lista_sequencial(lista, tamanho); break;
      case 18: printf("Saindo...\n"); exit(0);
      default: printf("Opção inválida!\n"); break;
    }
    
    /* esperando a ação do usuário para voltar ao menu em loop */
    getchar();
    printf("\nAperte qualquer tecla para voltar ao menu principal.\n");
    getchar();
    
    clear();
  }
}

/* -------------------- LISTA SEQUENCIAL - FIM -------------------------- */
/* -------------------- LISTA ENCADEADA - INICIO ------------------------ */

/* Encadeada - Primeiro nó */
EncPessoa* criar_no(char *nome, int rg)
{
  /* alocando memória para novo nó */
  EncPessoa *nova_pessoa = (EncPessoa*)malloc(sizeof(EncPessoa));
  
  int i;

  /* copiando nomes para o novo nó */
  for (i = 0; nome[i] != '\0'; i++)
  {
    c++;
    nova_pessoa->nome[i] = nome[i];
    m++;
  }

  /* para o fim da string de nome */
  nova_pessoa->nome[i] = '\0';
  m++;

  /* atribuindo rg no campo rg */
  nova_pessoa->rg = rg;
  m++;

  /* definindo o próximo como fim da lista */
  nova_pessoa->prox = NULL;

  return nova_pessoa;
}

/* Encadeada - Liberando memória */
void libera_encadeada(EncPessoa *inicio)
{
  /* ponteiro para o inicio da lista */
  EncPessoa *atual = inicio;
  m++;
  
  /* percorre até o fim da lista */
  while (atual != NULL)
  {
    c++;
    
    /* nó atual temporariamente armazenado */
    EncPessoa *temp = atual;
    m++;
    
    /* avança para o próximo nó antes do atual */
    atual = atual->prox;
    m++;

    free(temp);
  }
}

/* Encadeada - inserção de um nó no início da lista */
void inserir_inicio_encadeada(EncPessoa **inicio, FILE *arquivo)
{
  int posicao = 0;
  tempo_inicio = clock();
  m++;

  /* alocando memória para novo nó */
  EncPessoa *nova_pessoa = (EncPessoa*)malloc(sizeof(EncPessoa));
  m++;

  printf("Insira o nome da pessoa: \n");
  scanf(" %10[^\n]", nova_pessoa->nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &nova_pessoa->rg);
  
  /* insere novo nó no início da lista */
  nova_pessoa->prox = *inicio;
  m++;
  *inicio = nova_pessoa;
  m++;
  
  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nova_pessoa->nome, nova_pessoa->rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Encadeada - inserção de um nó no fim da lista */
void inserir_fim_encadeada(EncPessoa **inicio)
{
  int posicao = 1;
  tempo_inicio = clock();
  m++;
  char nome[TAM_NOME];
  int rg;

  printf("Insira o nome da pessoa: \n");
  scanf(" %9[^\n]", nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &rg);
  
  /* criando novo nó */
  EncPessoa *novaPessoa = criar_no(nome, rg);
  m++;
  
  /* se a lista estiver vazia põe nó no início */
  if (*inicio == NULL)
  {
    c++;
    *inicio = novaPessoa;
    m++;
  }
  else
  {
    EncPessoa *atual = *inicio;
    m++;

    /* percorrendo até o último nó avançando para o próximo se houver */
    while (atual->prox != NULL)
    {
      c++;
      atual = atual->prox;
      m++;
      posicao++;
    }

    /* insere novo nó no fim da lista */
    atual->prox = novaPessoa;
    m++;
  }

  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nome, rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}  

/* Encadeada - inserção de um nó na posição N */
void inserir_posicao_n_encadeada(EncPessoa **inicio, FILE *arquivo)
{
  tempo_inicio = clock();
  m++;
  char nome[TAM_NOME];
  int rg, posicao, contador = 0;

  printf("Em que posição deseja inserir os novos dados: \n");
  scanf("%d", &posicao);
  printf("Insira o nome da pessoa: \n");
  scanf(" %9[^\n]", nome);
  printf("Insira o RG da pessoa: \n");
  scanf("%d", &rg);
  
  /* criando novo nó */
  EncPessoa *nova_pessoa = criar_no(nome, rg);
  m++;
  
  /* verficando se a posição é a inicial da lista */
  if (posicao == 0)
  {
    c++;

    /* novo nó aponta para o início */
    nova_pessoa->prox = *inicio;
    m++;
    *inicio = nova_pessoa;
    m++;

    return;
  }
  
  /* ponteiro atual para o início da lista */
  EncPessoa *atual = *inicio;
  m++;

  /* percorre a lista até a posição desejada */
  while (atual != NULL && contador < posicao - 1)
  {
    atual = atual->prox;
    m++;
    contador++;
    c++;
  }
  
  /* para caso a posição não exista */
  if (atual == NULL)
  {
    printf("Posição inválida!\n");
    c++;
    free(nova_pessoa);
    return;
  }
  
  /* insere novo nó na posição desejada para próximo e nó atual para o novo */
  nova_pessoa->prox = atual->prox;
  m++;
  atual->prox = nova_pessoa;
  m++;

  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nome, rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Encadeada - retirar nó do início da lista encadeada */
void retirar_no_inicio_encadeada(EncPessoa **inicio)
{
  char nome[TAM_NOME];
  int rg, posicao = 0;
  tempo_inicio = clock();
  m++;

  /* verificando se a lista está vazia */
  if (*inicio == NULL)
  {
    printf("A lista já está vazia.\n");
    c++;
    return;
  }
  
  /* para copiar primeiro nó para "nome" */
  for (int i = 0; i < TAM_NOME; i++)
  {
    c++;
    nome[i] = (*inicio)->nome[i];
    m++;
  }
  
  /* copiando rg para campo rg */
  rg = (*inicio)->rg;
  m++;

  /* manipulando inicio da lista para o próximo nó */
  EncPessoa *temp = *inicio;
  m++;
  *inicio = (*inicio)->prox;
  m++;

  free(temp);

  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nome, rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Encadeada - Retirar nó do fim da lista encadeada */
void retirar_no_fim_encadeada(EncPessoa **inicio)
{
  
  char nome[TAM_NOME];
  int rg, i, posicao = 1;

  tempo_inicio = clock();
  m++;

  
  /* verifica se a lista está vazia */
  if (*inicio == NULL)
  {
    printf("A lista já está vazia.\n");
    c++;
    return;
  }
  
  /* caso haja apenas um nó na lista */
  if ((*inicio)->prox == NULL)
  {
    c++;
    free(*inicio);
    *inicio = NULL;
  }
  else
  { 
    /* definindo o início da lista */
    EncPessoa *atual = *inicio;
    m++;

    /* percorre até o último nó */
    while (atual->prox->prox != NULL)
    {
      atual = atual->prox;
      m++;
      posicao++;
      c++;
    }
    
    /* armazenando o nome */
    for (i = 0; i < TAM_NOME; i++)
    {
      c++;
      nome[i] = atual->prox->nome[i];
      m++;
    }
      
    /* armazenando o rg */
    rg = atual->prox->rg;
    m++;

    free(atual->prox);
    atual->prox = NULL;
    m++;
  }

  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nome, rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Encadeada - retirar nó na posição n da lista encadeada */
void retirar_no_posicao_n_encadeada(EncPessoa **inicio) {
  
  char nome[TAM_NOME];
  int rg, i, posicao, contador = 0;

  printf("Em que posição deseja retirar o dado?: \n");
  scanf("%d", &posicao);
  
  tempo_inicio = clock();
  m++;
  
  /* verificando se a lista está vazia */
  if (*inicio == NULL)
  {
    printf("A lista já está vazia.\n");
    c++;
    return;
  }

  /* se for na posição inicial retira do início */
  if (posicao == 0)
  {
    retirar_no_inicio_encadeada(inicio);
    m++;
    return;
  }


  /* ponteiro atual no início da lista e inicialização do nó anterior */
  EncPessoa *atual = *inicio;
  m++;
  EncPessoa *anterior = NULL;
  
  /* percorre a lista até a posição desejada ou até o final */
  while (atual != NULL && contador < posicao)
  {
    anterior = atual;
    m++;
    atual = atual->prox;
    m++;
    contador++;
    c++;
  }
  
  /* verificando se a posição está nos limites da lista */
  if (atual == NULL)
  {
    printf("Posição inválida!\n");
    c++;
    return;
  }
  
  /* armazenando dados nome e rg */
  for (int i = 0; i < TAM_NOME; i++)
  {
    c++;
    nome[i] = atual->nome[i];
    m++;
  }
  
  /* inserindo rg no campo rg */
  rg = atual->rg;
  m++;
  
  /* desconecta o nó atual da lista */
  anterior->prox = atual->prox;
  m++;
  free(atual);

  tempo_fim = clock();
  m++;
  printf("NOME: %s, RG: %d\n", nome, rg);
  numeros();
  printf("posição na lista: %d\n", posicao);
  tempo();
}

/* Encadeada - procurar nó com campo RG na lista encadeada */
void procurar_no_rg_encadeada(EncPessoa *inicio)
{
  int rg, posicao;
  printf("Digite o RG que deseja procurar: \n");
  scanf("%d", &rg);

  tempo_inicio = clock();
  m++;

  /* definindo o início da lista */
  EncPessoa *atual = inicio;
  m++;
  
  /* perrendo cada elemtento (posição) da lista */
  for (posicao = 0; atual != NULL; posicao++)
  {
    c++;

    /* verifica se o rg atual é o procurado */
    if (atual->rg == rg)
    {
      c++;
      tempo_fim = clock();
      m++;
      printf("Pessoa encontrada: NOME: %s, RG: %d\n", atual->nome, atual->rg);
      numeros();
      printf("posição na lista: %d\n", posicao);
      tempo();
      return;
    }
    atual = atual->prox;
    m++;
  }
    
  printf("Pessoa com RG: %d não encontrada.\n", rg);
  tempo_fim = clock();
  m++;
  numeros();
  tempo();
}

/* Encadeada - Mostrar a lista na tela */
void mostrar_encadeada(EncPessoa *atual)
{
  /* percorrendo e exibindo a lista até o final dela */
  while (atual != NULL)
  {
    printf("NOME: %s, RG: %d\n", atual->nome, atual->rg);
    atual = atual->prox;
  }
}

/* Encadeada - salvar lista encadeada em um arquivo */
void salvar_lista_encadeada(EncPessoa *inicio) {
  FILE *arquivo;
  arquivo = fopen("encadeada.txt", "w");
    
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  
  /* Definindo o início da lista */
  EncPessoa *atual = inicio;

  /* Enquanto não chegar no fim da lista */
  while (atual != NULL)
  {
    /* escreve no arquivo linha por linha no formato nome,rg */
    fprintf(arquivo, "%s,%d\n", atual->nome, atual->rg);
    atual = atual->prox;
  }
    
  fclose(arquivo);
  printf("Lista salva com sucesso em encadeada.txt!\n");
}

void ler_lista_encadeada(EncPessoa **inicio)
{
  /* inicialização dos ponteiros das extremidades */
  *inicio = NULL;
  EncPessoa *ultimo = NULL;

  FILE *arquivo = fopen("encadeada.txt", "r");

  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  char nome[TAM_NOME];
  int rg;

  /* lendo linhas que contém nomes (até 10 caracteres) e rg (8 caracteres) após a vírgula */
  while (fscanf(arquivo, "%9[^,],%d\n", nome, &rg) == 2)
  {
    /* criando novo nó */
    EncPessoa *novaPessoa = criar_no(nome, rg);
  
    /* se a lista estiver vazia define nó como início, senão conecta último nó ao próximo */
    if (*inicio == NULL)
      *inicio = novaPessoa;
    else
      ultimo->prox = novaPessoa;
    
    /* atualiza ponteiro para o último nó */
    ultimo = novaPessoa;
  }

  fclose(arquivo);
}

/* Encadeda - Preparar inicializando os tipos de dados e "lendo" os arquivos */
void encadeada(FILE *arquivo)
{
  /* inicializando primeiro e último nó */
  EncPessoa *inicio = NULL, *ultimo = NULL;
  
  char nome[TAM_NOME];
  int rg;
  
  /* enquanto está lendo linhas que contém nomes (até 10 caracteres) e rg (8 caracteres) após a vírgula */
  while (fscanf(arquivo, "%9[^,],%d\n", nome, &rg) == 2)
  {
    /* criando novo nó */
    EncPessoa *nova_pessoa = criar_no(nome, rg);
    
    /* se a lista estiver vazia define nó como início, senão conecta último nó ao próximo */
    if (inicio == NULL)
      inicio = nova_pessoa;
    else
      ultimo->prox = nova_pessoa;
    
    /* atualiza ponteiro para o último nó */
    ultimo = nova_pessoa;
  }

  fclose(arquivo);
  
  /* definindo o início da lista */
  EncPessoa *atual = inicio;
    
  funcoes_encadeada(arquivo, atual, inicio);

  libera_encadeada(inicio);
}

/* Encadeada - Para o caso de decidir de qual função usar */
void funcoes_encadeada(FILE *arquivo, EncPessoa *atual, EncPessoa *inicio)
{
  int funcoes;

  while (1)
  {
    /* zerando movimentações e comparações */
    m = 0;
    c = 0;

    /* exibindo o menu do texto */
    funcoes_texto();
    printf(" 8) Mostrar a lista na tela.\n");
    printf(" 9) Salvar a lista em um arquivo (nome,RG).\n");
    printf("10) Ler a lista de um arquivo. (nome,RG) (lista)\n");
    printf("11) Sair do sistema.\n\n");
    printf("Opção desejada: \n");

    scanf("%d", &funcoes);

    switch (funcoes)
    {
      case 1: inserir_inicio_encadeada(&inicio, arquivo); break;
      case 2: inserir_fim_encadeada(&inicio); break;
      case 3: inserir_posicao_n_encadeada(&inicio, arquivo); break;
      case 4: retirar_no_inicio_encadeada(&inicio); break;
      case 5: retirar_no_fim_encadeada(&inicio); break;
      case 6: retirar_no_posicao_n_encadeada(&inicio); break;
      case 7: procurar_no_rg_encadeada(inicio); break;
      case 8: clear(); mostrar_encadeada(inicio); break;
      case 9: salvar_lista_encadeada(inicio); break;
      case 10: ler_lista_encadeada(&inicio); break;
      case 11: printf("Saindo...\n"); exit(0);
      default: printf("Opção inválida!\n"); break;
    }

    /* esperando a ação do usuário para voltar ao menu em loop */
    getchar();
    printf("\nAperte qualquer tecla para voltar ao menu principal.\n");
    getchar();
    
    clear();
  }
}

/* -------------------- LISTA ENCADEADA - FIM --------------------------- */

/* Abrindo arquivo texto... */
FILE *abrir_aquivo(char *nome_arquivo)
{
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "r");
  return arquivo;
}

/* Para o caso de decidir de qual arquivo usar */
char* opcoes_arquivos()
{
  char *nome_arquivo = NULL;
  int numero_arquivo;
  printf("Selecione entre os arquivos abaixo: \n\n");
  printf("1) NomeRG10.txt\n2) NomeRG50.txt\n3) NomeRG100.txt\n4) NomeRG1K.txt\n5) NomeRG10K.txt\n6) NomeRG1M.txt\n7) NomeRG100M.txt\n8) Sair do sistema\n\n");
  printf("Opção de arquivo desejado: \n");
  scanf("%d", &numero_arquivo);

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

/* Fazendo a execução "morrer", exibindo mensagem de erro e de uso */
int die(char *mensagem)
{
  printf("%s\n", mensagem);
  printf("Uso: programa [ sequencial(s*) | encadeada(e*) ].\n");
  exit(1);
}

/* Função principal e seus parametros */
int main(int argc, char *argv[]) {
  char *nome_arquivo = NULL;

  /* O argumento é sempre o segundo elemento, o "1" */
  char *tipo_lista = argv[1];
  
  /* Manipulando erros de argumentos */
  if (argc == 1)
    die("Não há argumentos, é preciso especificar o tipo de lista!");
  else if (argc > 2)
    die("Há argumentos demais, use apenas um argumento por vez!");
    
  /* Selecionando o primeiro caractere do argumento como tipo de lista escolhida */
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
      die("Argumentos inválido!");
  }

  return 0;
}

