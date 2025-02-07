#pragma once
#include<iostream>
#define MAX_SIZE 50
using namespace std;

class Queue
{
private:
	int rear, front;
	int size;
	int arr[MAX_SIZE];

public:
	Queue();
	bool isFull();
	bool isEmpty();
	void Enqueue(int x);
	int Dequeue();
	void clear();
	int queue_size();
	int peek();


};

