#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TOTAL_COLORS 9
#define TOTAL_ATTEMPTS 10
#define LENGTH_OF_CODE 4


// Function declarations
void get_the_user_input(char *the_user_input);
int check_the_guess(char *the_secret_code, char *the_user_guess, int *well_placed, int *misplaced);
void generate_the_secret_code(char *the_secret_code);
int is_the_input_valid(char *the_input);




int main(int argc, char *argv[]) {
    char the_secret_code[LENGTH_OF_CODE + 1];
    int number_of_attempts = TOTAL_ATTEMPTS;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc && is_the_input_valid(argv[i + 1])) {
                strncpy(the_secret_code, argv[i + 1], LENGTH_OF_CODE);
                the_secret_code[LENGTH_OF_CODE] = '\0';
                i++;
            } else {
                printf("The code is invalid.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc && atoi(argv[i + 1]) > 0) {
                number_of_attempts = atoi(argv[i + 1]);
                i++;
            } else {
                printf("The number of attempts is invalid.\n");
                return 1;
            }
        } else {
            //the_usage();
            printf("Usage: my_mastermind [-c the_secret_code] [-t number_of_attempts]\n");
            return 1;
        }
    }
    if (strlen(the_secret_code) != LENGTH_OF_CODE){
        generate_the_secret_code(the_secret_code);
    }
        
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int attempt = 0; attempt < number_of_attempts; attempt++) {
        char the_user_guess[LENGTH_OF_CODE + 1];
        int well_placed = 0, misplaced = 0;
        printf("---\nRound %d\n", attempt);
        get_the_user_input(the_user_guess);
        
        if (check_the_guess(the_secret_code, the_user_guess, &well_placed, &misplaced)) {
            printf("Congratz! You did it!\n");
            return 0;
        }
    
        if (well_placed == 0 && misplaced == 0) {
            printf("Well placed pieces: 0\n");
            printf("Misplaced pieces: 0\n");
        } else {
            printf("Well placed pieces: %d\n", well_placed);
            printf("Misplaced pieces: %d\n", misplaced);
        }
    }
    printf("You ran out of attempts. The secret code was: %s\n", the_secret_code);
    return 0;
}

// Function to get the user input
void get_the_user_input(char *the_user_input) {
    int index = 0;
    char the_input;
    while (1) {
        int bytes_read = read(0, &the_input, 1);
        if (bytes_read <= 0 || the_input == '\n') {
            the_user_input[index] = '\0';
            break;
        }
        if (the_input == '\x04') {
            exit(0);
        }
        if (the_input >= '0' && the_input <= '8')
            the_user_input[index++] = the_input;
        else {
            printf("Wrong input!\n");
            while ((bytes_read = read(0, &the_input, 1)) > 0 && the_input != '\n');
            index = 0;
        }
    }
}

// Function to check the guess
int check_the_guess(char *the_secret_code, char *the_user_guess, int *well_placed, int *misplaced) {
    for (int i = 0; i < LENGTH_OF_CODE; i++) {
        if (the_secret_code[i] == the_user_guess[i])
            (*well_placed)++;
    }
    for (int i = 0; i < LENGTH_OF_CODE; i++) {
        if (the_secret_code[i] != the_user_guess[i]) {
            for (int j = 0; j < LENGTH_OF_CODE; j++) {
                if (i != j && the_secret_code[i] == the_user_guess[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
    return (*well_placed == LENGTH_OF_CODE);
}

// Function to generate the secret code
void generate_the_secret_code(char *the_secret_code) {
    srand(time(NULL));
    for (int i = 0; i < LENGTH_OF_CODE; i++){
        the_secret_code[i] = '0' + rand() % TOTAL_COLORS;
    }

    the_secret_code[LENGTH_OF_CODE] = '\0';
} 

// Function to check the validity of input
int is_the_input_valid(char *the_input) {
    for (int i = 0; i < LENGTH_OF_CODE; i++) {
        if (the_input[i] < '0' || the_input[i] > '8')
            return 0;
    }
    return 1;
}