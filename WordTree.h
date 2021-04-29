//
// Created by Sparsh Pai on 2021-03-23.
//

#ifndef PROJECT_2_250_WORDTREE_H
#define PROJECT_2_250_WORDTREE_H

#include <string>
#include "Node.h"

using namespace std;

class WordTree {

public:

    ~WordTree();
    int getIndexOfChar(char character);
    char getCharAtIndex(int index);
    bool insert(string word);
    bool erase(string word);
    bool search(string word);
    void print();
    void autocomplete(string prefix);
    bool isEmpty();
    void clear();
    int size();

private:
    void traverse(Node * node, int index, string word);
    void findLetters(Node * node, int index, string word, int size);
    void findPrefix(Node *node, int index, string prefix);
    void print_recursive(Node* current, string s);
    void deleteAll(Node*current);
    void destruct(Node*current);
    void deleteTree();

};


#endif //PROJECT_2_250_WORDTREE_H
