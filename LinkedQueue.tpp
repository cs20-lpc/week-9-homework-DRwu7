template <typename T>
LinkedQueue<T>::LinkedQueue() {
    this->length = 0;
    head = nullptr;
    last = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    this->length = 0;
    head = nullptr;
    last = nullptr;
    
    // Use the public enqueue method to safely copy elements
    Node* curr = copyObj.head;
    while (curr != nullptr) {
        enqueue(curr->value);
        curr = curr->next;
    }
}

template <typename T>
void LinkedQueue<T>::clear() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    
    // Reset state variables
    head = nullptr;
    last = nullptr;
    this->length = 0;
}

// BRANCH MODIFIED: Queue Operations

template <typename T>
T LinkedQueue<T>::back() const {
    if (isEmpty()) {
        throw string("back: error, queue is empty");
    }
    return last->value;
}

template <typename T>
void LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        throw string("dequeue: error, queue is empty");
    }
    
    Node* oldHead = head;
    
    // Move head to the next node
    head = head->next;
    
    // Delete the old head
    delete oldHead;
    
    this->length--;
    
    // Special case: if the queue is now empty, 'last' must also be nullptr
    if (this->length == 0) {
        last = nullptr;
    }
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem) {
    Node* newNode = new Node(elem);
    
    // Case 1: Queue is empty
    if (isEmpty()) {
        head = newNode;
        last = newNode;
    } 
    // Case 2: Queue is not empty
    else {
        last->next = newNode;
        last = newNode; // Update 'last' to the new node
    }
    
    this->length++;
}

template <typename T>
T LinkedQueue<T>::front() const {
    if (isEmpty()) {
        throw string("front: error, queue is empty");
    }
    return head->value;
}

template <typename T>
int LinkedQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return this->length == 0;
}
