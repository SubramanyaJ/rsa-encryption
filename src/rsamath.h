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

unsigned long int power(int a, int b){
    if(b == 1)
        return a;
    else
        return a*power(a, b-1);
}

long long int optmodulus(long long int a, long long int e, long long int m){
    long long int retval = 1;
    for(int i = 0; i < e; ++i){
        retval = (retval*a)%m;
    }
    return retval;
}