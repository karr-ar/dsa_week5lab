#include <iostream>
using namespace std;

struct Node{
    char data;
    Node* next;
    Node* prev;
};
class Stack{
private:
    Node* head;
    Node* tail;
    int size;
public:
    Stack(){
        head= nullptr;
        tail = nullptr;
        size =0;
    }
    ~Stack(){
        clearStack();
    }
    void push(char data){
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;
        if(size ==0){
            head= tail = newNode;
            newNode->prev = nullptr;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    void pop(){
        if(size==0) return;
        if(size==1){
            delete head;
            head=tail=nullptr;
        }
        else{
            Node* toDelete = tail;
            tail= tail->prev;
            delete toDelete;
            tail->next = nullptr;
        }
        size--;
    }
    char top(){
        if(size==0) return '\0';
        return tail->data;  
    }

    bool isEmpty(){
        return size==0;
    }
    bool checkBalance(string expression){
    for(int i = 0; i < expression.size(); i++){
        char c = expression[i];

        if(c == '(' || c == '{' || c == '['){
            push(c);
        }
        else if(c == ')'){
            if(top() != '(') return false;
            pop();
        }
        else if(c == '}'){
            if(top() != '{') return false;
            pop();
        }
        else if(c == ']'){
            if(top() != '[') return false;
            pop();
        }
    }
    return isEmpty();
}
    void displayStack(){
        Node* temp= tail;
        while(temp!= nullptr){
            cout<<temp->data<<endl;
            temp= temp->prev;
        }
    }
    void clearStack(){
        while(!isEmpty()) pop();
    }
};

int main(){
    Stack st;

    string tests[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])"
    };

    for(int i = 0; i < 7; i++){
        cout << tests[i] << " -> ";

        if(st.checkBalance(tests[i]))
            cout << "Balanced";
        else
            cout << "Not Balanced";

        cout << endl;

        st.clearStack();
    }

    return 0;
}