template <typename T>
ArrayQueue<T>::ArrayQueue(int size)
: maxSize(size), frontPos(0), backPos(0) {
    buffer = new T[maxSize];
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& rightObj) {
    if (this != &rightObj) {
        delete[] buffer;
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] buffer;
}

template <typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& copyObj) {
    this->length = copyObj.length;
    maxSize = copyObj.maxSize;
    frontPos = copyObj.frontPos;
    backPos = copyObj.backPos;

    buffer = new T[maxSize];
    for (int i = 0; i < maxSize; ++i) {
        buffer[i] = copyObj.buffer[i];
    }
}

template <typename T>
T ArrayQueue<T>::back() const {
    if (isEmpty()) {
        throw string("back: error, queue is empty");
    }
    return buffer[backPos];
}

template <typename T>
void ArrayQueue<T>::clear() {
    this->length = 0;
    frontPos = 0;
    backPos = 0;
}

template <typename T>
void ArrayQueue<T>::dequeue() {
    if (isEmpty()) {
        throw string("dequeue: error, queue is empty");
    }
    frontPos = (frontPos + 1) % maxSize;
    this->length--;
}

template <typename T>
void ArrayQueue<T>::enqueue(const T& elem) {
    if (isFull()) {
        // Simulation 1 logic: silently reject if full
        throw string("enqueue: error, queue is full, customer turned away");
    }

    // Advance backPos before inserting, handle wrap-around
    backPos = (backPos + 1) % maxSize;

    if (isEmpty()) {
        // If empty, backPos must point to the front element.
        backPos = frontPos;
    } else if (this->length > 0) {
        // If not empty, the next back element is (backPos + 1) % maxSize.
        // We revert backPos to correctly index the last element.
        backPos = (backPos - 1 + maxSize) % maxSize;
    }


    if (isEmpty()) {
        buffer[backPos] = elem;
    } else {
        buffer[(frontPos + this->length) % maxSize] = elem;
    }


    if (isEmpty()) {
        buffer[frontPos] = elem;
    } else {
        buffer[(backPos + 1) % maxSize] = elem;
    }

    buffer[backPos] = elem;
    this->length++;
}

template <typename T>
T ArrayQueue<T>::front() const {
    if (isEmpty()) {
        throw string("front: error, queue is empty");
    }
    return buffer[frontPos];
}

template <typename T>
int ArrayQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayQueue<T>::isFull() const {
    return this->length == maxSize;
}