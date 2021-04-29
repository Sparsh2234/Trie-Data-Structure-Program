//
// Created by Sparsh Pai on 2021-03-23.
//

#include "Node.h"
#include "WordTree.h"

WordTree * funcAccessor;

Node::Node() {
    isTerminate = false;
    isShared = false;
    //Initialize all child nodes to be null
    for (int i = 0; i < 26; i++) {
        childNodes[i] = nullptr;
    }
}

void Node::setChild(int index) {
    Node * character = new Node();
    childNodes[index] = character;
}

void Node::deleteChild(int index) {
    delete childNodes[index];
    childNodes[index] = nullptr;
}

Node * Node::getChild(int index) {
    return childNodes[index];
}

char Node::getChildValue(int index) {
    return funcAccessor->getCharAtIndex(index);
}

void Node::setTerminate() {
    isTerminate = true;
}

void Node::removeTerminate() {
    isTerminate = false;
}

bool Node::getTerminateStat() {
    return isTerminate;
}

void Node::setShared() {
    numShared++;
}

void Node::removeShared() {
    numShared--;
}

int Node::getSharedStat() {
    return numShared;
}

//int Node::getChildCount() {
//    return childNodes.
//}