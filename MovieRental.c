#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_STRING 150        
#define MAX_MOVIES 5


typedef struct{
  char title[MAX_STRING];
  int releaseDate;
  char director[MAX_STRING];
  char genre[MAX_STRING];
  float rating;
  int avaiability;
  char code[MAX_STRING];
}Movie;


Movie movies[MAX_MOVIES];
int totalMovies = 0;     
void flush();


Movie registerMovie(){       
  printf("- - - - Movie Registration - - - -\n");

  Movie m;
  printf("Movie title: ");
  fgets(m.title, MAX_STRING, stdin);
  m.title[strcspn(m.title, "\n")] = '\0';
        
  printf("Director: ");
  fgets(m.director, MAX_STRING, stdin);
  m.director[strcspn(m.director, "\n")] = '\0';
        
  printf("Genre: ");
  fgets(m.genre, MAX_STRING, stdin);
  m.genre[strcspn(m.genre, "\n")] = '\0';
    
  printf("Release date: ");
  scanf("%d", &m.releaseDate);
  flush();
    
  printf("Rating: ");
  scanf("%f", &m.rating);
  flush();

  printf("Avaiability: ");
  scanf("%d", &m.avaiability);
  flush();

  printf("Movie code: ");
  scanf("%s", &m.code);
  printf("\n");
  
  printf("Movie registered!\n\n");
  return m;
}


void showMovies(){
  printf("- - - - Movies Registered - - - -\n");
        
  for(int i = 0; i < totalMovies; i++) {
    printf("Movie %d\n", i + 1);
    printf("Title: %s\n", movies[i].title);
    printf("Director: %s\n", movies[i].director);
    printf("Genre: %s\n", movies[i].genre);
    printf("Release date: %d\n", movies[i].releaseDate);
    printf("Rating: %.2f\n", movies[i].rating);
    printf("Avaiability: %d\n", movies[i].avaiability);
    printf("Movie code: %s\n", movies[i].code);
    printf("\n");
  }
}


void searchMovie(char name[MAX_STRING], Movie movies[MAX_MOVIES]){                
  for(int i = 0; i < totalMovies; i++){
    Movie aux = movies[i];
    int result = strcmp(name, aux.title);
    
    if(result == 0){
      printf("Release date: %d\n", aux.releaseDate);
      printf("Director: %s\n", aux.director);
      printf("Genre: %s\n", aux.genre);
      printf("Rating: %.2f\n", aux.rating);
      printf("Avaiability: %d\n", aux.avaiability);
      printf("Movie code: %s\n", aux.code);
      return;
    }
  }
  printf("\nMovie not found!\n");
}


void deleteMovie(char name[MAX_STRING], Movie movies[MAX_MOVIES]){
  int indexMovie;
  for(int i = 0; i < MAX_MOVIES; i++) {
    Movie aux = movies[i];
    int result = strcmp(name, aux.title);
      
    if(result == 0){
      indexMovie = i;

      if(indexMovie == totalMovies + 1){
        for(int j = indexMovie; j > 0; j--)
          movies[j] = movies[j - 1];
        
        totalMovies--;
      }

      for(int k = indexMovie; k < totalMovies; k++)
        movies[k] = movies[k + 1];
      
      totalMovies--;
      printf("\nMovie deleted!\n");
    }
  }
}


void saveMovies(){ 
  FILE *file;
  file = fopen("Movies.txt", "w");        

  for(int i = 0; i < totalMovies; i++){
    fprintf(file, "{ \"%s\", %d, \"%s\", \"%s\", %.2f, %d, \"%s\" }\n",       
            movies[i].title,
            movies[i].releaseDate,
            movies[i].director,
            movies[i].genre,
            movies[i].rating,
            movies[i].avaiability,
            movies[i].code);
  }
  fclose(file);     
  printf("Movie(s) saved sucessfully!\n");
}


void loadMovies(){       
  FILE *file;
  file = fopen("Movies.txt", "r");

  if(file == NULL){
    printf("Loading error!\n");
    return;
  }
  else {
    printf("File loaded sucessfully!\n");
    while(fscanf(file, "{ \"%[^\"]\", %d, \"%[^\"]\", \"%[^\"]\", %f, %d, \"%[^\"]\" }\n",
          movies[totalMovies].title,
          &movies[totalMovies].releaseDate,
          movies[totalMovies].director,
          movies[totalMovies].genre,
          &movies[totalMovies].rating,
          &movies[totalMovies].avaiability,
          movies[totalMovies].code) != EOF){
            totalMovies++;
    }
  }
  fclose(file);
}


void rentalTime(){
  struct tm *date_time;
  time_t seconds;
  time(&seconds);
  date_time = localtime(&seconds);

  printf("Hour: %d:%d:%d\n", date_time->tm_hour, date_time->tm_min, date_time->tm_sec);
  printf("Date: %d/%d/%d\n", date_time->tm_mday, date_time->tm_mon + 1, date_time->tm_year + 1900);
}


void devolutionTime(){
  struct tm *date_time;
  time_t seconds;
  time(&seconds);
  date_time = localtime(&seconds);

  printf("Date: %d/%d/%d\n", date_time->tm_mday + 3, date_time->tm_mon + 1, date_time->tm_year + 1900);
}


