#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Movie {
    int id;
    char name[50];
    char time[20];
    int available_seats;
    struct Movie *left, *right;
} Movie;

Movie* insertMovie(Movie* root, int id, const char* name, const char* time, int seats);
Movie* deleteMovie(Movie* root, int id);
Movie* findMin(Movie* node);
void displayMovies(Movie* root);
Movie* searchMovieById(Movie* root, int id);
Movie* searchMovieByName(Movie* root, const char* name);
void saveMoviesToFile(Movie* root, FILE* fp);
Movie* loadMoviesFromFile(Movie* root, const char* filename);
void freeMovies(Movie* root);

#endif
