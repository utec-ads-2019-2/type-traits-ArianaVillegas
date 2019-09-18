#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"

template <typename Tr>
class TraitsList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;

    private:
        Node<T>* head;
        Operation cmp;

        bool find(T data, Node<T> **(&pointer)) {
            while(*pointer){
                if(cmp((*pointer)->data,data)) {
                    if (data == (*pointer)->data){
                        return true;
                    }
                } else {
                    return false;
                }
                pointer=&((*pointer)->next);
            }
            return false;
        }
              
    public:
        TraitsList() : head(nullptr) {};
             
        bool insert(T data) {
            Node<T>** temp = &head;
            if (!find(data, temp)) {
                Node<T>* node=new Node<T>(data);
                node->next=(*temp);
                (*temp)=node;
                return true;
            }
            return false;
        }
             
        bool remove(T data) {
            Node<T>** temp = &head;
            if (find(data, temp)) {
                Node<T>* next = nullptr;
                if((*temp)->next) next=(*temp)->next;
                delete (*temp);
                (*temp)=next;
                return true;
            }
            return false;
        }  

        bool find(T data) {
            return find(data,&head);
        }

        T operator [] (int index) {
            Node<T>* temp = head;
            int t=size();
            if(t>index){
                while(index>0){
                    temp=temp->next;
                    --index;
                }
                return temp->data;
            }
            return -1;
        }
             
        int size() {
            int size=0;
            Node<T>* temp = head;
            while(temp){
                temp=temp->next;
                ++size;
            }
            return size;
        }

        void print() {
            Node<T>* temp = head;
            while(temp){
                cout << temp->data << ' ';
                temp=temp->next;
            }
        }

        ~TraitsList() {
            if(head) head->killSelf();
            head= nullptr;
        }         
};

#endif