#include "Node.hpp"

Node::Node(){
    for (int i =0 ; i < 26; i ++ ){ 
        alpha[i] = nullptr;
    }
    endOfWord= false;
}

Node * Node::getAlpha(int index){
    return alpha[index]; 
}
bool Node::getEndOfWord(){
    return endOfWord;
}

void Node :: setEndOfWord(bool val){
    endOfWord = val;
}

void Node::setAlpha(int index, Node * node){
    alpha[index] = node;
}

Node::~Node(){
}