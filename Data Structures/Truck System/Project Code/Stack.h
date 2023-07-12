#include <iostream>
/*Function templates are special functions that can operate 
with generic types. This allows us to create a function 
template whose functionality can be adapted to more than 
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/

template <typename T>
class Stack
{
public:
	Stack();
	~Stack();
	bool isEmpty() const;
	int size() const;

	//Push: Place item on top of the stack
	void push(const T &newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T &stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();

private:
	struct ListNode
	{
		T item;
		ListNode *next;
	};
	ListNode *_head;
	int _size;
};

template <typename T>
Stack<T>::Stack() // Constructor
{
	this->_head = new ListNode(); // Creating head node
	this->_size = 0; // Setting size to zero
}

template <typename T>
Stack<T>::~Stack()
{
	if (this->size() > 0) // Delete head if stack not empty
	{
		delete this->_head;
	}
}

template <typename T>
bool Stack<T>::isEmpty() const // Check if the size is zero
{
	return this->_size == 0;
}

template <typename T>
int Stack<T>::size() const // Get stack size
{
	return this->_size;
}

template <typename T>
void Stack<T>::push(const T &newItem)
{
	ListNode *newNode; // Create new node and make it as new head
	newNode = new ListNode();
	newNode->item = newItem;
	newNode->next = this->_head; // Make next to old head 
	this->_head = newNode;
	this->_size++; // increase size
}

template <typename T>
void Stack<T>::getTop(T &stackTop) const // Set head node item to the reference
{
	stackTop = this->_head->item;
}

template <typename T>
void Stack<T>::pop()
{
	if (this->isEmpty()) // If empty return
	{
		return;
	}
	if (this->size() == 1) // If only 1 node is present create new empty head node.
	{
		this->_head = new ListNode();
	}
	else // Else Just move the head node to the next one
	{
		this->_head = this->_head->next;
	}
	this->_size--; // decrease size
}
