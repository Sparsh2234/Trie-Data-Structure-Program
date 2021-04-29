//
// Created by Sparsh Pai on 2021-03-23.
//

#include <iostream>
#include "WordTree.h"
#include "Node.h"

using namespace std;

Node * head = new Node();
Node * current = head;

int numOfNodes = 0;

int numberOfWords = 0;

bool returnVal;

int count = 0;

bool WordTree::insert(string word) {

    int charIndex = getIndexOfChar(word[count]);

    if (current->getChild(charIndex) == nullptr){
        current->setChild(charIndex);
        current = current->getChild(charIndex);

        if (count < word.size()-1) {
            count++;
            numOfNodes++;
            insert(word);                        //Recursive call to function 'insert()'
        }
        else {
            returnVal = true;

            current->setTerminate();
            numberOfWords++;
            count = 0;
            current = head;
        }
    }

    else {

        current = current->getChild(charIndex);
        current->setShared();

        if (count < word.size()-1) {
            count++;
            numOfNodes++;
            insert(word);                        //Recursive call to function 'insert()'
        }

        else {

            returnVal = true;

            if (count == (word.size()-1) && current->getTerminateStat() == true){
                returnVal = false;
                numberOfWords--;
            }

            current->setTerminate();
            numberOfWords++;
            count = 0;
            current = head;

        }

    }

    return returnVal;
}

bool isNotSubWord = false;
bool nullPtrFound = false;
bool isSharedBasic = false;
bool terminateMet = false;
bool hasSingleVisited = false;
bool wordIsContained = false;

bool WordTree::erase(string word) {
    nullPtrFound = false;
    terminateMet = false;
    isNotSubWord = false;
    isSharedBasic = false;
    hasSingleVisited = false;
    wordIsContained = false;

    traverse(current,0, word);

    if (nullPtrFound == false) {
        numberOfWords--;
    }

    return nullPtrFound;
}


void WordTree::traverse(Node *node, int index,  string word) {
    if (node == nullptr) {
        nullPtrFound = true;
    }

    if(search(word) == false) {
         nullPtrFound = true;
    }

    if (node != nullptr && index < word.size()-1)
    {
        if (word.size() == 1) {
            hasSingleVisited = true;
        }
        traverse(node->getChild(getIndexOfChar(word[index])),index + 1,word);
    }


    if(nullPtrFound == false){

        if(node->getChild(getIndexOfChar(word[index])) == nullptr) {
            nullPtrFound = true;
            return;
        }

        if (node->getChild(getIndexOfChar(word[index]))->getSharedStat() > 1) {
            node->getChild(getIndexOfChar(word[index]))->removeShared();
            isSharedBasic = true;
        }

        if (node != nullptr && node->getChild(getIndexOfChar(word[index]))->getSharedStat() == 0) {
            isNotSubWord = true;
            numOfNodes--;
            node->deleteChild(getIndexOfChar(word[index]));
        }

        else if (node != nullptr && node->getChild(getIndexOfChar(word[index])) != nullptr && node->getChild(getIndexOfChar(word[index]))->getTerminateStat() == true && terminateMet == false) {
            if (isNotSubWord == false) {
                node->getChild(getIndexOfChar(word[index]))->removeTerminate();
                terminateMet = true;
            }
        }

        else if (node->getChild(getIndexOfChar(word[index]))->getSharedStat() == 0 && node->getChild(getIndexOfChar(word[index])) != nullptr) {
            numOfNodes--;
            node->deleteChild(getIndexOfChar(word[index]));
        }

        else if (isSharedBasic == false) {
            node->getChild(getIndexOfChar(word[index]))->removeShared();
        }

        isSharedBasic = false;
    }
}


bool WordTree::isEmpty() {
    if (numOfNodes > 0) {
        return false;
    } else {
        return true;
    }
}

bool WordTree::search(string word) {
    current = head;
    returnVal = false;
    int wordSize = word.size();
    findLetters(current, 0, word, wordSize);
    return returnVal;

}

