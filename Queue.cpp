#include "Queue.h"

Queue::Queue()
{
	front = 0;
	rear = -1;
	size = 0;

}

bool Queue::isFull()
{
	return (size == MAX_SIZE);
}

bool Queue::isEmpty()
{
	return size == 0;
}

void Queue::Enqueue(int x)
{
	if (isFull())
		return;
	else {
		rear = rear + 1 % MAX_SIZE;
		arr[rear] = x;
		size++;

	}


}

int Queue::Dequeue()
{
	if (isEmpty())
		return 0;
	else
	{
		int temp = arr[front];
		front = (front + 1) % MAX_SIZE;
		size--;
		return temp;

	}

}

void Queue::clear()
{
	size = 0;
	rear = -1;
	front = 0;

}

int Queue::queue_size()
{
	return size;
}

int Queue::peek()
{
	return arr[front];
}




