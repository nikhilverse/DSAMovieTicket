#include "movie.h"

Movie* createMovie(int id, const char* name, const char* time, int seats) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    newMovie->id = id;
    strcpy(newMovie->name, name);
    strcpy(newMovie->time, time);
    newMovie->available_seats = seats;
    newMovie->left = newMovie->right = NULL;
    return newMovie;
}

Movie* insertMovie(Movie* root, int id, const char* name, const char* time, int seats) {
    if (!root) return createMovie(id, name, time, seats);
    if (id < root->id)
        root->left = insertMovie(root->left, id, name, time, seats);
    else if (id > root->id)
        root->right = insertMovie(root->right, id, name, time, seats);
    return root;
}

Movie* findMin(Movie* node) {
    while (node && node->left) node = node->left;
    return node;
}

Movie* deleteMovie(Movie* root, int id) {
    if (!root) return NULL;
    if (id < root->id)
        root->left = deleteMovie(root->left, id);
    else if (id > root->id)
        root->right = deleteMovie(root->right, id);
    else {
        if (!root->left) {
            Movie* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Movie* temp = root->left;
            free(root);
            return temp;
        }
        Movie* temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->time, temp->time);
        root->available_seats = temp->available_seats;
        root->right = deleteMovie(root->right, temp->id);
    }
    return root;
}

void displayMovies(Movie* root) {
    if (!root) return;
    displayMovies(root->left);
    printf("ID: %d | Name: %s | Time: %s | Seats: %d\n",
           root->id, root->name, root->time, root->available_seats);
    displayMovies(root->right);
}

Movie* searchMovieById(Movie* root, int id) {
    if (!root || root->id == id) return root;
    return (id < root->id) ? searchMovieById(root->left, id)
                           : searchMovieById(root->right, id);
}

Movie* searchMovieByName(Movie* root, const char* name) {
    if (!root) return NULL;
    Movie* found = searchMovieByName(root->left, name);
    if (found) return found;

    char tempRoot[50], tempInput[50];
    for (int i = 0; root->name[i]; i++) tempRoot[i] = tolower(root->name[i]);
    tempRoot[strlen(root->name)] = '\0';
    for (int i = 0; name[i]; i++) tempInput[i] = tolower(name[i]);
    tempInput[strlen(name)] = '\0';

    if (strcmp(tempRoot, tempInput) == 0)
        return root;

    return searchMovieByName(root->right, name);
}

void saveMoviesToFile(Movie* root, FILE* fp) {
    if (!root) return;
    saveMoviesToFile(root->left, fp);
    fprintf(fp, "%d,%s,%s,%d\n", root->id, root->name, root->time, root->available_seats);
    saveMoviesToFile(root->right, fp);
}

Movie* loadMoviesFromFile(Movie* root, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return root;
    int id, seats; char name[50], time[20];
    while (fscanf(fp, "%d,%49[^,],%19[^,],%d\n", &id, name, time, &seats) == 4) {
        root = insertMovie(root, id, name, time, seats);
    }
    fclose(fp);
    return root;
}

void freeMovies(Movie* root) {
    if (!root) return;
    freeMovies(root->left);
    freeMovies(root->right);
    free(root);
}
