/**
 * Robert Timm
 * 816006938
 * Assignment #5
 *
 * PriorityQueue.h
 * A priority queue based on the implementation of a binary heap
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include "BinaryHeap.h"
#include <cstdlib>
#include <stdexcept>
using namespace std;

// define the error: EmptyPriorityQueue
struct EmptyPriorityQueue : std::range_error {
	explicit EmptyPriorityQueue(char const* msg=NULL): range_error(msg) {}
};

template<typename T>
class Item {

public:
	int key;
	T *elem;
	int locIndex;

	Item(const int k = 0, T *e = new T(), int l = 0):
		key(k), elem(e), locIndex(l) { } //constructor
};


template <typename T>
class PQComp {
public:
	int operator()(const Item<T>& a, const Item<T>& b){
		return a.elem->getCmp() - b.elem->getCmp();
	}
};


template<typename T>
class PriorityQueue{
protected:
	typedef Item<T> _Item;
	typedef PQComp<T> _PQComp;
private:

	static const int DEF_SIZE = 800;

public:
	BinaryHeap<_Item, _PQComp> bh;

	// constructor
	PriorityQueue(int size = DEF_SIZE) : bh(size) {}

	// is the heap empty?
	bool isEmpty() const { return bh.isEmpty(); }

	// insert a new item into the heap
	void insertItem(const int k, T *e){
		bh.insert(_Item(k, e));
	}

	// build the heap using a top down traversal
	void buildHeap(){
		bh.buildHeap();
	}

	// get the min element in the heap O(1)
	T* minElement() throw(EmptyPriorityQueue){
		if(bh.isEmpty())
			throw EmptyPriorityQueue();
		return bh.findMin().elem;
	}

	// get the min key in the heap O(1)
	const int minKey() throw(EmptyPriorityQueue){
		if(bh.isEmpty())
			throw EmptyPriorityQueue();
		return bh.findMin().key;
	}

	// remove the min element in the heap O(1)
	void removeMin() throw(EmptyPriorityQueue){
		if(bh.isEmpty())
			throw EmptyPriorityQueue();
		bh.deleteMin();
	}

	// get the item at some id O(1)
	T* getLocator(int id){
		return bh.getLocator(id).elem;
	}


	// get the item at some id O(1)
	T* replaceKey(int id, int val){
		bh.getLocator(id).elem->final_distance = val;
		return bh.getLocator(id).elem;
	}

	// remove the element at some id O(1)
	void remove(int id){
		bh.remove(id);
	}


};

// output the item
template<typename T>
ostream& operator<<(ostream& out, Item<T>& item) {
	out << item.elem;
	return out;
}

// output the priority queue
template<typename T>
ostream& operator << (ostream& out, PriorityQueue<T> pq) {
	out << pq.bh;
	return out;
}


#endif
