#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//definem  constantes
#define MAX_STRING 150        
#define MAX_MOVIES 5

//é uma estrutura de dados
typedef struct {
  char title[MAX_STRING];
  int releaseDate;
  char director[MAX_STRING];
  char genre[MAX_STRING];
  float rating;
  int avaiability;
  char code[MAX_STRING];
} Movie;
//nome/tipo dessa estrutura

//vetor que amarzenará os filmes
Movie movies[MAX_MOVIES];

//contador que será usado para dimensionar o vetor de filmes
int totalMovies = 0;     
void flush();

//função de cadastro dos filmes
Movie registerMovie() {       
  printf("- - - - Cadastro de Filme - - - -\n");

  Movie m;
  printf("Titulo do filme: ");
  //salva uma string com espaço. fgets(variável string, tamanho, stdin)
  fgets(m.title, MAX_STRING, stdin);
  m.title[strcspn(m.title, "\n")] = '\0';
        
  printf("Diretor: ");
  fgets(m.director, MAX_STRING, stdin);
  m.director[strcspn(m.director, "\n")] = '\0';
        
  printf("Genero: ");
  fgets(m.genre, MAX_STRING, stdin);
  m.genre[strcspn(m.genre, "\n")] = '\0';
    
  printf("Ano de lancamento: ");
  scanf("%d", &m.releaseDate);
  flush();
    
  printf("Avaliacao: ");
  scanf("%f", &m.rating);
  flush();

  printf("Disponibilidade: ");
  scanf("%d", &m.avaiability);
  flush();

  printf("Codigo do filme: ");
  scanf("%s", &m.code);
  printf("\n");
  
  printf("Filme registrado!\n");
  printf("\n");
    
  return m;
}


//função que mostra os filmes cadastrados
void showMovies() {
  printf("- - - - Filmes Cadastrados - - - -\n");
        
  for(int i = 0; i < totalMovies; i++) {
    printf("Filme %d\n", i + 1);
    printf("Titulo: %s\n", movies[i].title);
    printf("Diretor: %s\n", movies[i].director);
    printf("Genero: %s\n", movies[i].genre);
    printf("Ano de Lancamento: %d\n", movies[i].releaseDate);
    printf("Avaliacao: %.2f\n", movies[i].rating);
    printf("Disponibilidade: %d\n", movies[i].avaiability);
    printf("Codigo do filme: %s\n", movies[i].code);
    printf("\n");
  }
}


//função que procura e mostra os dados de um filme pelo nome
void searchMovie(char name[MAX_STRING], Movie movies[MAX_MOVIES]) {                
  for(int i = 0; i < totalMovies; i++) {
    Movie aux = movies[i];
    //função que  compara duas strings. strcmp(string1, string2)
    int result = strcmp(name, aux.title);
    
    if(result == 0) {
      printf("Ano de Lancamento: %d\n", aux.releaseDate);
      printf("Diretor: %s\n", aux.director);
      printf("Genero: %s\n", aux.genre);
      printf("Avaliacao: %.2f\n", aux.rating);
      printf("Disponibilidade: %d\n", aux.avaiability);
      printf("Codigo do filme: %s\n", aux.code);
      printf("\n");
      return;
    }
  }
  printf("\nFilme nao encontrado!\n");
  printf("\n");
}


void deleteMovie(char name[MAX_STRING], Movie movies[MAX_MOVIES]) {
  int indexMovie;
  for(int i = 0; i < MAX_MOVIES; i++) {
    Movie aux = movies[i];
    int result = strcmp(name, aux.title);
      
    if(result == 0) {
      indexMovie = i;

      if(indexMovie == totalMovies + 1) {
        for(int j = indexMovie; j > 0; j--)
          movies[j] = movies[j - 1];
        
        totalMovies--;
      }

      for(int k = indexMovie; k < totalMovies; k++)
        movies[k] = movies[k + 1];
      
      totalMovies--;
      printf("\nFilme deletado!\n");
      printf("\n");
    }
  }
}


//função para salvar os filmes
void saveMovies() { 
  //declarar uma variável FILE com um ponteiro que aponta para um arquivo "nome"
  FILE *file;
  //a função fopen faz com que o ponteiro aponte para um arquivo . fopen("Endereço onde o arquivo será salvo, "nome do arquivo.txt", comando a ser executado "w, r, a")
  file = fopen("Filmes.txt", "w");        

  for(int i = 0; i < totalMovies; i++) {
    //função que escreve dentro do arquivo. fprintf(ponteiro, "mensagem").
    fprintf(file, "{ \"%s\", %d, \"%s\", \"%s\", %.2f, %d, \"%s\" }\n",       
            movies[i].title,
            movies[i].releaseDate,
            movies[i].director,
            movies[i].genre,
            movies[i].rating,
            movies[i].avaiability,
            movies[i].code);
  }

  //fclose serve para fechar o arquivo associado
  fclose(file);     
  printf("Filme(s) salvo(s) com sucesso!\n");
  printf("\n");
}


//função que carrega os filmes
void loadMovies() {       
  FILE *file;
  file = fopen("Filmes.txt", "r");

  if(file == NULL) {
    printf("Erro ao carregar!\n");
    printf("\n");
    return;
  }
  else {
    printf("Arquivo carregado com sucesso!\n");
    printf("\n");
    while(fscanf(file, "{ \"%[^\"]\", %d, \"%[^\"]\", \"%[^\"]\", %f, %d, \"%[^\"]\" }\n",
          //função que escaneia um arquivo. fscanf(ponteiro, "variaveis", alocação)
          movies[totalMovies].title,
          &movies[totalMovies].releaseDate,
          movies[totalMovies].director,
          movies[totalMovies].genre,
          &movies[totalMovies].rating,
          &movies[totalMovies].avaiability,
          movies[totalMovies].code) != EOF) {
            totalMovies++;
          //EOF é uma condição do SO, atingida quando não há mais dados a serem lidos
    }
  }
  fclose(file);
}


