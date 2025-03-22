## Auto completion Suggestion Using trie
A trie is a perfect data structure for implementing an auto-complete system. it allows for efficient prefix searching, making it ideal for suggesting words based on user input

## Step to implement auto-complete with trie
1. Create a TrieNode structure with child pointers and an end words checking
2. Insert words into the trie that will be used for suggestion
3. Search for a given prefix and find all words that match
4. Use depth-first search (DFS) to collect words that match the prefix
