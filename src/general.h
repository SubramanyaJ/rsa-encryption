#include <string.h>

void getInt(int *p, char name[]){
    printf("Enter the value of %s : ", name);
    scanf("%i", p);
}

bool getprimes(int *p, int *q){
    int a, b;
    getInt(&a, "p");
    getInt(&b, "q");
    if(primecheck(a) && primecheck(b)){
        *p = a;     *q = b;
        return true;
    }
    return false;
}

void clear(){
    while ( getchar() != '\n' );
}

void filesize(int *maincount){
    FILE *file;
    int count = 0;
    char ch;

    file = fopen("message.txt", "r");
    if (file == NULL){
        printf("Unable to open file.\n");
        return;
    }
    while ((ch = fgetc(file)) != EOF){
        count++;
    }
    *maincount = count;
    
    fclose(file);
}