//função para imprimir a data de aluguel. É um extra
void rentalTime() {
  struct tm *date_time;
  time_t seconds;
  time(&seconds);
  date_time = localtime(&seconds);

  printf("Hora: %d:%d:%d\n", date_time->tm_hour, date_time->tm_min, date_time->tm_sec);
  printf("Data: %d/%d/%d\n", date_time->tm_mday, date_time->tm_mon + 1, date_time->tm_year + 1900);
}


//função para imprimir a data de devolução
void devolutionTime() {
  struct tm *date_time;
  time_t seconds;
  time(&seconds);
  date_time = localtime(&seconds);

  printf("Data: %d/%d/%d\n", date_time->tm_mday + 3, date_time->tm_mon + 1, date_time->tm_year + 1900);
}


//função para alugar um filme
void rentMovie(Movie movies[MAX_MOVIES]) {
  printf("- - - - Aluguel de Filme - - - -\n");

  char request[MAX_STRING];
  printf("Titulo do filme: ");
  fgets(request, MAX_STRING, stdin);
  request[strcspn(request, "\n")] = '\0';
  
  int result, demandQtt;
  for(int i = 0; i < totalMovies; i++) {
    Movie aux = movies[i];
    result = strcmp(request, aux.title);
    if(result == 0) {
      printf("Quantidade: ");
      scanf("%d", &demandQtt);

      if(demandQtt > aux.avaiability) {
        printf("\nQuantidade insuficiente disponivel!\n");
        printf("\n");
        return;
      }
      else {
        movies[i].avaiability = movies[i].avaiability - demandQtt;
        printf("\nFilme alugado com sucesso!\n");
        printf("\n");

        printf("- - - - Recibo de Aluguel - - - -\n");
        printf("Filme: %s\n", request);
        printf("Codigo do filme: %s\n", aux.code);
        printf("Quantidade: %d\n", demandQtt);
        printf("Valor a ser pago: R$ %d,00\n", demandQtt * 10);
        rentalTime();
        printf("\n");
        printf("Devolucao:\n");
        devolutionTime();
        printf("\n");
        printf("Observacoes:\n");
        printf("Multa para cada dia de atraso no valor de R$2,00.\n");
        printf("A partir da data de recebimento, o cliente tem ate 3 dias para devolver o filme sem multa.\n");
        printf("A integridade deste filme, bem como o compromisso de devolve-lo e de responsabilidade\ndo cliente, bem como o pagamento de multa em eventuais atrasos, danos ou perda.\n");
        printf("\n");
      }
      break;
    }
  }
  if(result != 0) {
    printf("\nFilme nao encontrado/disponivel!\n");
    printf("\n");
    return;
  }
}


//função para limpar a entrada padrão <stdin>
void flush() {        
  while(getchar() != '\n');
}


int main() {
  int option;
  char name[MAX_STRING];

  //nesse caso é mais coveniente usar "do while" ao invés de "for"
  do {
    printf("- - - - MEGA VIDEO - - - -\n");
    printf("Opcoes:\n1. Cadastrar filme\n2. Ver filmes cadastrados\n3. Ver dados de um filme\n4. Excluir um filme\n5. Salvar\n6. Carregar\n7. Alugar e emitir comprovante de aluguel\n8. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &option);
    flush();
    printf("\n");
        
    switch(option) {
      case 1:
        if(totalMovies < MAX_MOVIES) {
          movies[totalMovies] = registerMovie();
          totalMovies++;
          printf("Total cadastrado: %d/%d\n", totalMovies, MAX_MOVIES);
          printf("\n");
        }
        else {
            printf("Quantidade maxima cadastrada! (%d/%d)\n", totalMovies, MAX_MOVIES);
            printf("\n");
          }
        break;
      case 2:
        if(totalMovies == 0) {
           printf("Nenhum filme cadastrado!\n");
           printf("\n");
        }
        else
          showMovies();
        break;
      case 3:
        if(totalMovies == 0) {
          printf("Nenhum filme cadastrado!\n");
          printf("\n");
        }
        else {
          printf("Filme: ");
          fgets(name, MAX_STRING, stdin);
          name[strcspn(name, "\n")] = '\0';
          searchMovie(name, movies);
        }
        break;
      case 4:
        if(totalMovies == 0) {
          printf("Nenhum filme cadastrado!\n");
          printf("\n");
        }
        else {
          printf("Filme: ");
          fgets(name, MAX_STRING, stdin);
          name[strcspn(name, "\n")] = '\0';
          deleteMovie(name, movies);
        }
        break;
      case 5:
        if(totalMovies == 0) {
          printf("Erro! Nao foi possivel salvar\n");
          printf("\n");
        }
        else
          saveMovies();
        break;
      case 6:
        loadMovies();
        break;
      case 7:
        if(totalMovies == 0) {
          printf("Erro! Nao foi possivel alugar!\n");
          printf("\n");
        }
        else
          rentMovie(movies);
        break;
      case 8:
        printf("Obrigado por alugar na MEGA VIDEO!\n");
        printf("Horario de funcioamento:\nSEG a SEX, das 13:00 as 21:00\nSAB e DOM de 13:00 as 17:00\n");
        printf("\n");
        printf("Saindo...\n");
        break;
      default:
        printf("Opcao invalida!\n");
        printf("\n");
    }
  } while(option != 8);
  return 0;
}
