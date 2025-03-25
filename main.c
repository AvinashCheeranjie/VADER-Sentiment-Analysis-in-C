#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "utility.h"

int main(){
    char *filename = "vader_lexicon.txt";
    HashTable* ht = create_table();

    unsigned int numWords; // number of words in the lexicon file
    WordData *wordData = NULL; // array of WordData structs
    
    readLexiconFile(ht, filename, &wordData, &numWords);   
    
    char sentences[][100] = {
        "VADER is smart, handsome and funny.",
        "VADER is smart, handsome, and funny!",
        "VADER is very smart, handsome, and funny.",
        "VADER is VERY SMART, handsome, and FUNNY.",
        "VADER is VERY SMART, handsome, and FUNNY!!!",
        "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!",
        "VADER is not smart, not handsome, nor funny.",
        "At least it isn't a horrible book.",
        "The plot was good, but the characters are uncompelling and the dialog is not great.",
        "Make sure you :) or :D today!",
        "Not bad at all"
    };

    unsigned int size; // size of tokens array
    for(unsigned int j=0; j < sizeof(sentences)/sizeof(sentences[0]); j++){   
        printf("Sentence %d: %s\n", j+1, sentences[j]);
        float compound = calculateCompoundScore(ht, sentences[j], &size);
        printf("Compound Score: %f\n", compound);
        printf("\n");
    }

    freeHashTable(ht);
    free(wordData);
    return 0;
}