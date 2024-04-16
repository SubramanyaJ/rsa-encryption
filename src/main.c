#include <stdio.h>
#include "rsamath.h"
#include "general.h"

// !Please enter the text to be encrypted into the message.txt file in this directory!

int main(){

// Decision 1*
    puts("Select encryption or decryption e/d : ");                     // Lower overhead than printf()
    char decision = getchar();                                          // decision variable
    clear();

// Encryption
    int mod, enc_key, dec_key;                                          // values of n, e, and d

    if(decision == 'e'){                                                // Encryption block

        // Decision 2*
        puts("Is key generation needed? y/n : ");
        decision = getchar();
        clear();

        if(decision == 'y'){                                            // Key generation

            int p, q;                                                   // Primes p and q
            if(!getPrimes(&p, &q)){
                puts("Error : Two prime numbers were not entered");     // Error handling
                return -1;
            }

            
            int t, x, y;
            carmichael_totient(p, q, &mod, &t);                         // Computes the totient function

            // Decision 3*
            puts("Show all possible enc values? y/n : ");
            decision = getchar();
            clear();              
                
            if( decision == 'y' ){
                coprimes(t);                                            // Shows all possible encryption key values
            }
            else if( decision = 'n' ){
                optimal_coprimes(t);                                    // Shows encryption values with lowest Hamming Weight
            }
            else{                                                       // Error handling fro decision 3
                puts("Error : Invalid input");
                return -3;
            }
            
            puts("Select an encryption exponent : ");
            scanf("%i", &enc_key);                                      // Obtains an encryption exponent from the user
                
            {
                int x, y;                                               // Calculates the value of decryption exponent
                gcdExtended(t, enc_key, &x, &y);                        
                if( y < 0 )     {   dec_key = t +y;   }                 // Block ensures destruction of
                else            {   dec_key = y;      }                 // unnecessary variables
            }
            
            printf("The decryption key is : (%d, %d)\n", dec_key, mod);
        }

        else if( decision == 'n' ){
            puts("Enter the encryption key in the format (e , n)");     
            scanf("(%d, %d)", &enc_key, &mod);                          // Obtains encryption key from the user
        }
        
        else{                                                           // Error handling for decision 2
            puts("Invalid input");
            return -2;
        }
        //End of obtaining a key
        
        //Start of encryption

        FILE *input_file, *output_file;                                 // File pointers
        char index;                                                     // Indexing character : used to read the message file

        input_file = fopen("message.txt", "r");                         // Opens message.txt in Read mode
        if( input_file == NULL ){                                       // Error handling for input_file
            puts("Error in opening the file.");
            return -4;
        }

        output_file = fopen("output.txt", "w");                         // Opens output.txt in Write mode
        if( output_file == NULL ){                                      // Error handling for output_file
            puts("Error in opening the file.");
            return -5;
        }

        while( (index = fgetc(input_file)) != EOF ){                                // Reads input file, and directly 
            fprintf(output_file, "%lld ", powerModulus(index, enc_key, mod));       // encrypts them into output
        }

        fclose(input_file);                                             // Closes input_file
        fclose(output_file);                                            // Closes output_file

        puts("Encryption successful, written to output.txt");

        return 1;                                                       // End of the encryption program
    }                                                                   // exits with code +1

    if(decision == 'd'){                                                // Decryption block
        
        puts("Enter the decryption key in the format (d, n)");          
        scanf("(%d, %d)", &dec_key, &mod);                              // Obtains decryption key from the user

        FILE *input_file, *output_file;                                 // File pointers

        input_file = fopen("output.txt", "r");                          // Opens output.txt in Read mode
        if( input_file == NULL ){                                       // Error handling for input_file
            puts("Error in opening the file.");
            return -6;
        }

        output_file = fopen("decoded.txt", "w");                        // Opens decoded.txt in Write mode
        if( output_file == NULL ){                                      // Error handling for output_file
            puts("Error in opening the file.");
            return -7;
        }

        long long int index;                                            // Indexing integer
        while( fscanf(input_file, "%lld", &index) != EOF ){                         // Reads the encrypted text, and directly
            fprintf(output_file, "%c", powerModulus(index, dec_key, mod));          // decrypts them into the output
        }

        fclose(input_file);                                             // Closes input_file
        fclose(output_file);                                            // Closes output_file

        puts("Decryption successful, written to decoded.txt");

        return 2;                                                       // End of  decryption program
    }                                                                   // exits with code +2

    else{                                               // Error handling for decision 1
        puts("Error : Invalid input");
        return -1;
    }

}

/*
    Known weaknesses :
        1. No input validation for encryption exponent
        2. Unoptimised powerModulus function
*/