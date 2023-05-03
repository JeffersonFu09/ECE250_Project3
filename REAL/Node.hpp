using namespace std;

class Node{
    private: 
        Node * alpha[26];
        bool endOfWord;
    public: 
        Node();
        ~Node();
        Node * getAlpha(int index); 
        bool getEndOfWord();
        void setEndOfWord(bool val);
        void setAlpha(int index, Node * node);
};