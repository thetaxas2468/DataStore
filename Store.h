/*
 * Store.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */

#ifndef STORE_H_
#define STORE_H_
#include <iostream>
#include <fstream>
using namespace std;
class IllegalIndex{};
//doing base class because datastore class is not generic so we need to use polymorphism here and we do virutal in order to have virtual table
//and to do the polymorphism
class pop{
public:
	virtual ~pop(){}
};
template<class T>
class Store:public pop{
private:
	int index;
	fstream &file;
public:
	Store(fstream& file1):index(0),file(file1){}
	void append(const T& object);
	void write(int index,const T& object)throw(IllegalIndex);
	T& read(int index)throw(IllegalIndex);

};
#include "Storebool.h"
#include "Storechar.h"
#include "StoreT.h"
#include "Storeint.h"
#include "Storedouble.h"
#endif /* STORE_H_ */
