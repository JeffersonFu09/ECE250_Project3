#include "Trie.hpp"
#include "Illegal_Exception.hpp"
#include <string>
#include <iostream> 
using namespace std;
Trie::Trie(){
    root = new Node();
    numberOfWords = 0;
};
Trie::~Trie(){
}

Node * Trie::getRoot(){
    return root;
}
void Trie::setDeleted(bool val){
    deleted = val;
}
bool Trie::getDeleted(){
    return deleted;
}

bool Trie::exceptionCatcher(string word){
    try{
        for(int i =0; i < word.length(); i ++ ){
            if ('A'> char(word[i]) || 'Z'<char(word[i]) ){
                throw illegal_exception();
            }
        }
        return false;
    }catch(illegal_exception){
        cout << "illegal argument" << endl;
        return true;
    }
}

bool Trie::isEmpty(){
        return (numberOfWords==0); 
    }

bool Trie::insert(string word){
    Node * temp = root; 
    int count = 0;
    int index = 0;
    while(count != word.length()){
        char letter = word[count];
        index = letter - 'A';
        if (temp->getAlpha(index) == nullptr){
            temp->setAlpha(index, new Node());
        }
        temp= temp->getAlpha(index); 
        if (count== word.length()-1){
            if(temp->getEndOfWord() == true){
                return false;
            }
            temp->setEndOfWord(true);
            numberOfWords++; 
        }
        count++; 
    }
    return true; 

}

int Trie::getNumberOfWords(){
    return numberOfWords;
}

void Trie::print(Node * curNode, string subString){
    if(curNode == nullptr){
        return;
    }
    if (curNode->getEndOfWord()){
        cout<< subString << " ";
    }
    for (int i =0; i < 26 ; i ++ ){
        char letter = 'A' +i;
        print(curNode->getAlpha(i), subString+letter);
    }
}

void Trie::countPrefix(Node * curNode, string prefix, bool check){
    if(curNode == nullptr){
        return ;
    }
    if(check || prefix.length() == 0){
        check = true;
        if (curNode->getEndOfWord()){
            setPrefixCounter(getPrefixCounter()+1);
        }
    }
    if (check){ // Once i'm at the end of my prefix, i can keep recursively 
        for (int i =0 ; i < 26; i++){
            countPrefix(curNode->getAlpha(i), prefix, check);
        }
    }else{// Recursive down to the end of the prefix
        int index = prefix[0] - 'A'; 
        countPrefix(curNode->getAlpha(index), prefix.substr(1,prefix.size()-1), check);
    }

}

int Trie::getPrefixCounter(){
    return prefixCounter;
}

void Trie::setPrefixCounter(int num){
    prefixCounter = num;
}

Node* Trie::erase(Node * curNode, string word){
    bool anyChildren = false;
    if (curNode == nullptr){
        return nullptr;
    }
    if (word.length() == 0){
        // cout << "HERE 1" << endl;
        if (curNode->getEndOfWord()){
            // cout << "HERE 2" << endl;
            numberOfWords--;
            setDeleted(true);
            curNode->setEndOfWord(false);
        }

        for (int i =0 ; i < 26 ; i ++ ){
            if (curNode->getAlpha(i)!= nullptr){
                anyChildren = true;
                break;
            }
        }
        if (!anyChildren){
            delete curNode;
            curNode = nullptr;
        }
        return curNode;
    }
    int index = word[0] - 'A';
    curNode->setAlpha(index, erase(curNode->getAlpha(index), word.substr(1, word.size()-1)));
    for (int i =0 ; i < 26 ; i ++ ){ 
        if (curNode->getAlpha(i)!=nullptr){
            anyChildren= true;
            break;
        }
    }
    if (!anyChildren && !curNode->getEndOfWord()&&getDeleted()){
        delete curNode;
        curNode = nullptr;
    }
    return curNode;
}

void Trie::spellCheck(Node * curNode, string subword, string word){
    if (curNode == nullptr){
        return;
    }
    int index = word[0]-'A';
    if (curNode->getAlpha(index) == nullptr && subword != ""){
        print(curNode, subword);
        return;
    }
    spellCheck(curNode->getAlpha(index), subword+word[0], word.substr(1,word.size()-1) );
}

bool Trie::wordExists(Node* curNode, string word){
    if (curNode == nullptr){
        return false;
    }
    int index = word[0] - 'A';
    if (word.length()==0){
        if (curNode->getEndOfWord()){
            return true;
        }else{
            return false;
        }
    }
    return wordExists(curNode->getAlpha(index), word.substr(1, word.size()-1));
}

void Trie::clear(Node * curNode){
    for(int i =0 ; i < 26 ; i++){
        if (curNode->getAlpha(i)!=nullptr){
            clear(curNode->getAlpha(i));
        }
    }
    // if (curNode == root){
    //     return;
    // }
    delete curNode; // Maybe see if we have to check if it's not the root node, then we delete the root node elsewhere
    curNode = nullptr;
    return;
}
