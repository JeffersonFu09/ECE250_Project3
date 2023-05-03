#include "Node.hpp"
#include <string>
using namespace std;

class Trie{
    private:
        Node * node;
        Node * root;
        int numberOfWords;
        int prefixCounter=0;
        bool deleted= false;
    public:
        Trie();
        void setDeleted(bool val);
        bool getDeleted(); 
        Node * getRoot();
        bool isEmpty();
        bool insert(string word);
        int getNumberOfWords();
        void print(Node * ptr, string subString); 
        int getPrefixCounter();
        void setPrefixCounter(int num);
        void countPrefix(Node* ptr, string prefix, bool check);
        Node* erase(Node * ptr, string word);
        void spellCheck(Node * ptr, string substring, string word);
        bool wordExists(Node * ptr, string word);
        bool exceptionCatcher(string word);
        void clear(Node * ptr);
        ~Trie();
};