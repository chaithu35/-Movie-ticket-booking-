
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 3
#define MAX_SHOWTIMES 3
#define MAX_SEATS 50

typedef struct {
    char movieName[50];
    char showtimes[MAX_SHOWTIMES][10];
} Movie;

typedef struct {
    char movieName[50];
    char showtime[10];
    int seatNumber;
} Booking;

void showMovies(Movie movies[]) {
    printf("\nAvailable Movies:\n");
    for (int i = 0; i < MAX_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i].movieName);
    }
}

void showShowtimes(Movie movie) {
    printf("\nAvailable Showtimes for %s:\n", movie.movieName);
    for (int i = 0; i < MAX_SHOWTIMES; i++) {
        printf("%d. %s\n", i + 1, movie.showtimes[i]);
    }
}

void bookTicket(Movie movies[]) {
    int movieChoice, showtimeChoice, seatNumber;
    Booking booking;

    showMovies(movies);
    printf("Select a movie (1-%d): ", MAX_MOVIES);
    scanf("%d", &movieChoice);
    if (movieChoice < 1 || movieChoice > MAX_MOVIES) {
        printf("Invalid movie choice!\n");
        return;
    }

    strcpy(booking.movieName, movies[movieChoice - 1].movieName);

    showShowtimes(movies[movieChoice - 1]);
    printf("Select a showtime (1-%d): ", MAX_SHOWTIMES);
    scanf("%d", &showtimeChoice);
    if (showtimeChoice < 1 || showtimeChoice > MAX_SHOWTIMES) {
        printf("Invalid showtime choice!\n");
        return;
    }

    strcpy(booking.showtime, movies[movieChoice - 1].showtimes[showtimeChoice - 1]);

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNumber);
    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    booking.seatNumber = seatNumber;

    // Display confirmation
    printf("\nBooking Confirmed!\n");
    printf("Movie: %s\n", booking.movieName);
    printf("Showtime: %s\n", booking.showtime);
    printf("Seat Number: %d\n", booking.seatNumber);

    // Save booking to file
    FILE *file = fopen("booking_history.txt", "a");
    if (file == NULL) {
        printf("Error opening booking history file!\n");
        return;
    }
    fprintf(file, "Movie: %s | Showtime: %s | Seat: %d\n",
            booking.movieName, booking.showtime, booking.seatNumber);
    fclose(file);

    printf("Booking saved to history!\n");
}

void viewBookingHistory() {
    FILE *file = fopen("booking_history.txt", "r");
    if (file == NULL) {
        printf("No booking history found!\n");
        return;
    }

    char ch;
    printf("\n--- Booking History ---\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("\n------------------------\n");
}

int main() {
    Movie movies[MAX_MOVIES] = {
        {"Chandramuki", {"10:00AM", "2:00PM", "6:00PM"}},
        {"Your Name.", {"11:00AM", "3:00PM", "7:00PM"}},
        {"Matrix", {"9:00AM", "1:00PM", "5:00PM"}}
    };

    int choice;

    do {
        printf("\n==== Movie Ticket Booking ====\n");
        printf("1. Book a Ticket\n");
        printf("2. View Booking History\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket(movies);
                break;
            case 2:
                viewBookingHistory();
                break;
            case 3:
                printf("Thank you for using the booking system!\n");
                break;
            default:
                printf("Invalid choice! Please select again.\n");
        }
    } while (choice != 3);

    return 0;
}
