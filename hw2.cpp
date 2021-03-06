/**
* file: hw2.cpp -  
* @author Michael Arvan
* @see "Seattle University, CPSC5600, Winter 2020"
*
*	Design
*	1. Create a Heap class
*	2. Create a SumHeap class to parallel summation
*	3. Extend heap to include prefixSums method
*
**/
#include <chrono>
#include <vector>
#include <thread>
#include <iostream>
#include <string>
#include <future>
using namespace std;


const int SEQUENTIAL_CUTOFF = 8;
const int N = 16;  // FIXME must be power of 2 for now
typedef vector<int> Data;

class Heaper{
public:
	Heaper(const Data *data) : n(data->size()), data(data){
		interior= new Data(n-1,0);
	}

	virtual ~Heaper(){
		delete interior;
	}
	
protected:
	int n;
	const Data *data;
	Data *interior;
	
	virtual int size (){
		return (n-1) + n;
	}
	
	virtual int value(int i){
		if(i < (n-1))
			return interior->at(i);
		else
			return data->at(i-(n-i));
	}
	
	virtual int parent(int i){
		return (i-1) / 2;
	}
	
	virtual int left(int i){
		return (i*2) + 1;
	}
	
	virtual int right(int i){
		return (i*2) + 2;
	}
	
	virtual bool hasLeft(int i){
		return left(i) < n;
	}
	
	virtual bool hasRight(int i){
		return right(i)< n;
	}
	virtual bool isLeaf(int i){
		if (i > n)
			return false;
		
		return true;
	}
};

class SumHeap : public Heaper{
public:
	SumHeap(const Data *data) : Heaper(data){
		calcSum(data->at(i));
	}
	
	int sum(int node){
		return value(node);
	}
	
	void prefixSums(const Data *prefix){
		
	}
	
private:
	int threadCount = 0;	
	
	void calcSum(int i){
		if(isLeaf(i)){
			return;
		}
		if (threadCount < SEQUENTIAL_CUTOFF){	
			calcSum(left(i));
			auto handle = async(launch::async, &SumHeap::calcSum, this, right(i));
			handle.wait();
			interior->at(i) = value(left(i)) + 5;//value(right(i));
			threadCount++;
		} else{
			calcSum(left(i));
			calcSum(right(i));
			interior->at(i) = value(left(i)) + value(right(i));
		}
	}
};

int main() {
    Data data(N, 1);  // put a 1 in each element of the data array
    Data prefix(N, 1);
	
    // start timer
    auto start = chrono::steady_clock::now();

    SumHeap heap(&data);
	
	for (int i =0; i < N;i++)
	cout << heap.sum(i) << endl;

    //heap.prefixSums(&prefix);

    // stop timer
    auto end = chrono::steady_clock::now();
    auto elpased = chrono::duration<double,milli>(end-start).count();

    int check = 1;
    for (int elem: prefix)
        if (elem != check++) {
            cout << "FAILED RESULT at " << check-1;
            break;
        }
    cout << "in " << elpased << "ms" << endl;
    return 0;
}