#ifndef BOOKING_H
#define BOOKING_H

#include "movie.h"

typedef struct Booking {
    int movie_id;
    char customer_name[50];
    int seat_no;
    struct Booking *next;
} Booking;

Booking* bookTicket(Booking* head, Movie* movie, const char* customer, int seat_no);
void displayBookings(Booking* head);
Booking* cancelBooking(Booking* head, int seat_no);
void saveBookingsToFile(Booking* head, const char* filename);
Booking* loadBookingsFromFile(const char* filename);
void freeBookings(Booking* head);

#endif
