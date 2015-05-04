/* Developer: Shiwei Huang
 * Purpose: In addition to the traditional Queue operations, this program will add another class called mikeQ which is a derived class under Queue.
 * This mikeQ class has two methods:
 * enMike (x) - enqueue the integer x in the normal manner except if it is 10 or greater than the front of the queue, then insert the value at the front rather than the usual rear.
 * deMike (x) - dequeue x items from the front;
 * Input: The input consists of a character ('e' for enqueue, 'd' for dequeue, and 'q' for quit) and an integer to enqueue.
 * Output: The program should display the proper integers as desired by the user. 
 * Note: 
 * 1) A class queue implemented as a circular array that stores integers. The methods to be implemented should be called enqueue (x), dequeue(), front(), empty(), and full().
 * 2) In this exercise, the maximum number of items that need to be stored is 100. 
 * 3) The derived class of queue is called mikeQ. This class should have access to the methods of the queue class and include two new methods: enMike(x) and deMike(x).
 */

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <math.h>  

using namespace std;
const int MAXQUEUESIZE = 100; // The maximum number of items that need to be stored is 100.

// class queue
class queueType {

public:
	bool empty ();
	bool full ();
	int front ();
	void enqueue ( int x );
	void dequeue ();
	queueType (); // constructor
protected:
	int count; //variable to count number of elements in the queue;
	int queueFront; //variable to point to the first element of the queue;
	int queueRear; //variable to point to the last element of the queue;
	int *list; //pointer to point to the array that holds the queue elements;

};

//constructor
queueType :: queueType () {
	queueFront = 0; //front of the queue;
	queueRear = MAXQUEUESIZE -1; //read of the queue;
	count = 0; //current number of integers in the queue;
	list = new int [ MAXQUEUESIZE ]; //create a queue implemented as a circular array with a fixed number.
}

//Function to determine whether the Queue is empty;
//Precondition: queue exists;
//Postcondition: returns true if the queue is empty, otherwise returns false;
bool queueType :: empty () {
	if ( count == 0 ) {
		return true;
	}
	else {
		return false;
	}
}


//Function to determine whether the queue is full;
//Precondition: queue exists;
//Postcondition: return true if the queue is full, otherwise returns false;
bool queueType :: full () {
	if ( count == MAXQUEUESIZE ) {
		return true;
	}
	else {
		return false;
	}
}

//Function to return the first element of the queue;
//Precondition: The queue exists and is not empty;
//Postcondition: The first element of the queue is returned;
int queueType :: front () {
	if ( count != 0 ) {
		return list [queueFront];
	}
	else {
		cout << "Queue is empty. First element cannot be returned." << endl;
	}
}

//Function to add newElement to the queue;
//Precondition: the queue exists and is not full;
//Postcondition: The queue is changed and newElement is added to the queue;
void queueType :: enqueue ( int newElement ) {
	if ( !full() ) {
		queueRear = ( queueRear + 1 ) % MAXQUEUESIZE;
		count ++;
		list [ queueRear ] = newElement;
	}
	else {
		cout << "Cannot add new element to a full queue." << endl;
	}
}

//Function to remove the first element of the queue;
//Precondition: The queue exists and is not empty;
//Postcondition: The queue is changed and the first element is removed from the queue;
void queueType :: dequeue () {
	if ( !empty() ) {
		count --;
		queueFront = ( queueFront + 1 ) % MAXQUEUESIZE;
	}
	else {
		cout << "Cannot move from an empty queue." << endl;
	}
}

//derived class under queue. mikeQ contains two new methods: enMike (x) and deMike (x);
class mikeQ : public queueType {
public:
	void enMike ( int x );
	void deMike ( int xItems );
};

//Function to enqueue the integer x in the normal manner if number is less than 10; If the interger is 10 or greater, insert the number at the front of the array queue;
//Precondition: queue exists and is not full.
//Postcondition: The queue is changed and new integer is added to the queue. The location of the added integer depends on whether the integer is less than or greater or equal than 10. 
void mikeQ  :: enMike ( int x ) {
	if ( !full() ) {
		if ( x < 10 ) {
			enqueue (x);
		}
		else { //  ( x >= 10 )
			mikeQ tmpQ; // make a tmpQ to store all elements from my first queue;
			//deQueue all existing elements from my first queue and enqueue all elements to my temp queue;
			while ( !empty() ) {
				int tmp = front();
				dequeue ();
				tmpQ.enqueue (tmp);
			}
			//insert the element to my first queue;
			enqueue (x);
			//deQueue all elements from my temp Queue and enqueue the elements from temp Queue to first Queue;
			while ( !tmpQ.empty() ) {
				int tmp = tmpQ.front();
				tmpQ.dequeue();
				enqueue (tmp);
			}
		} //else
	} // if

	else { // if first Queue is full;
		cout << "Cannot add new element to full queue." << endl;
	}
} //enMike;


//Function to dequeue x number of items from the front;
//Precondition: dequeue exists and number of existing integers are greater than or equal to x items that need to be dequeted;
//Postcondition: The queue is changed and x number of items have been dequeued from the queue;
void mikeQ :: deMike ( int x ) {
	if ( x <= count ) { // check queue has enough elements to deQueue;
		for ( int i = 0; i < x; i++ ) {
			dequeue ();
		}
	}
	else {
		cout << "error - cannot dequeue more elements than queue has" << endl;
	}
}

int main () {
   mikeQ q;      // create a Mike queue
   int   item;   // item to add to queue
   char  ch;     // character code
   cout << "enter e(nter), d(equeue), or q(uit): ";
   cin >> ch;
   while ( ch != 'q' ) {
   	if ( ch == 'e' ) {
   		if ( !q.full() ) {
   			cout << "number: ";
   			cin >> item;
   			q.enMike ( item );
   		}
   		else {
   			cout << "error - queue is full" << endl;
   		}
   	}

   	else if ( ch == 'd' ) {
   		if ( ! q.empty() ) {
   			cout << q.front () << endl;
   			q.deMike (1);
   		}
   		else {
   			cout << "error- empty queue" << endl;
   		}
   	}

   	else {
   		cout << "error in code - ignored" << endl;
   	}

   	cout << "enter e(nter), d(equeue), or q(uit):";
   	cin >> ch;
   } //while

   while ( ! q.empty () ) {
   	cout << q.front () << endl;
   	q.dequeue ();
   }

   return 0;

} // main()


