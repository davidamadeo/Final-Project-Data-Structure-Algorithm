#include <iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "holder.h"
using namespace std;

template <typename T>
struct NODE{
	T data;
	NODE<T>* link;
};

template <typename T>
class LinkedList{
	public:
		LinkedList();
		~LinkedList();
		void insert(const T& item);
		NODE<T>* getFirst();
		void deleteSpecificItem(string name);
		
	private:
		NODE<T>* first;
		NODE<T>* last;

};

template <typename T>
NODE<T>* LinkedList<T>::getFirst(){
	return first;
}


template <typename T>
LinkedList<T>::LinkedList()
{
	first = NULL;
	last = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    if(first != NULL)
    {   
        NODE<T> *curr, *soon;
        curr = this->first->link;
        while(curr != NULL) 
        {
            if(curr->link != NULL)
            {
                soon = curr->link;
                delete curr;
                curr = soon;
            }
            else
            {
                delete curr;
                break;
            }

        }
    }
    delete this->first;
    delete this->last;
}

template <typename T>
void LinkedList<T>::insert(const T& item){
	NODE<T>* newNode = new NODE<T>;
	newNode->data = item;
	newNode->link = NULL;
	
	if (first == NULL){
		first = newNode;
		last = newNode;
	}
	
	else{
		last->link = newNode;
		last = newNode;
	}
}

template <typename T>
void LinkedList<T>::deleteSpecificItem(string name){
	if (first!=NULL){
	NODE<T> *curr = first;
		NODE<T> *prev = NULL;
		while(curr!=NULL){
			if(curr->data.getName() == name){
				break;
			}
			else{
				prev = curr;
				curr = curr->link;
			}
		}
		if (curr == NULL){
			cout<<"INVALID HOLDER"<<endl;
		}
		else{
			if (curr->data.getAmount() == 0){
				if(curr == first){
						first = first->link;
					}
					else{
						prev->link = curr->link;
						last = prev;
					}
					delete curr;
					cout<<"You have successfuly removed "<<name<<endl;
			}
			else{
				cout<<"You still got balance or due credit on "<<name<<endl;
				cout<<"Action denied"<<endl;
			}
		}	}
}		
#endif
