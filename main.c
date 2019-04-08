#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int wordcount;
    setSortThreads(8);
    if (!argv[1])
    {
        fprintf(stderr, "Please include a filename as an argument.\n");
        return -1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (!fp)
    {
        fprintf(stderr, "Error: File not found.\n");
        return -1;
    }
    wordcount = 0;
    while (!feof(fp))
    {
        sortable[wordcount] = getNextWord(fp);
        wordcount++;
    }
    wordcount--;
    fclose(fp);
    for (int i = 0; i < wordcount; i++)
    {
        printf("%s | ", sortable[i]);
    }
    printf("\n\n\n");
    SortParams *test = (SortParams *)malloc(sizeof(SortParams));
    test->array = sortable;
    test->left = 0;
    test->right = wordcount;
    quickSort(test);
    if (isSorted(sortable, wordcount))
    {
        printf("Sorting Successful!\n");
    }
    else
    {
        printf("Sorting Failed!\n");
    }
    return 0;
}