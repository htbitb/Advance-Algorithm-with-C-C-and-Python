#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define ALPHABET_SIZE 26

/**
 * define TrieNode structure 
 */
typedef struct TrieNode{
    struct TrieNode* Children[ALPHABET_SIZE]; //Array of pointers to child nodes
    bool IsEndofWorld; // To mark if this node represents the end of a word
}TrieNode;


/**
 * Function to create a new Trie node
 */
TrieNode* CreateTrieNode(){
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->IsEndofWorld = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->Children[i] = NULL;
    }
    return node;
}

/**
 * Insert a word into the trie
 */
void insert(TrieNode* root, const char* word)
{
    TrieNode* current = root;
    while(*word)
    {
        int index = *word - 'a';
        if (!current->Children[index]){
            current->Children[index] = CreateTrieNode();
        }
        current = current->Children[index];
        word++;
    }
    current->IsEndofWorld = true;

}
/**
 * Search for a word in the Trie
 */
bool search(TrieNode *root, const char* word){
    TrieNode* current = root;
    while(*word){
        int index = *word - 'a';
        if(!current->Children[index]){
            return false;
        }
        current = current->Children[index];
        word++;
    }
    return current != NULL && current->IsEndofWorld;
}

/**
 * Helper function to check if a node has children
 */
bool hasChildren(TrieNode* node){
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if(node->Children[i]) return true;
    }

    return false;
}

/**
 * Delete a word from the trie
 */
bool Delete(TrieNode* root, const char* word, int depth){
    if(!root) return false;

    // base case: if we've reached the end of the word
    if (*word == '\0'){
        if(root->IsEndofWorld){
            root->IsEndofWorld = false;
            return !hasChildren(root); //if no children, this node can be deleted
        }

        return false;
    }

    int index = *word - 'a';
    if (Delete(root->Children[index], word + 1, depth + 1)){
        free(root->Children[index]);
        root->Children[index] = NULL;
        return !hasChildren(root) && !root->IsEndofWorld;
    }

    return false;
}

/*
* wrapper function to delete a word
*/
void deleteWord(TrieNode* root, const char* word){
    Delete(root, word, 0);
}

/**
 * Display Trie for debugging
 */
void display(TrieNode* root, char str[], int level){
    if(root->IsEndofWorld){
        str[level] = '\0';
        printf("%s", str);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if(root->Children[i]){
            str[level] = i + 'a';
            display(root->Children[i], str, level + 1);
        }
    }
}
/*
*free the trie memory
*/
void freeTrie(TrieNode* root){
    if(!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++){
        freeTrie(root->Children[i]);
    }

    free(root);
}

int main(){
    TrieNode* root = CreateTrieNode();

    insert(root, "hello");
    insert(root, "world");

    printf("Searching 'hello': %s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("Searching 'world': %s\n", search(root, "world") ? "Found" : "Not Found");
    printf("Searching 'hi': %s\n", search(root, "hi") ? "Found" : "Not Found");

    deleteWord(root, "hello");
    printf("After deletion, searching 'hello' : %s\n", search(root, "hello") ? "Found" : "Not found");


    freeTrie(root);

    return 0;

}