#include <iostream>
#include <string>
#include "rsamath.h"
using namespace std;

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

//Start of key generation
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
//Output coded message  
    int coded[messcount];
    printf("The coded message is : \n");
    for(int i = 0; i < messcount; ++i){
        coded[i] = optmodulus(message[i], e, n);
        printf("[%i]", coded[i]);
    }
    printf("\n");
//End of encryption

//Start of decryption
//Output decoded ciphertext
    printf("The decoded ciphertext : \n");
    int decoded[messcount];
        for(int i = 0; i < messcount; ++i){
            decoded[i] = optmodulus(coded[i], d, n);
            printf("[%i]", decoded[i]);
        }
    printf("\n");
//Output decoded text
    printf("The decoded text : ");
    for(int i = 0; i < messcount; ++i){
            printf("%c", decoded[i]);
    }
    printf("\n");
//End of decryption
    return 0;
//End of program
}