#include "trie.h"

#include <iostream>

using namespace std;

int main()
{
    TrieNode* root = new TrieNode();

    insert(root, "hello");
    insert(root, "candle");
    insert(root, "canary");
    insert(root, "lamp");


    cout << search(root, "canary") << endl;
    cout << search(root, "tv") << endl;
    cout << search(root, "candle") << endl;

    cout << search(root, "canary") << endl;
    cout << search(root, "movie") << endl;


    return 0;
}
