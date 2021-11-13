#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>

struct TrieNode
{
    std::unordered_map<char, TrieNode*> edges;
    bool isEndWord = false;
};

void insert(TrieNode* root, const std::string& word)
{
    TrieNode* currentNode = root;

    for(auto ch : word)
    {
        if(currentNode->edges.find(ch) == currentNode->edges.end()) // char doesn't exist as an edge
        {
            currentNode->edges[ch] = new TrieNode();
        }
        currentNode = currentNode->edges[ch];
    }
    currentNode->isEndWord = true;
}

bool search(TrieNode* root, const std::string& word)
{
    TrieNode* currentNode = root;

    for(auto ch : word)
    {
        if(currentNode->edges.find(ch) == currentNode->edges.end()) // char doesn't exist as an edge
        {
            return false;
        }
        currentNode = currentNode->edges[ch];
    }
    return currentNode->isEndWord;
}

#endif // TRIE_H
