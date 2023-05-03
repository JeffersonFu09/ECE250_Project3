#include "Trie.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main();
int main(){
    string cmd; 
    Trie * tree = new Trie();
    bool check = false;
    string word; 
    string prefix;
    string addWord;
    bool illegal;
    while (cin >> cmd ){
        if (cmd== "empty"){
            check = tree->isEmpty();
            if (check){
                cout << "empty 1" << endl;
            }else{
                cout << "empty 0" << endl; 
            }
        }else if(cmd == "i"){
            cin >> word;  
            illegal = tree->exceptionCatcher(word);

            if (!illegal){  
                check = tree->insert(word);
                if (check){
                    cout << "success" << endl;
                }else{
                    cout << "failure" << endl;
                }
            }
        }else if(cmd == "size"){
            cout << "number of words is " << tree->getNumberOfWords() << endl;
        }else if (cmd == "p"){
            if (tree->getNumberOfWords()!=0){
                tree->print(tree->getRoot(),"");
                cout << "" <<endl;
            }
        }else if (cmd == "c"){
            cin >> prefix;
            illegal = tree->exceptionCatcher(prefix);
            if (!illegal){
                tree->countPrefix(tree->getRoot(), prefix, false);
                int num =tree->getPrefixCounter();
                if (num >0){
                    cout << "count is " << tree->getPrefixCounter() << endl;
                }else{
                    cout << "not found" << endl;
                }
                tree->setPrefixCounter(0);
            }
        }else if (cmd == "exit"){
            tree->clear(tree->getRoot());
            delete tree;
            tree= nullptr;
            break;
        }else if (cmd == "e"){
            cin >> word;
            illegal = tree->exceptionCatcher(word);
            if (!illegal){
                // int lastNode = tree->getNumberOfWords();
                tree->erase(tree->getRoot(), word); // If there is a single char erase.'
                if (tree->getDeleted()){
                    cout << "success" << endl;
                }else{
                    cout << "failure" << endl;
                }
                if (tree->getNumberOfWords() ==0 && tree->getDeleted() ){
                    delete tree;
                    tree=new Trie();
                } 
                tree->setDeleted(false);
            }

        }else if(cmd == "spellcheck"){
            cin >> word;
            check = tree->wordExists(tree->getRoot(), word);
            if (check){
                cout<< "correct" << endl;
            }else{
                tree->spellCheck(tree->getRoot(), "", word);
                cout << "" << endl;
            }
        }else if (cmd == "load"){
            ifstream fin("corpus.txt");
            while (fin>>addWord){
                tree->insert(addWord);
            }
            cout<< "success" << endl;
        }else if (cmd == "clear"){
            tree->clear(tree->getRoot());
            delete tree;
            tree = new Trie();
            cout << "success" << endl;
        }
    }
}