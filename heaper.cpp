#include "heaper.h";

Heaper::Heaper(const Data *data) : n(data->size()), data(data){
	interior= new Data(n-1,0);
}

~Heaper(){
	delete interior;
}
	
int Heaper::size (){
	return (n-1) + n;
}
	
int Heaper::value(int i){
	if(i < (n-1))
		return interior->at(i);
	else
		return data->at(i-(n-i));
}
	
int Heaper::parent(int i){
	return (i-1) / 2;
}
	
int Heaper::left(int i){
	return (i*2) + 1;
}
	
int Heaper::right(int i){
	return (i*2) + 2;
}
	
bool Heaper::hasLeft(int i){
	return left(i) < n;
}
	
bool Heaper::hasRight(int i){
	return right(i)< n;
}

bool Heaper::isLeaf(int i){
	if (i > n)
		return false;
	
	return true;
}
