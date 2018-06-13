#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

class CircularBuffer {
	friend class Iterator;
private:
	// ������
    int *arr;
    // ������
    int size;
    // ���������� ���������
    int engaged;
public:
	class Iterator {
	private:
		// ������� ���������
	    int pos;
	    // ��������� �� ����������� �����
	    CircularBuffer *buffer;
	public:
		// �����������: ������� �� ����, ��������� ��������� �� ������������ �� ������ �����
	    explicit Iterator(CircularBuffer & buf) : pos(0), buffer(&buf) {}
	    // ���������� ������, �.�. ������� ������
	    virtual ~Iterator() {}
	    // ������������� �������� �� ������
	    void start() {
		    pos = 0;
		}
		// �������� ������� �����
	    void next() {
		    ++pos;
		}
		// �������� �� �����: ���� ������� ����� �� ������� ������� - �����
	    bool finished() {
		    return pos == buffer->engaged;
		}
	    int getValue() {
	    	// ������ ����� �� ����� �� ��������� �������
	    	if (pos == buffer->engaged) {
	    		throw "Can't get from outside of engaged";
			}
		    return buffer->arr[pos];
		}
	};
    explicit CircularBuffer(int);
    explicit CircularBuffer(CircularBuffer&);
    virtual ~CircularBuffer();
    void pushBack(int);
    int pop();
    int head();
    int getSize();
    void erase();
    bool isEmpty();
};


#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
