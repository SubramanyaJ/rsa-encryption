#include <stdbool.h>
#include <math.h>

bool primeCheck(int p){                                                 // Checks if the number is prime
    if(p == 0 || p == 1)
        return false;
    for(int i = 2; i <= sqrt(p); i++){
        if(p%i==0){
            return false;
        }
    }
    return true;
}

int gcd(int a, int b){                                                  // Returns the Greatest Common
    if(b>a)                                                             // Divison of the numbers
        return gcd(b, a);
    if(b==0)
        return a;
    else   
        return gcd(b, a%b);
}

int gcdExtended(int a, int b, int *x, int *y){                          // Carries out the extended
    if(a==0){                                                           // Eucllidian calculation
        *x = 0, *y = 1;
        return b;
    }

    int tempx, tempy;
    int gcd = gcdExtended(b%a, a, &tempx, &tempy);
    *x = tempy - tempx*(b/a);
    *y = tempx;

    return gcd;
}

void carmichael_totient(int p, int q, int *n, int *t){                  // Returns the Carmichael
    *n = p*q;                                                           // Totient function value
    *t = ((p-1)*(q-1))/(gcd((p-1), (q-1)));
}

void coprimes(int n){                                                   // Prints all coprimes
    for(int i = 2; i < n; ++i){                                         // of the number
        if( gcd(n, i) == 1 )
            printf("%i\t", i);
    }
    printf("\n");
}

void optimal_coprimes(int n){                                           // Prints the coprimes of the number
    int count = 0;                                                      // having smallest Hamming weight
    for(int i = 2; i <= n; i *=2, count++){}

    int optimal[count];
    for(int i = 0; i < count; i++){
        optimal[i] = pow(2, i)+1;
    }

    for(int i = 0; i < count; i++){
        if(gcd(n, optimal[i]) == 1){
            printf("%i\t", optimal[i]);
        }
    }   printf("\n");

}

long long int powerModulus(long long int a, long long int key, long long int mod){
    long long int return_value = 1;
    for(int i = 0; i < key; i++){                                   // A function that calculates
        return_value = (return_value*a)%mod;                            // (a^key) mod (mod)
    }
    return return_value;
}