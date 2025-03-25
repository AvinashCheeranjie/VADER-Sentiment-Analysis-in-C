#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "utility.h"

// Intensifier words
const char *INTENSIFIERS[] = {"absolutely", "amazingly", "awfully", "completely", "considerably",
 "decidedly", "deeply", "effing", "enormously", "entirely", "especially", "exceptionally", "extremely", 
 "fabulously", "flipping", "flippin", "fricking", "frickin", "frigging", "friggin", "fully", "fucking",
 "greatly", "hella", "highly", "hugely", "incredibly", "intensely", "majorly", "more", "most", "particularly",
 "purely", "quite", "really", "remarkably", "so", "substantially", "thoroughly", "totally", "tremendously",
 "uber", "unbelievably", "unusually", "utterly", "very", "almost", "barely", "hardly", "just enough", 
 "kind of", "kinda", "kindof", "kind-of", "less", "little", "marginally", "occasionally", "partly", 
 "scarcely", "slightly", "somewhat", "sort of", "sorta", "sortof", "sort-of"};

// Negation words
const char *NEGATIONS[] = {"aint", "arent", "cannot", "cant", "couldnt", "darent", "didnt", "doesnt", "not", 
 "never", "nor", "isnt", "wasnt", "shouldnt", "wouldnt", "wont", "without", "zero"};

/*===============================================================================================================*/

