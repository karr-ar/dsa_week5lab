#include <iostream>
using namespace std;

struct Node{
    int jobID;
    string docName;
    int numberOfPages;
    Node* next;
    Node* prev;
};
class Queue{
private:
    Node* head;
    Node* tail;
    int size;
public:
    Queue(){
        head= nullptr;
        tail = nullptr;
        size =0;
    }
    ~Queue(){
        clearQueue();
    }
    void addJob(int jobID, string docName, int numberOfPages){
        Node* newNode = new Node();
        newNode->jobID = jobID;
        newNode->docName = docName;
        newNode->numberOfPages = numberOfPages;
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
    void processJob(){
        if(size == 0){
            cout << "Queue is empty. No job to process." << endl;
            return;
        }
        if(size==1){
            delete head;
            head=tail=nullptr;
        }
        else{
            Node* toDelete = head;
            head= head->next;
            delete toDelete;
            head->prev = nullptr;
        }
        size--;
    }
    void viewNextJob(){
        if(size == 0){
            cout << "Queue is empty. No job to process." << endl;
            return;
        }
        cout<<"Job ID: "<<head->jobID<<" Document Name: "<<head->docName <<" Number of pages: "<< head->numberOfPages<<endl;
    }

    bool isEmpty(){
        return size==0;
    }
    int countJobs(){
        return size;
    }
    void displayQueue(){
        Node* temp= head;
        while(temp!= nullptr){
            cout<<"Job ID: "<<head->jobID<<" Document Name: "<<head->docName <<" Number of pages: "<< head->numberOfPages<<endl;
            temp= temp->next;
        }
        cout<<"<--------------------------------------------------------------------------------------------->"<<endl;
    }
    void clearQueue(){
        while(!isEmpty()) processJob();
    }
};

int main(){

    Queue q;

    q.addJob(101, "Assignment1.pdf", 10);
    q.addJob(102, "Report.docx", 25);
    q.addJob(103, "Notes.pdf", 5);
    q.addJob(104, "LabTask.docx", 15);

    // 1. Display all jobs
    cout << "All Jobs:" << endl;
    q.displayQueue();

    // 2. Process two jobs
    q.processJob();
    q.processJob();

    // 3. Display remaining jobs
    cout << "\nRemaining Jobs:" << endl;
    q.displayQueue();

    // 4. Add a new job
    q.addJob(105, "Project.pdf", 20);

    // 5. Display next job
    cout << "\nNext Job:" << endl;
    q.viewNextJob();

    // 6. Process all remaining jobs
    while(!q.isEmpty()){
        q.processJob();
    }

    // 7. Attempt to process from empty queue
    q.processJob();

    return 0;
}