#ifndef _QUEUE_
#define _QUEUE_

#include<iostream>
using namespace std;


template<class T>
class Queue{
	//ADT class
	private:
		T * queueArray;	//Dynamic array
		int queueSize;	//The maximum size of the queue
		int numItems; 	//Record the numbe rof itme in the queue
		int front; 		//Fornt index of queue
		int rear; 		//Back index of queue
	public:
		Queue(int size);
		~Queue();
		void enQueue(T newData);	//add new data to the queue
		void deQueue(T &item);	//del data from queue
		bool isFull();	//check queue is full or not			
		bool isEmpty();//check queue is empty or not
		void clear(); //reset the queue
		int getStockSize(); //get the queue size
		int getNumItem(); //get the number of item in queue
		T getItem(int index) const;//get the item in the Queue (getter)
		
};

template<class T>
Queue<T>::Queue(int size){
	queueArray=new T[size];//create the dynamic array
	queueSize=size;
	numItems=0;//no item in this moment
	
	front=0;
	rear=queueSize-1;
}

//delete data from queue
template<class T>
Queue<T>::~Queue(){
	delete[]queueArray;
}

//add a new item to the queue
template<class T>
void Queue<T>::enQueue(T newData){
	if(isFull()){
		std::cout<<"The queue is Full"<<std::endl;
	}else{
		//move the rear to the next location
		rear=(rear+1)%queueSize;
		
		//add the new data to the array
		queueArray[rear]=newData;
		
		//increase numItem by 1
		numItems++;
	}
}

//Delete the front item from the queue
template<class T>	
void Queue<T>::deQueue(T &item){
	if(isEmpty()){
		std::cout<<"The queue is empty! "<<std::endl;
	}else{
		//Take out the front item and store it to item
		item=queueArray[front];
		
		//Move the front to the next position
		front=(front+1) % queueSize;
		
		//reduce numItem by 1
		numItems--;
	}
}

template<class T>
bool Queue<T>::isFull(){
	return(numItems==queueSize);
}	

template<class T>			
bool Queue<T>::isEmpty(){
	//return(numItem==true);
	if(numItems==0){
		return true;
	}else{
		return false;
	}
}

//Reset Queue
template<class T>
void Queue<T>::clear(){
	front=0;
	rear=queueSize-1;
	numItems=0;
}

//get the queue size
template<class T>
int Queue<T>::getStockSize(){
	return queueSize;
}

//get the number of item in queue
template<class T>
int Queue<T>::getNumItem(){
	return numItems;
}

//get the item in the Queue (getter)
template<class T>
T Queue<T>::getItem(int index) const {
    return queueArray[(front + index) % queueSize];
}
#endif
