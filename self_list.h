#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"

template <typename T>
class SelfList {
    public: 
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Node<T>* tail;
        Method method;

    public:
        SelfList(Method method) : head(nullptr), tail(nullptr), method(method) {};

        Node<T>* front(){
            return head;
        }

        void insert(T data) {
            Node<T>* node=new Node<T>(data);
            if(head){
                node->prev=tail;
                tail->next=node;
            } else {
                head=node;
            }
            tail=node;
        }
             
        bool remove(T data) {
            Node<T>* node=head;
            while(node){
                if(node->data==data){
                    if(node->next) node->next->prev=node->prev;
                    else tail=node->prev;
                    if(node->prev) node->prev->next=node->next;
                    else head=node->next;
                    delete node;
                    node = nullptr;
                    return true;
                }
                node=node->next;
            }
            return false;
        }  

        bool find(T data) {
            Node<T>* node=head, *actual=head;
            if(node && node->data==data) {
                if(method==Count) ++(node->rep);
                return true;
            }
            node=node->next;
            while(node){
                if(node->data==data) {
                    switch (method){
                        case Move:
                            if(node->next) node->next->prev=node->prev;
                            node->prev->next=node->next;
                            node->next=head;
                            head->prev=node;
                            head=node;
                            break;
                        case Count:
                            ++(node->rep);
                            while(actual){
                                if(actual->rep<node->rep){
                                    node->prev->next=node->next;
                                    if(node->next) node->next->prev=node->prev;
                                    else tail=node->prev;
                                    if(actual->prev) actual->prev->next=node;
                                    else head=node;
                                    node->next=actual;
                                    actual->prev=node;
                                    break;
                                }
                                actual=actual->next;
                            }
                            break;
                        case Transpose:
                            swap(node->prev->data,node->data);
                            break;
                    }
                    return true;
                }
                node=node->next;
            }
            return false;
        }

        T operator [] (int index) {
            Node<T>* node=head;
            for(int i=0; i<index; ++i){
                node=node->next;
            }
            return node->data;
        }
             
        int size() {
            Node<T>* node=head;
            int size=0;
            while(node){
                ++size;
                node=node->next;
            }
            return size;
        }

        void print() {
            Node<T>* node=head;
            while(node){
                cout << node->data << ' ';
                node=node->next;
            }
            cout<<'\n';
        }

        void merge(SelfList<T>* list){
            Node<T>* node=list->front();
            while(node){
                insert(node->data);
                node=node->next;
            }
        }

        ~SelfList() {
            if(head) head->killSelf();
            head= nullptr;
        }  
};

#endif