#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode{
    struct TrieNode* children[ALPHABET_SIZE];
    bool IsEndOfWord;
}TrieNode;

/**
 * Function to create a new Trie Node
 * 2025.03.22
 */

TrieNode* CreateTrieNode(){
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->IsEndOfWord = false;
    for(int i = 0; i < ALPHABET_SIZE; i++){
        node->children[i] = NULL;
    }

    return node;
}

/**
 * Function to insert a word into the Trie
 * 2025.03.22
 */
void insert(TrieNode* root, const char* word)
{
    TrieNode* current = root;
    while(*word)
    {
        int index = *word - 'a';
        if (!current->children[index]){
            current->children[index] = CreateTrieNode();
        }
        current = current->children[index];
        word++;
    }
    current->IsEndOfWord = true;

}

/**
 * Function to search for a given prefix in the Trie
 * 2025.03.22
 */
TrieNode* searchPrefix(TrieNode* node, const char *prefix){
    TrieNode* current = node;
    while(*prefix){
        int index = *prefix - 'a';
        if(!current->children[index]) return NULL;
        current = current->children[index];
        prefix++;
    }

    return current;
}

/**
 * Depth-First Search to collect all words with a given prefix
 * 2025.03.22
 */
void CollectWords(TrieNode* node, char prefix[], int level){
    if (node->IsEndOfWord){
        prefix[level] = '\0';
        printf("%s\n", prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++){
        if(node->children[i]){
            prefix[level] = i + 'a';
            CollectWords(node->children[i], prefix, level + 1);
        }
    }
}

/**
 * Function to display auto-complete suggestions
 * 2025.03.22
 */
void autoComplete(TrieNode *node, const char *prefix){
    TrieNode* prefixNode = searchPrefix(node, prefix);
    if(!prefixNode){
        printf("No suggestion word found for %s", prefix);
        return;
    }

    char buffer[100];
    strcpy(buffer, prefix);
    printf("Suggestion for %s : \n", prefix);
    CollectWords(prefixNode, buffer, strlen(prefix));
}

// Main function to test Auto-Complete
int main() {
    TrieNode *root = CreateTrieNode();

    // Sample dictionary for auto-complete suggestions
    char *words[] = {"hello", "hell", "hero", "her", "help", "helmet", "healthy", "heap", "happy", "happen"};
    int n = sizeof(words) / sizeof(words[0]);

    // Insert words into Trie
    for (int i = 0; i < n; i++) {
        insert(root, words[i]);
    }

    // Auto-complete suggestions for different prefixes
    autoComplete(root, "he");
    autoComplete(root, "hel");
    autoComplete(root, "hap");
    autoComplete(root, "z");  // Non-existing prefix

    return 0;
}