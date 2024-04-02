#include <stdio.h>
#include "rsamath.h"
#include "general.h"

int main(){

//Key Generation    
    //Obtaining prime numbers
    int p, q;
    if(getprimes(&p, &q)){
        printf("p = %i, q = %i\n", p, q);
    }
    else{
        printf("Two prime numbers were not entered\n");
        return -1;
    }
    //Calculating n, t, e, d
    int n, t, e, d, x, y;
    product_totient(p, q, &n, &t);
    coprimes(t);
    getInt(&e, "e");
    gcdlong(t, e, &x, &y);
    if( y < 0 )     {d = t + y; }
    else            {d = y;     }
    printf("n = %i, t = %i, e = %i, d = %i\n", n, t, e, d);

//Encryption
    //Obtaining text from input file
    int index = 0;
    int inp_coded[2000];
    FILE *inptxt;
    char c;
    inptxt = fopen("message.txt", "r");
    if (inptxt == NULL) {
        printf("Error opening input file\n");
        return -1;
    }
    while ((c = fgetc(inptxt)) != EOF && index < 2000) {
        inp_coded[index] = optmodulus(c, e, n);
        index++;
    }
    fclose(inptxt);
    //Output to file
    FILE *outtxt;
    outtxt = fopen("output.txt", "w");
    if (outtxt == NULL) {
        printf("Error opening output file\n");
        return -1;
    }
    for(int i = 0; i < index; i++){
        fprintf(outtxt, "%i ", inp_coded[i]);
    }   printf("\n");
    fclose(outtxt);


//Decryption
    //Obtaining coded message
    FILE *file;
    int numbers[2000];
    int num, count = 0;

    file = fopen("output.txt", "r");
    if(file == NULL){
        printf("Error opening output file\n");
        return -1;
    }
    while(fscanf(file, "%d", &num) != EOF && count < 2000){
        numbers[count++] = num;
    }
    fclose(file);

    for (int i = 0; i < count; i++){
        printf("%d ", numbers[i]);
    }   printf("\n");

    for(int i = 0; i < count; i++){
        printf("%c", optmodulus(numbers[i], d, n));
    }

    return 0;
}