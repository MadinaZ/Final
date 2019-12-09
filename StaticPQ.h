//  Programmer: Hiroaki Takeuchi
//  Programmer's ID: 1718699
#include "safedelete.h"
#include "StaticArray.h"

#include <algorithm>
#include <list>
using namespace std;

#ifndef StaticPQ_h
#define StaticPQ_h



template<typename V, int CAP>
class StaticPQ
{
	V* values;
	int siz;
	V dummy;
	int keeppop_counter;
	StaticArray<V,CAP> keep;


public:
	StaticPQ();
	StaticPQ<V, CAP>& operator=(const StaticPQ<V, CAP>&);
	int index(int) const;
	int capacity() { return CAP; }
	void push(const V&);
	void pop();
	V top() const { return siz == 0 ? V() : values[0]; }
	int size() const { return siz; }
	int sizeKeep() const { return keeppop_counter; }
	bool empty() const { return siz == 0 ? true : false; }
	void clear() {siz = 0; }

	void topKeepandPop(); //pop and keep the popped object in a static array
	void keepPushBack(); // push the kept objects back to the PQ
};

template<typename V, int CAP>
StaticPQ<V, CAP>::StaticPQ()
:values(new V[CAP])
,siz(0)
,dummy(V())
,keeppop_counter(0)
{
	for(int i = 0; i < CAP; i++)
		values[i] = V();
};

template<typename V, int CAP>
StaticPQ<V, CAP>& StaticPQ<V,CAP>::operator=(const StaticPQ<V, CAP>& ori)
{
	if(this == &ori) { return *this; }

	safedeleteArray(values);
	values = new V[CAP];
	for(int i = 0; i < CAP; i++)
		values[i] = ori.values[i];
	siz = ori.siz;
	dummy = ori.dummy;
	keeppop_counter = ori.keeppop_counter;

	return *this;
}


template<typename V, int CAP>
void StaticPQ<V, CAP>::push(const V& value)
{
	values[siz] = value;
	int index = siz;
	int p_index = (index + 1) / 2 - 1;
	++siz;

	while(p_index >= 0)
	{
		if(values[p_index] < values[index])
		{
			swap(values[index], values[p_index]);
			index = p_index;
			p_index = (index + 1) / 2 - 1;
		}
		else
			break;
	}
}

template<typename V, int CAP>
void StaticPQ<V, CAP>::pop()
{
	if(siz == 0) return;

	values[0] = values[--siz];
	int index = 0, big_index = 0;
	int l_index = index * 2 + 1; if(l_index > siz) return;
	int r_index = index * 2 + 2;

	while(true)
	{
		if(r_index > siz)
			big_index = l_index;
		else
		{
			if(values[r_index] < values[l_index])
				big_index = l_index;
			else
				big_index = r_index;
		}
		if(values[index] < values[big_index])
		{
			swap(values[big_index], values[index]);
			index = big_index;
			l_index = index * 2 + 1; if(l_index > siz) break;
			r_index = index *  2 + 2;
		}
		else
			break;
	}
}

template<typename V, int CAP>
void StaticPQ<V, CAP>::topKeepandPop()
{
	keep[keeppop_counter++] = top();
	pop();
}

template<typename V, int CAP>
void StaticPQ<V, CAP>::keepPushBack()
{
	for(int i = 0; i < keeppop_counter; i++)
		push(keep[i]);

	keeppop_counter = 0;
}

#endif
