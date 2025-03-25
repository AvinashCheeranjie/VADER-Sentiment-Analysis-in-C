#ifndef UTILITY_H
#define UTILITY_H

// Constants for sentiment analysis
#define ALPHA 15 // Normalization constant for the compound score
#define INTENSIFIER_FACTOR 0.293f  
#define PUNCTUATION_FACTOR 0.292f  
#define ALLCAPS_FACTOR 1.5f 
#define NEGATION_FACTOR -0.74f 

// Constants for the WordData and HashTable structs
#define ARRAY_SIZE 10 // Max size of the distribution array 
#define MAX_STRING_LENGTH 20 // Max length of a word
#define TABLE_SIZE 1000 // Size of the hash table

// Struct representing Word Data 
typedef struct WordData{
    char word[MAX_STRING_LENGTH];
    float value1;
    float value2;
    int intArray[ARRAY_SIZE];
    struct WordData *next;
} WordData;

// Hash table struct
typedef struct HashTable{
    WordData* table[TABLE_SIZE];
} HashTable;

// Sentiment Analysis Functions 
void readLexiconFile(HashTable *ht, char *filename, WordData **wordData, unsigned int *numWords);
char **tokenizeSentence(char sentence[], unsigned int *size);
float calculateCompoundScore(HashTable *ht, char sentence[], unsigned int *size);

// Hash Table Functions
HashTable* create_table();
float search(HashTable *ht, char *key);
void insert(HashTable *ht, char *key, float value1, float value2, int intArray[ARRAY_SIZE]);
void freeHashTable(HashTable *ht);

#endif // UTILITY_H