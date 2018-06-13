#ifndef CIRCULARBUFFER_ITERATOR_H
#define CIRCULARBUFFER_ITERATOR_H

#include "CircularBuffer.h"

class Iterator {
private:
    CircularBuffer *buffer;
    CircularBuffer *backup;
public:
    explicit Iterator(CircularBuffer&);
    virtual ~Iterator();
    void start();
    void next();
    bool finish();
    int getValue();
};


#endif //CIRCULARBUFFER_ITERATOR_H
