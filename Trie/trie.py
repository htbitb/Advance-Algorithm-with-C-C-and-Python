
class TrieNode:
    def __init__(self):
        self.children = {}
        self.isEndofWord = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        current = self.root

        for char in word:
            if(char not in current.children):
                current.children[char] = TrieNode()
            current = current.children[char]
        current.isEndofWord = True
        
    def search(self, word):
        current = self.root
        
        for char in word:
            if char not in current.children:
                return False
            current = current.children[char]
        
        return current != None and current.isEndofWord
    
    def delete(self, word):
        def _delete(node, word, depth):
            if depth == len(word) - 1:
                if node.isEndofWord:
                    return False #word not found
                node.isEndofWord = False
                return len(node.children) == 0
            
            char = word[depth]
            if char not in node.children:
                return False
            
            should_delete = _delete(node.children[char], word, depth+1)
            
            if should_delete:
                del node.children[char]
                return len(node.children[char]) == 0
            
            return False
        
        _delete(self.root, word, 0)
            
        
A = Trie()
A.insert("hello")
A.insert("world")
A.delete("hello")
print("Found" if A.search("hello") else "Not Found")