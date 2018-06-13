#include <iostream>
#include "Iterator.h"

void Iterator::start() {
    delete this->buffer;
    this->buffer = new CircularBuffer(*backup);
}

void Iterator::next() {
    buffer->pop();
}

bool Iterator::finish() {
    return buffer->isEmpty();
}

int Iterator::getValue() {
    return buffer->head();
}

Iterator::Iterator(CircularBuffer &buffer) {
    this->backup = &buffer;
    this->buffer = new CircularBuffer(buffer);
}

Iterator::~Iterator() {
    delete this->buffer;
    delete this->backup;
}
