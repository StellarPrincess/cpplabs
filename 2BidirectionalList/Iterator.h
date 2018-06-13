#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T>
class Iterator {
public:
	virtual void start();
	virtual T getValue() = 0;
	virtual void next();
	virtual bool isFinished();
};

template<typename T>
void Iterator<T>::start() {

}

template<typename T>
bool Iterator<T>::isFinished() {
	return false;
}

template<typename T>
void Iterator<T>::next() {

}
#endif
