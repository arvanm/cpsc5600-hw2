#ifndef HEAPER_H
#define HEAPER_H

#include <vector>

typedef std::vector<int> Data;

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

#endif
