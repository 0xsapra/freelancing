// Include required header files here!
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

// The name of the input file and output file
#define IN_FILE "quotes.txt"
#define OUT_FILE "output.txt"

// The maximum number of quotes we can read from input file
#define MAX_QUOTES 100

// The maximum size of a quote (string) in the IN_FILE file
#define MAX_LEN 1000

// This function will be used in sorting to swap strings ("pointers").
void swap(char**, char**);

// Selection Sort function here.
void selection_sort(char**, size_t);

// Read quotes from file and add them to an array. This functions adjusts the size of quotes!
// Note: second parameter (size_t) should reflect the number of quotes we will read from the file!
void read_in(char**, size_t*);

// Print the quotes using array of pointers.
void print_out(char**, size_t);

// Save the sorted quotes in the OUT_FILE file (size_t here is linked to MAX_QUOTES or actual number of quotes!)
void write_out(char**, size_t);

// Free memory!
void free_memory(char**, size_t);

int main() {

    // Create array of pointers. Each pointer should point to heap memory where each quote is kept. 
    // I.e. quotes[0] points to first quote saved on the heap.
    char *quotes[MAX_QUOTES];

    // Number of quotes in the file quotes.txt. We assume initially that file has MAX_QUOTES quotes.
    // Must be adjusted inside the function read_in when the file is read!
    size_t size=MAX_QUOTES; 

    // Read quotes from file and place them into array quotes. 
    // Note: size reflects how many quotes we read from the file (between 0 and MAX_QUOTES).
    read_in(quotes, &size);

    selection_sort(quotes, size);
    
    printf("\n--Output:\n");
    print_out(quotes, size);
    // write_out(quotes, size);
    
    free_memory(quotes, size);
    
    return (0);
}

void read_in(char** inputFile, size_t *size){

    int nlines = 0, i;
    char *buffer;
    int max_lines, c, buflen, bufpos, end_of_line;

    FILE *fp = fopen(IN_FILE, "r"); // Open file in read mode
    
    max_lines = MAX_QUOTES;
    
    // creating a 2d char array 

    if (fp == 0) { 
        printf("Cannot open file %s \n", IN_FILE); 
        exit(0); 
    } 
    bufpos = 0; // index at current line, to check if it exceed MAX_LEN
    buflen = MAX_LEN;

    // buffer to input single quote
    buffer = (char *) malloc(buflen * sizeof(char *));
    
    c = 0;

    while (c != EOF) {

      end_of_line = 0;

      c = fgetc(fp);

      if ( c== '\r'){
        continue;
      } else if (c == EOF || c == '\n') {
        end_of_line = 1;
       /* Discard this character. */
      } else {
        /* Put this character in the buffer. */
        /* But check if we have enough memory first! */
        /* Leave room for the null character at the end*/
        if (bufpos >= buflen - 1) {
            printf("Number of characters in a quotes exceed %d\n", MAX_QUOTES);
            continue;
          // buflen += MAX_LINE_LENGTH_INC;
          // buffer = (char *) realloc(buffer, buflen * sizeof(char));
        }
        buffer[bufpos] = c;
        bufpos++;
      }

      if (end_of_line) {
        /* Remember this line and get a new buffer. */
        /* Check if we need more memory. */
        if (nlines >= max_lines) {
          printf("Number of quotes in file exceed %d\nStopped Loading more quotes\n\n", MAX_QUOTES);
          break;
        }
        if(bufpos == 0){
            // skipping 0 length lines from file
            continue;
        }

        /* Null terminate the buffer.*/
        buffer[bufpos++] = 0;

        inputFile[nlines] = buffer;
        nlines++;

        bufpos = 0;
        buflen = MAX_LEN;
        buffer = (char *) malloc(buflen * sizeof(char *));
      }
    }
    *size = nlines;

    printf("\n--Input:\n");
    print_out(inputFile, nlines);

    fclose(fp);
    return;
}

void swap(char** str1, char** str2){
    char* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void selection_sort(char** quote, size_t size){
    
    for(int i=0;i < size -1; i++){
        int minCurrentLineLenght = strlen(quote[i]);
        int minIndex = i;

        for(int j=i+1; j < size;j++){
            if ( strlen(quote[j]) < minCurrentLineLenght ){
                minCurrentLineLenght = strlen(quote[j]);
                minIndex  = j;
            } else if( strlen(quote[j]) == minCurrentLineLenght ){
                // checking for same length string and sort them lexographically
                int temp = strcoll(quote[minIndex], quote[j]);
                if(temp > 0) {
                    swap(&quote[minIndex], &quote[j]);
                }
            }
        }
        swap(&quote[i], &quote[minIndex]);
    }
}

void print_out(char** quotes, size_t size){
    for(int i=0;i<size;i++){
        printf("%s\n", quotes[i]);
    }
}

void free_memory(char** quotes, size_t size){
    for(int i=0;i<size;i++){
        free(quotes[i]);
    }
}

void write_out(char** quotes, size_t size){

    FILE *fptr;
    fptr = fopen(OUT_FILE, "w");
    if(fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    for(int i=0; i < size; i++){
        fprintf(fptr,"%s\n", quotes[i]);
    }
    fclose(fptr);
    return;
}



// You need to create functions according to prototypes defined above funciton main()!
