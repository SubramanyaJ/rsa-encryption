#include <stdbool.h>

void clear(){                                                           // Used to clear the input buffer
    while ( getchar() != '\n' );
}

void getInteger(int *p, char name[]){                                   // Obtains an integer from the user
    printf("Enter the value of %s : ", name);
    scanf("%i", p);
}

bool getPrimes(int *p, int *q){                                         // Gets two numbers, and checks whether
    int a, b;                                                           // these numbers are primes
    getInteger(&a, "p");
    getInteger(&b, "q");
    if(primeCheck(a) && primeCheck(b)){
        *p = a;     *q = b;
        clear();
        return true;
    }
    return false;
}