void WordTree::findLetters(Node *node, int index, string word, int size) {

    if (node != nullptr && node->getChild(getIndexOfChar(word[index])) != nullptr && index < size) {
        if (node->getChild(getIndexOfChar(word[index]))->getTerminateStat() == true) {
            returnVal = true;

            if (index == size-1)
            {
                return;
            }
        } else {
            returnVal = false;
        }

        node = node->getChild(getIndexOfChar(word[index]));


        findLetters(node, index + 1, word, word.size());
    } else {

//        if (index > size) {
//            returnVal = false;
//        }
//
//        if (index )
        returnVal = false;
        return;
    }

}



string output;
void WordTree::print() {
    string word = "";
    print_recursive(current, word);

    int size = output.size();
    output = output.substr(0, size-1);
    if(output.size() != 0) {
        cout<<output<<endl;
    }
    output.clear();
}

void WordTree::print_recursive(Node *current, string s) {
    if (current == nullptr) {
        return;
    }

    if (current->getTerminateStat() ==  true) {

        //cout<< s + " ";
        output = output + s + " ";
    }

    for (int i = 0; i <= 25; i++){
        if (current->getChild(i) != nullptr) {
            print_recursive(current->getChild(i), s + getCharAtIndex(i));
        }
    }
}

void WordTree::autocomplete(string prefix) {
    findPrefix(current, 0, prefix);
    int size = output.size();
    output = output.substr(0, size-1);
    if(output.size() != 0) {
        cout<<output<<endl;
    }
    output.clear();
}

void WordTree::findPrefix(Node *node, int index, string prefix) {

    if (index <= prefix.size() - 1) {
        if (node != nullptr && node->getChild(getIndexOfChar(prefix[index])) != nullptr) {

            node = node->getChild(getIndexOfChar(prefix[index]));
            findPrefix(node, index + 1, prefix);

            if (index == prefix.size()-1) {
                print_recursive(node, prefix); //DFS preorder is already done in a previously implemented function
                return;
            }

        } else {
            return;
        }
    }

}

void WordTree::clear() {
    deleteAll(current);
    numberOfWords = 0;
    numOfNodes = 0;
}

void WordTree::deleteAll(Node * current) {

    if (current == nullptr) {
        return;
    }

    for (int i = 0; i <= 25; i++){
        if (current->getChild(i) != nullptr) {
            deleteAll(current->getChild(i));
            current->deleteChild(i);
        }
    }
}

int WordTree::size() {
    return numberOfWords;
}

WordTree::~WordTree() {
    deleteTree();
    delete head;
}


void WordTree::deleteTree() {
    destruct(current);
    delete head;
    head = nullptr;
}

void WordTree::destruct(Node * current) {

    if (current == nullptr) {
        delete current;
        return;
    }

    for (int i = 0; i <= 25; i++){
        if (current->getChild(i) != nullptr) {
            destruct(current->getChild(i));
            delete current->getChild(i);
        }
    }
}

int WordTree::getIndexOfChar(char character) {
    switch(character) {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'q':
            return 16;
        case 'r':
            return 17;
        case 's':
            return 18;
        case 't':
            return 19;
        case 'u':
            return 20;
        case 'v':
            return 21;
        case 'w':
            return 22;
        case 'x':
            return 23;
        case 'y':
            return 24;
        case 'z':
            return 25;
        default:
            return '!';
    }
}

char WordTree::getCharAtIndex(int index) {
    switch (index) {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        case 8:
            return 'i';
        case 9:
            return 'j';
        case 10:
            return 'k';
        case 11:
            return 'l';
        case 12:
            return 'm';
        case 13:
            return 'n';
        case 14:
            return 'o';
        case 15:
            return 'p';
        case 16:
            return 'q';
        case 17:
            return 'r';
        case 18:
            return 's';
        case 19:
            return 't';
        case 20:
            return 'u';
        case 21:
            return 'v';
        case 22:
            return 'w';
        case 23:
            return 'x';
        case 24:
            return 'y';
        case 25:
            return 'z';
        default:
            return '!';
    }
}