// Check if word is in Negations or Intensifiers list
bool isInList(char *word, const char **list, int listSize) {
    for (int i = 0; i < listSize; i++) {
        if (strcmp(word, list[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Count exclamation marks attached to a given word
int countExclamationMarks(const char *word){
    int count = 0;
    for(int i = 0; word[i] != '\0'; i++){
        if(word[i] == '!'){
            count++;
        }
    }
    return count;
}

// Convert input string to uppercase
char *strupr(char *str){
    char *ptr = str;
    while(*ptr != '\0'){
        *ptr = (char)toupper(*ptr);
        ptr++;
    }
    return str;
}

// Convert input string to lowercase
char *strlwr(char *str){
    char *ptr = str;
    while(*ptr != '\0'){
        *ptr = (char)tolower(*ptr);
        ptr++;
    }
    return str;
}

// Strip trailing and leading punctuation in a given word
char *strip_punct(char *token) {
    int len = (int)strlen(token);
    int i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (!ispunct(token[i])) {
            token[j++] = token[i];
        }
    }
    token[j] = '\0';
    // check if token was an emoticon
    if (strlen(token) < 2) {
        return NULL;
    }
    return token;
}

// Read the lexicon file and store the data in a WordData array and HashTable
void readLexiconFile(HashTable *ht, char *filename, WordData **wordData, unsigned int *numWords) { 
    FILE *file = fopen(filename, "r"); 
    char line[1024]; 
    *wordData = NULL; // array of WordData 
    *numWords = 0; // to track the number of words in the file 

    while (fgets(line, sizeof(line), file)) { 
        WordData lexicon; 
        char *data = strtok(line, " \t"); 
        strcpy(lexicon.word, data); 
        data = strtok(NULL, " \t"); 
        lexicon.value1 = data ? strtof(data, NULL) : 0.0f; //convert datum string to a float if != NULL
        data = strtok(NULL, " \t");
        lexicon.value2 = data ? strtof(data, NULL) : 0.0f;
        for(int j = 0; j < ARRAY_SIZE; j++){
            data = strtok(NULL, " [");
            lexicon.intArray[j] = data ? atoi(data) : 0;
        }

        (*numWords)++; 
        *wordData = realloc(*wordData, (*numWords) * sizeof(WordData)); // reallocate memory for variable number of words in file
        (*wordData)[*numWords - 1] = lexicon; 
        insert(ht, lexicon.word, lexicon.value1, lexicon.value2, lexicon.intArray); // insert data into hash table
    }
    fclose(file); 
}

// Tokenize a given sentence
char **tokenizeSentence(char sentence[], unsigned int *size){
    long unsigned str_len = (long unsigned)strlen(sentence);
    char **tokens = (char **)malloc(str_len * sizeof(char *));
    char *token = strtok(sentence, " ,.");
    unsigned int i = 0;
    while(token != NULL){
        tokens[i] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
        strcpy(tokens[i], token);
        token = strtok(NULL, " ,.");
        i++;
    }
    *size = i; // size of the tokens array 
    return tokens;
}

void freeTokens(char **tokens, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        free(tokens[i]);
    }
    free(tokens);
}

// Calculate the compound score of a given sentence
float calculateCompoundScore(HashTable *ht,char sentence[], unsigned int *size){
    char **tokens = tokenizeSentence(sentence, size); 
    float totalScore = 0.0;
    float multiplier = 1.0;
    bool but = false; 

    for(unsigned int i = 0; i < *size; i++){ 
        int exclamationCount = countExclamationMarks(tokens[i]);
        if(exclamationCount > 0 && exclamationCount < 4){
            totalScore += ((float)exclamationCount*PUNCTUATION_FACTOR); 
        }

        char *copy = strdup(tokens[i]);
        char *word = strlwr(strip_punct(copy) ? strip_punct(copy) : tokens[i]); // NULL indicates token is an emoticon
        float wordScore = search(ht, word);

        // Check for "but" to boost the subsequent sentiments
        if (strcmp(word, "but") == 0){
            multiplier *= 1.5f;
            but = true;
        }

        // Intensifier check
        if (isInList(word, INTENSIFIERS, sizeof(INTENSIFIERS) / sizeof(INTENSIFIERS[0]))){
            multiplier *= INTENSIFIER_FACTOR;
            // Check if intensifier is in ALL CAPS
            if (strcmp(strupr(word), tokens[i]) == 0){
                multiplier *= ALLCAPS_FACTOR;
            }
            free(copy);
            continue;
        } 

        // Negation check
        if (isInList(word, NEGATIONS, sizeof(NEGATIONS) / sizeof(NEGATIONS[0]))){
            multiplier *= NEGATION_FACTOR;
            // Check if negation is in ALL CAPS
            if (strcmp(strupr(word), tokens[i]) == 0) {
                multiplier *= ALLCAPS_FACTOR;
            }
            free(copy);
            continue;
        }

        if (wordScore != 0.0){
            // Check for ALL CAPS and ignore emoticons 
            if (strcmp(strupr(word), tokens[i]) == 0 && strlen(word) > 2) {
                multiplier *= ALLCAPS_FACTOR;
            }

            if(multiplier > 1.0 && but == true){
                totalScore += wordScore*(1+multiplier);
                free(copy);
                continue;
            }
            if(multiplier == 1.0){
                totalScore += (wordScore*multiplier);
                free(copy);
                continue;
            } 
            if(multiplier > 0.0){
                totalScore += wordScore*(1+multiplier);
                multiplier = 1.0;
            }           
            if(multiplier < 0.0){
                totalScore += (wordScore*multiplier);
                multiplier = 1.0;
            }
            
        }
        free(copy);     
    }
    freeTokens(tokens, *size);
    float compound = (float)(totalScore/sqrt(totalScore*totalScore + ALPHA));
    return compound;
}
 
HashTable* create_table() {
    HashTable* ht = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
} 

// Hash function for string (djb2 algorithm)
unsigned long hashString(char *key){
    unsigned long hash = 5381;
    unsigned char c;
    while ((c = (unsigned char)*key++)) {
        hash = (unsigned long)(((hash << 5) + hash) + c); // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// Insert word and its data to hash table
void insert(HashTable *ht, char *key, float value1, float value2, int intArray[ARRAY_SIZE]){
    unsigned long index = hashString(key);
    WordData *newEntry = (WordData *)malloc(sizeof(WordData));
    strcpy(newEntry->word, key);
    newEntry->value1 = value1;
    newEntry->value2 = value2;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        newEntry->intArray[i] = intArray[i];
    }
    newEntry->next = ht->table[index]; 
    ht->table[index] = newEntry;
}

// Search for value1 by word
float search(HashTable *ht, char *key){
    unsigned long index = hashString(key);
    WordData *entry = ht->table[index];
    while (entry != NULL) {
        if(strcmp(entry->word, key) == 0){
            return entry->value1;
        }
        entry = entry->next;
    }
    return 0.0; // Key not found
}

void freeHashTable(HashTable *ht){
    for(int i = 0; i < TABLE_SIZE; i++){
        WordData *entry = ht->table[i];
        while(entry != NULL){
            WordData *prev = entry;
            entry = entry->next;
            free(prev);
        }
    }
    free(ht);
}








