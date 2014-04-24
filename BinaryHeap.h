/**
 * Robert Timm
 * 816006938
 * Assignment #5
 *
 * BinaryHeap.h
 * A binary heap with the added ability to remove elements at a specific
 *  location based on the element's given location in the heap's array.
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <stdexcept>
#include <vector>

using namespace std;

// define the error: EmptyHeap
struct EmptyHeap : std::range_error {
  explicit EmptyHeap(char const* msg=NULL): range_error(msg) {}
};

template <typename T, typename C>
class BinaryHeap {

public:

	// constructor
	BinaryHeap(int size = DEF_SIZE) {
		currentSize = 0;
		getNewArray(size);
		locator.resize(size);
	}

	// find the min element in the heap O(1)
	T& findMin() throw(EmptyHeap) {
		if(isEmpty()) throw EmptyHeap();
		return array[0];
	}

	// get the main data structure for this heap
	T* getarray() {return array;}

	// get an element by it's id O(1)
	T getLocator(int id) throw(EmptyHeap);

	int getSize() { return currentSize; }			// get the size of this heap
	bool isEmpty()const{return currentSize == 0;}	// is the heap empty?
	void buildHeap();							// build the heap (top-down)
	void insert(const T& x);					// insert a new element into the heap O(1)
	void deleteMin() throw(EmptyHeap);			// delete the min element in the heap O(1)
	void walkDown(int hole);					// walk down the heap starting from some location
	void remove(int id) throw(EmptyHeap);		// remove an element at a specified location O(1)

private:
	C comp;				// used to compare to elements
	int currentSize;	// the current size of the heap
	T *array;			// main data structure
	int length;			// the length of the data structure (array)
	vector<int> locator;// used to located items in the heap in O(1)

	// a defined starting size of the heap
	static const int DEF_SIZE = 800;

	// create a new array based on a new size
	void getNewArray(int newSize) {
		array = new T[newSize];
		length = newSize;
	}

	// validate the size of the data structure
	void checkSize(){
		if (currentSize == length) {
			T *oldArray = array;
			getNewArray(2*currentSize);
			for (int i = 0; i < currentSize; i++) {
				array[i] = oldArray[i];
			}
			delete [] oldArray;
		}
	}
};

template<typename T, typename C>
void BinaryHeap<T, C>::buildHeap() {
	for (int i = (currentSize-2)/2; i >= 0; i--)
		walkDown(i);
}

template<typename T, typename C>
T BinaryHeap<T, C>::getLocator(int id) throw(EmptyHeap) {
	if(isEmpty())
		throw EmptyHeap();
	return array[locator[id]];
}

template<typename T, typename C>
void BinaryHeap<T, C>::remove(int id) throw(EmptyHeap) {
	if(isEmpty())
		throw EmptyHeap();

	array[locator[id]] = array[ --currentSize ];
	walkDown(0);
}

template<typename T, typename C>
void BinaryHeap<T, C>::insert(const T& x)
{
	checkSize();
	int hole = currentSize++;
	for( ; hole > 0 && comp(array[(hole-1)/2], x) > 0; hole = (hole-1)/2){
		array[hole] = array[(hole-1)/2];
	}
	array[hole] = x;
}

template<typename T, typename C>
void BinaryHeap<T, C>::deleteMin() throw(EmptyHeap)
{
	array[0] = array[ --currentSize ];
	walkDown(0);
}

template<typename T, typename C>
void BinaryHeap<T, C>::walkDown(int hole)
{
	int child;
	T key = array[hole];
	for( ; 2*hole+1 < currentSize; hole = child){
		child = 2*hole+1;
		if(child != currentSize-1 && comp(array[child], array[child+1]) > 0)
			child++;
		if(comp(key, array[child]) > 0)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = key;

	for(int i = 0; i < DEF_SIZE; ++i){
		locator[array[i].elem->getKey()] = i;
	}
}

template<typename T, typename C>
ostream& operator<<(ostream& out, BinaryHeap<T, C>& bh) {
	T* array = bh.getarray();
	for(int i = 0; i < bh.getSize(); ++i) {
		out << array[i];
	}
	return out;
}


#endif
