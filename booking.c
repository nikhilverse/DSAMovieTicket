#include "booking.h"

Booking* bookTicket(Booking* head, Movie* movie, const char* customer, int seat_no) {
    if (!movie || movie->available_seats <= 0) {
        printf("No available seats for this movie!\n");
        return head;
    }

    Booking* newBooking = (Booking*)malloc(sizeof(Booking));
    newBooking->movie_id = movie->id;
    strcpy(newBooking->customer_name, customer);
    newBooking->seat_no = seat_no;
    newBooking->next = head;
    head = newBooking;

    movie->available_seats--;
    printf("Booking successful for %s!\n", customer);
    return head;
}

void displayBookings(Booking* head) {
    Booking* temp = head;
    while (temp) {
        printf("Movie ID: %d | Customer: %s | Seat: %d\n",
               temp->movie_id, temp->customer_name, temp->seat_no);
        temp = temp->next;
    }
}

Booking* cancelBooking(Booking* head, int seat_no) {
    Booking *temp = head, *prev = NULL;
    while (temp && temp->seat_no != seat_no) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Booking not found!\n");
        return head;
    }
    if (!prev)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Booking canceled successfully!\n");
    return head;
}

void saveBookingsToFile(Booking* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    for (Booking* temp = head; temp; temp = temp->next)
        fprintf(fp, "%d,%s,%d\n", temp->movie_id, temp->customer_name, temp->seat_no);
    fclose(fp);
}

Booking* loadBookingsFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;
    Booking* head = NULL;
    int movie_id, seat_no;
    char name[50];
    while (fscanf(fp, "%d,%49[^,],%d\n", &movie_id, name, &seat_no) == 3) {
        Booking* newB = (Booking*)malloc(sizeof(Booking));
        newB->movie_id = movie_id;
        strcpy(newB->customer_name, name);
        newB->seat_no = seat_no;
        newB->next = head;
        head = newB;
    }
    fclose(fp);
    return head;
}

void freeBookings(Booking* head) {
    while (head) {
        Booking* temp = head;
        head = head->next;
        free(temp);
    }
}
