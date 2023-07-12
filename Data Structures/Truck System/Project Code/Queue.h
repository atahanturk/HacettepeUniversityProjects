/*Function templates are special functions that can operate 
with generic types. This allows us to create a function 
template whose functionality can be adapted to more than 
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T &newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T &queueTop) const;

private:
	struct QueueNode
	{
		T item;
		QueueNode *next;
	};
	int _size;
	/* to avoid the traversal to the last node, 
	 an additional pointer to the last node is defined*/
	QueueNode *_lastNode;
	QueueNode *_firstNode;
};



template <typename T>
Queue<T>::Queue() // Constructor
{
	this->_firstNode = new QueueNode(); // Creating firstNode
	this->_lastNode = new QueueNode(); // Creating lastNode
	this->_size = 0; // Set size to 0
}

template <typename T>
Queue<T>::~Queue() // Destructor deletes the pointers
{
	if (this->size() >= 2)
	{
		delete this->_firstNode;
		delete this->_lastNode;
	}
	else if (this->size() == 1)
	{
		delete this->_firstNode;
	}
}

template <typename T>
bool Queue<T>::isEmpty() const // Check if size is zero
{
	return this->_size == 0;
}

template <typename T>
int Queue<T>::size() const // Get queue size
{
	return this->_size;
}

template <typename T>
void Queue<T>::enqueue(const T &newItem)
{
	if (this->size() == 0) // If size is zero then first and last nodes are the same and it is the newItem node
	{
		this->_firstNode->item = newItem;
		this->_firstNode->next = NULL;
		this->_lastNode = this->_firstNode;
		this->_size++; // Increase size
	}
	else
	{
		QueueNode *newNode; // Create new node if size is not zero and add to the last of the queue
		newNode = new QueueNode();
		newNode->item = newItem;
		newNode->next = NULL;
		this->_lastNode->next = newNode;
		this->_lastNode = newNode;
		this->_size++; // Increase size
	}
}

template <typename T>
void Queue<T>::getFront(T &queueTop) const // Set firstNode item to the reference
{
	queueTop = this->_firstNode->item;
}

template <typename T>
void Queue<T>::dequeue()
{
	if (this->isEmpty()) // If empty return
	{
		return;
	}
	if (this->size() == 1) // If only 1 node is present create new empty Nodes.
	{
		this->_firstNode = new QueueNode();
		this->_lastNode = new QueueNode();
	}
	else // Else Just move the first node to the next one 
	{
		this->_firstNode = this->_firstNode->next;
	}
	this->_size--; // decrease size
}
