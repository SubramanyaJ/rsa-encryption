#include <math.h>
#include <stdbool.h>

bool primecheck(int p){
    if(p == 0 || p == 1)
        return false;
    for(int i = 2; i <= sqrt(p); i++){
        if(p%i==0){
            return false;
        }
    }
    return true;
}

int gcd(int a, int b){
    if(b>a)
        return gcd(b, a);
    if(b==0)
        return a;
    else   
        return gcd(b, a%b);
}

void product_totient(int p, int q, int *n, int *t){
    *n = p*q;
    *t = ((p-1)*(q-1))/(gcd((p-1), (q-1)));
}

void coprimes(int n){
    for(int i = 2; i < n; ++i){
        if( gcd(n, i) == 1 )
            printf("%i\t", i);
    }
    printf("\n");
}

int gcdlong(int a, int b, int *x, int *y){
    if(a==0){
        *x = 0, *y = 1;
        return b;
    }

    int tempx, tempy;
    int gcd = gcdlong(b%a, a, &tempx, &tempy);
    *x = tempy - tempx*(b/a);
    *y = tempx;

    return gcd;
}

long long int optmodulus(long long int a, long long int e, long long int m){
    long long int retval = 1;
    for(int i = 0; i < e; ++i){
        retval = (retval*a)%m;
    }
    return retval;
}