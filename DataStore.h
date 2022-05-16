/*
 * DataStore.h
 *
 *  Created on: Jan 19, 2021
 *      Author: win 10
 */

#ifndef DATASTORE_H_
#define DATASTORE_H_
#include <iostream>
#include <fstream>
#include <vector>
#include "Store.h"
//Data store that has vector that is generic and polymorphic to pop and its sons like Store
//we have some exceptions that we throw
class FileFound{};
class StoreFound{};
class StoreNotFound{};
class FileNotFound{};
class NotSameType{};
class DataStore{
private:
	vector<pop*> stores;
public:
	template<class T>
	void create(const char* name)throw(FileFound,StoreFound);
	template<class T>
	void load(const char* name)throw (FileNotFound,StoreFound,NotSameType);
	template<class T>
	Store<T>& store()throw (StoreNotFound);
};
#include "DataStoreT.h"

#endif /* DATASTORE_H_ */
