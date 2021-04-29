#include <iostream>

#include "WordTree.h"
#include "illegal_exception.h"
int main() {

    std::string line;
    WordTree tree;
    bool error;

    while (true) {

        if (cin.eof()) {
            break;
        }

        getline(cin, line);

        if (line == "exit") {
            break;
        }

        int pos = line.find(" ");
        std::string cmd = line.substr(0, pos);
        std::string obj = line.substr(pos + 1);


        if (cmd == "i") {
            pos = obj.find(" ");
            string word = obj.substr(0, pos);
            bool isIllegal = false;

            try {

                for (int i = 0; i < word.size(); i++) {
                    char ch = word[i];

                    if(tree.getIndexOfChar(ch) == '!') {
                        isIllegal = true;
                    }

                    if (isIllegal) {
                        throw illegal_exception();
                    }
                }

            } catch (illegal_exception p) {
                cout<<"illegal argument"<<endl;
            }


            if (!isIllegal) {
                error = tree.insert(word);

                if (error) {
                    cout << "success"<<endl;
                } else {
                    cout << "failure" <<endl;
                }
            }

        }

        if (cmd == "e") {
            pos = obj.find(" ");
            string word = obj.substr(0, pos);

            bool isIllegal = false;

            try {

                for (int i = 0; i < word.size(); i++) {
                    char ch = word[i];

                    if(tree.getIndexOfChar(ch) == '!') {
                        isIllegal = true;
                    }

                    if (isIllegal) {
                        throw illegal_exception();
                    }
                }

            } catch (illegal_exception p) {
                cout<<"illegal argument"<<endl;
            }

            if (!isIllegal) {
                error = tree.erase(word);

                if (!error) {
                    cout << "success"<<endl;
                } else {
                    cout << "failure"<<endl;
                }
            }
        }

        if (cmd == "s") {
            pos = obj.find(" ");
            string word = obj.substr(0, pos);

            bool isIllegal = false;

            try {

                for (int i = 0; i < word.size(); i++) {
                    char ch = word[i];

                    if(tree.getIndexOfChar(ch) == '!') {
                        isIllegal = true;
                    }

                    if (isIllegal) {
                        throw illegal_exception();
                    }
                }

            } catch (illegal_exception p) {
                cout<<"illegal argument"<<endl;
            }

            if (!isIllegal) {
                error = tree.search(word);
                if (error) {
                    cout<< "found "+word<< endl;
                } else {
                    cout<<"not found"<<endl;
                }
            }
        }

        if (cmd == "print") {
            tree.print();
        }

        if (cmd == "autocomplete") {
            pos = obj.find("*");
            string prefix = obj.substr(0, pos);
            tree.autocomplete(prefix);
        }

        if (cmd == "empty") {
            error = tree.isEmpty();
            if (error) {
                cout<<"empty 1"<< endl;
            } else {
                cout << "empty 0" << endl;
            }
        }

        if (cmd == "clear") {
            tree.clear();
            cout<<"success"<<endl;
        }

        if (cmd == "size") {
            int size = tree.size();
            if (size != 0) {
                cout<<"number of words is ";
                cout<<size<< endl;
            } else {
                cout << "number of words is 0" << endl;
            }
        }

    }

    return 0;
}
