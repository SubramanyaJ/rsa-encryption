#include <iostream>
#include <string>
using namespace std;

//math
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

//main
void getprimes(int *p, int *q){
    printf("Enter the first prime number : ");
    scanf("%i", &*p);
    printf("Enter the second prime number : ");
    scanf("%i", &*q);
}

string getmessage(){
    string retval;
    cout << "Enter your message : ";
    cin.clear(); cin.sync();
    getline(cin >> ws, retval);
    return retval;
}

int main(){

//Start of encryption
//Get the prime numbers
    int p, q;
    getprimes(&p, &q);
    printf("p = %i, q = %i\n", p, q);
//Calculate product and totient function
    int n, t;
    product_totient(p, q ,&n, &t);
    printf("n = %i, t = %i\n", n, t);
//Calculate the value of e
    int e;
    coprimes(t);
    printf("\nSelect a value for e : ");
    scanf("%i", &e);
//Calculate the value of d
    int x, y, d;
    gcdlong(t, e, &x, &y);
    if( y < 0 )
        d = t + y;
    else
        d = y;
    printf("The value of d is : %i\n", d);
//End of key generation

//Start of encryption
//Get a message
    string message = getmessage();
    
//Output padded plaintext
    int messcount = 0;
    printf("The padded plaintext is : \n");
    for(int i = 0; message[i]!='\0'; ++i, ++messcount){
        printf("[%i]", message[i]);
    }
    printf("\n");
//Outpud coded message  
    int coded[messcount];
    printf("The coded message is : \n");
    for(int i = 0; i < messcount; ++i){
        coded[i] = optmodulus(message[i], e, n);
        printf("[%i]", coded[i]);
    }
    printf("\n");
//End of encryption

//Start of decryption
//Outputs decoded ciphertext for cross-confirmation
    printf("The decoded ciphertext : \n");
    int decoded[messcount];
        for(int i = 0; i < messcount; ++i){
            decoded[i] = optmodulus(coded[i], d, n);
            printf("[%i]", decoded[i]);
        }
    printf("\n");
//Outputs decrypted text
    printf("The decoded text : ");
    for(int i = 0; i < messcount; ++i){
            printf("%c", decoded[i]);
    }
    printf("\n");
//End of decryption
    return 0;
//End of program
}