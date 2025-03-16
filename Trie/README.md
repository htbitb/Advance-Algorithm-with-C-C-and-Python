## What is a Trie?
A Trie is a tree-like data structure used to store strings efficiently for quick retrieval. it's widely used in applications like:

* **Auto-complete suggestions**
* **Spell checking**
* **IP routing**
* **Dictionary word searches**

## Steps to implement a Trie
1. Define the TrieNode structure
Each **TrieNode** should:
    * Have children (an array of pointers to other TrieNodes)
    * Have a flag to mark the end of a work
2. Create a New TrieNode
A helper function initializes a new node.

3. Insert a Word into the trie
Loop through the characters of the word and insert nodes if they don't exist.

4. Search for a Word in the Trie
Loop through the characters of the word and check if they exist in the Trie

5. Delete a Word from the Trie
User recursion to remove nodes that are no longer needed