#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sort.h"
#include <time.h>

#define DICT_MAX_WORD_LEN   256

char* getNextWord(FILE* fd) {
    char ch;                                /* holds current character */
    char wordBuffer[DICT_MAX_WORD_LEN];        /* buffer for build a word */
    int putChar = 0;                        /* current pos in buffer   */
    
    assert(fd != NULL);        /* the file descriptor better not be NULL */
    
    /* read characters until we find an alphabetic one (or an EOF) */
    while ((ch = fgetc(fd)) != EOF) {
        if (isalpha(ch)) break;
    }
    if (ch == EOF) return NULL;        /* if we hit an EOF, we're done */
    
    /* otherwise, we have found the first character of the next word */
    wordBuffer[putChar++] = tolower(ch);
    
    /* loop, getting more characters (unless there's an EOF) */
    while ((ch = fgetc(fd)) != EOF) {
        /* the word is ended if we encounter whitespace */
        /* or if we run out of room in the buffer       */
        if (isspace(ch) || putChar >= DICT_MAX_WORD_LEN - 1) break;
        
        /* otherwise, copy the (lowercase) character into the word   */
        /* but only if it is alphanumeric, thus dropping punctuation */
        if (isalnum(ch)) {
            wordBuffer[putChar++] = tolower(ch);
        }
    }
    
    wordBuffer[putChar] = '\0';        /* terminate the word          */
    return strdup(wordBuffer);        /* re-allocate it off the heap */
}

int compare(const void* word1, const void* word2) {
    char* w1 = *(char**) word1;
    char* w2 = *(char**) word2;
    
    return (strcmp(w1, w2));
}

int main(int argc, char** argv) {
    unsigned int count = 0;
    FILE* file = fopen("plrabn12.txt", "r");
    
    // count the words in the file
    char* word = getNextWord(file);
    while(word != NULL) {
        count++;
        free(word);
        word = getNextWord(file);
    }
    // reset offset
    fseek(file, 0, SEEK_SET);
    
    char* array[count];
    
    // fill array
    for (int i = 0; i < count; i++) {
        array[i] = getNextWord(file);
    }
    
    struct timespec qstart, qend;
    double qelapsed;
    
    // run benchmark test with qsort
    
    /*
    char** qArray = array;
    clock_gettime(CLOCK_MONOTONIC, &qstart);
    qsort(qArray, count, sizeof(char*), compare);
    clock_gettime(CLOCK_MONOTONIC, &qend);
    qelapsed = qend.tv_nsec - qstart.tv_nsec;
    printf("Qsort Time: %f\n", qelapsed); 
    */
    
    if (argc > 1) setSortThreads(atoi(argv[1]));

    printf("Thread %s\n ",argv[1]);

    struct timespec start, end;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    sortThreaded(array, count);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = end.tv_nsec - start.tv_nsec;
    printf("Time: %f\n", elapsed); 
    
    
    if (argc == 3) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", array[i]);
        }
    }    

    // free array
    for (int i = 0; i < count; i++) {
        free(array[i]);
    }
    
    fclose(file);
}
