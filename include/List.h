#include <iostream>
using namespace std;

template<class T>
class List{
private:
    class Node{
    public:
        T data;
        Node* next;
        Node(T data_ = {}, Node* next_ = nullptr) {
            data = data_;
            next = next_;
        }
    };
    Node* head;

    void clear(){
        Node* tmp, tmp1;
        tmp = head->next;
        while(tmp){
            tmp1 = tmp;
            tmp = tmp->next;
            delete tmp1;
        }
    }
public:
    List(){
        head = new Node();
    }
    ~List() {
        Node* tmp;
        while (head) {
            tmp = head;
            head = head->next;
            delete[] tmp;
        }
    }

    Node * getNext(int ind) const {
        Node* cur = head;
        for (int i = 0; i< ind;i++){
            if(!cur->next){
                throw logic_error("invalid query index");
            }
            cur = cur->next;
        }
        return cur->next;
    }

    T getData(int ind) const {
        Node* cur = head;
        for (int i = 0; i< ind;i++){
            if(!cur->next){
                throw logic_error("invalid query index");
            }
            cur = cur->next;
        }
        return cur->data;
    }


    void insert(int ind, T val){
        Node* tmp;
        T tval1;
        T tval2;
        tmp = head;
        for (int i = 0; i < ind; i++){
            if(!tmp->next){
                throw logic_error("invalid query index");
            }
            tmp = tmp->next;
        }
        if(!tmp->next){
            throw logic_error("invalid query index");
        }
        tmp = tmp->next;
        tval1 = tmp->data;
        tmp->data = val;
        while (tmp!=nullptr){
            tval2 = tval1;
            tmp = tmp->next;
            tval1 = tmp->data;
            tmp->data = tval2;
        }
    }

    bool operator==(const List& l) const noexcept{
        Node* tmp1 = head;
        Node* tmp2 = l.head;
        while(tmp1->next){
            if (!tmp2->next || tmp1->data != tmp2->data){
                return 0;
            }
        }
        return 1;
    }

    bool operator!=(const List& l) const noexcept{
        return !(*this==l);
    }

    List& operator=(const List& l) {
        if (this != &l) {
            Node* tmp = l.head;
            this->~List();
            if (tmp) {
                head = new Node(tmp->data);
                Node* tmp2 = head;
                while (tmp->next) {
                    tmp = tmp->next;
                    tmp2->next = new Node(tmp->data);
                    tmp2 = tmp2->next;
                }
            }
        }
        return *this;
    }

    void push_back(const T val){
        if (head == nullptr){
            head = new Node(val);
        }
        Node* current = head;
        while(current->next!=nullptr){
            current = current->next;
        }
        Node* newNode = new Node(val);
        current->next=newNode;
        delete newNode;
    }
    void pop(){
        Node* current = this->head;
        if (head->next==nullptr){
            delete head;
        }
        else{
            while(current->next->next!=nullptr){
                current = current->next;
            }
            delete current->next; //точно удаляется???
            current->next=nullptr;
        }
    }

    T& operator[](int ind) const{
        Node* tmp = head;
        for (int i = 0; i< ind; i++){
            tmp = tmp->next;
        }
        return tmp->data;
    }

    void del(int ind){
        Node* tmp;
        for (int i = 0; i < ind-1; i++){
            if(!tmp->next){
                throw logic_error("invalid query index");
            }
            tmp = tmp->next;
        }
        Node* tmpIns;
        Node* tmp2;
        tmpIns = tmp->next;
        if(!tmpIns->next){
            this->pop();
        }
        else{
            tmp2 = tmpIns->next;
            tmp->next = tmp2;
        }
    }
};
