#include "movie.h"
#include "booking.h"

#define MOVIE_FILE "data/movies.txt"
#define BOOKING_FILE "data/bookings.txt"

int main() {
    Movie* movieRoot = NULL;
    Booking* bookingHead = NULL;

    movieRoot = loadMoviesFromFile(movieRoot, MOVIE_FILE);
    bookingHead = loadBookingsFromFile(BOOKING_FILE);

    int choice;
    do {
        printf("\n--- Movie Ticket Management ---\n");
        printf("1. Add Movie\n2. Display Movies\n3. Search Movie by ID\n4. Search Movie by Name\n5. Delete Movie\n6. Book Ticket\n7. Show Bookings\n8. Cancel Booking\n9. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int id, seats;
            char name[50], time[20];
            printf("Enter ID, Name, Time, Seats: ");
            scanf("%d %s %s %d", &id, name, time, &seats);
            movieRoot = insertMovie(movieRoot, id, name, time, seats);
        } else if (choice == 2)
            displayMovies(movieRoot);
        else if (choice == 3) {
            int id;
            printf("Enter Movie ID: ");
            scanf("%d", &id);
            Movie* m = searchMovieById(movieRoot, id);
            if (m) printf("Found: %s at %s\n", m->name, m->time);
            else printf("Movie not found!\n");
        } else if (choice == 4) {
            char name[50];
            printf("Enter Movie Name: ");
            scanf("%s", name);
            Movie* m = searchMovieByName(movieRoot, name);
            if (m) printf("Found: %s at %s\n", m->name, m->time);
            else printf("Movie not found!\n");
        } else if (choice == 5) {
            int id;
            printf("Enter Movie ID to delete: ");
            scanf("%d", &id);
            movieRoot = deleteMovie(movieRoot, id);
            printf("Movie deleted successfully (if existed).\n");
        } else if (choice == 6) {
            int id, seat;
            char name[50];
            printf("Enter Movie ID and Your Name: ");
            scanf("%d %s", &id, name);
            Movie* m = searchMovieById(movieRoot, id);
            if (m) {
                printf("Enter seat number: ");
                scanf("%d", &seat);
                bookingHead = bookTicket(bookingHead, m, name, seat);
            } else printf("Invalid Movie ID!\n");
        } else if (choice == 7)
            displayBookings(bookingHead);
        else if (choice == 8) {
            int seat;
            printf("Enter seat number to cancel: ");
            scanf("%d", &seat);
            bookingHead = cancelBooking(bookingHead, seat);
        }
    } while (choice != 9);

    FILE* fpm = fopen(MOVIE_FILE, "w");
    saveMoviesToFile(movieRoot, fpm);
    fclose(fpm);
    saveBookingsToFile(bookingHead, BOOKING_FILE);

    freeMovies(movieRoot);
    freeBookings(bookingHead);

    printf("Goodbye!\n");
    return 0;
}
