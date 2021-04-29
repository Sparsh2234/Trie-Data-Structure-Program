//
// Created by Sparsh Pai on 2021-03-23.
//

#ifndef PROJECT_2_250_NODE_H
#define PROJECT_2_250_NODE_H


class Node {

public:
    Node();
    void setChild(int index);
    void deleteChild(int index);
    Node * getChild(int index);
    char getChildValue(int index);
    bool getTerminateStat();
    void setTerminate();
    void removeTerminate();
    int getSharedStat();
    void setShared();
    void removeShared();
    int getChildCount();

private:
    bool isTerminate;
    bool isShared;
    int numShared = 0;
    Node * childNodes[26];
};


#endif //PROJECT_2_250_NODE_H