void rentMovie(Movie movies[MAX_MOVIES]){
  printf("- - - - Movie Rental - - - -\n");

  char request[MAX_STRING];
  printf("Movie title: ");
  fgets(request, MAX_STRING, stdin);
  request[strcspn(request, "\n")] = '\0';
  
  int result, demandQtt;
  for(int i = 0; i < totalMovies; i++) {
    Movie aux = movies[i];
    result = strcmp(request, aux.title);
    if(result == 0) {
      printf("Quantity: ");
      scanf("%d", &demandQtt);

      if(demandQtt > aux.avaiability){
        printf("\nInsufficient quantity avaiable!\n");
        return;
      }
      else{
        movies[i].avaiability = movies[i].avaiability - demandQtt;
        printf("\nMovie rented sucessfully!\n\n");

        printf("- - - - Rental Receipt - - - -\n");
        printf("Movie: %s\n", request);
        printf("Movie code: %s\n", aux.code);
        printf("Quantity: %d\n", demandQtt);
        printf("Total: U$ %d.00\n", demandQtt * 10);
        rentalTime();
        printf("\n");
        printf("Devolution:\n");
        devolutionTime();
        printf("\n");
        printf("Notes:\n");
        printf("For each day of delaying, the constumer will be fined with a U$ 2.00 fee.\n");
        printf("From the day of receiving, the costumer has 3 days to hand in the movie(s) without being fined.\n");
        printf("The integrity of this movie, as well the compromise to devolve is all of the costumer,\nas well eventual delay, lost or damage.\n");
      }
      break;
    }
  }
  if(result != 0){
    printf("\nMovie not found/avaiable!\n");
    return;
  }
}


void returnMovie(Movie movies[MAX_MOVIES]){
  printf("- - - - Movie Devolution - - - -\n");
  
  char rentedMovie[MAX_STRING];
  printf("Movie title: ");
  fgets(rentedMovie, MAX_STRING, stdin);
  rentedMovie[strcspn(rentedMovie, "\n")] = '\0';
  
  int result, rentedQtt;
  for(int i = 0; i < totalMovies; i++){
    Movie aux = movies[i];
    result = strcmp(rentedMovie, aux.title);
    if(result == 0){
      printf("Quantity: ");
      scanf("%d", &rentedQtt);
      
      if(rentedQtt <= 0)
        printf("Invalid quantity\n");

      else{
        movies[i].avaiability = movies[i].avaiability + rentedQtt;
        printf("\nMovie sucessfully returned!\n");
      }
      break;
    }
  }
  if(result != 0){
    printf("\nError! Description does not match your receipt\n");
    return;
  }
}


void flush(){        
  while(getchar() != '\n');
}


void pause(){
  printf("Press any key to continue  ");
  getch();
  system("cls");
}


int main(){
  int option;
  char name[MAX_STRING];
  do{
    printf("- - - - MEGA VIDEO - - - -\n");
    printf("Options:\n1. Register a movie\n2. See registered movies\n3. See data of a movie\n4. Delete a movie\n5. Save\n6. Load\n7. Rent and print receipt\n8. Turn in movie\n9. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &option);
    flush();
    system("cls");
        
    switch(option){
      case 1:
        if(totalMovies < MAX_MOVIES){
          movies[totalMovies] = registerMovie();
          totalMovies++;
          printf("Total registered: %d/%d\n", totalMovies, MAX_MOVIES);
        }
        else
          printf("Maximium total registered! (%d/%d)\n", totalMovies, MAX_MOVIES);

        printf("\n");
        pause();
        break;
      case 2:
        if(totalMovies == 0)
           printf("No movie registered!\n\n");
        else
          showMovies();
        
        pause();
        break;
      case 3:
        if(totalMovies == 0)
          printf("No movie registered!\n");
        else{
          printf("Movie: ");
          fgets(name, MAX_STRING, stdin);
          name[strcspn(name, "\n")] = '\0';
          searchMovie(name, movies);
        }
        printf("\n");
        pause();
        break;
      case 4:
        if(totalMovies == 0)
          printf("No movie registered!\n");
        else{
          printf("Movie: ");
          fgets(name, MAX_STRING, stdin);
          name[strcspn(name, "\n")] = '\0';
          deleteMovie(name, movies);
        }
        printf("\n");
        pause();
        break;
      case 5:
        if(totalMovies == 0)
          printf("Error! Cannot save\n");
        else
          saveMovies();

        printf("\n");
        pause();
        break;
      case 6:
        loadMovies();
        printf("\n");
        pause();
        break;
      case 7:
        if(totalMovies == 0)
          printf("Error! Cannot rent!\n");
        else
          rentMovie(movies);
        
        printf("\n");
        pause();
        break;
      case 8:
        returnMovie(movies);
        printf("\n");
        pause();
        break;
      case 9:
        printf("Thank you for coming to  MEGA VIDEO!\n");
        printf("Opening hours:\nMON to FRI, from  1:00 p.m. to 9:00 p.m.\nSAT to SUN from 1:00 p.m. to 5:00 p.m.\n\n");
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid option!\n");
        printf("\n");
        pause();
    }
  } while(option != 9);
  return 0;
}