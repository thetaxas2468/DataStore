/*
 * DataStoreT.h
 *
 *  Created on: Jan 19, 2021
 *      Author: win 10
 */

#ifndef DATASTORET_H_
#define DATASTORET_H_
#include "DataStore.h"
#include <typeinfo>
#include <iostream>
#include <vector>
#include <algorithm>
template<class T>
void DataStore::create(const char* name)throw (FileFound,StoreFound){
	//check if there is file already
	fstream check(name);
	if(check.good()!=0){
		throw FileFound();
	}
	//check if there is store already
	for(std::vector<pop*>::iterator it=stores.begin();it!=stores.end();++it){
		if(typeid(Store<T>)==typeid(**it)){
			throw StoreFound();
		}
	}
	//creating the store and adding it to the vector
	ofstream q(name,ios::binary|ios::out);
	fstream *file=new fstream(name,ios::binary|ios::in|ios::out);
	this->stores.push_back(new Store<T>(*file));
}
template<class T>
void DataStore::load(const char* name)throw (FileNotFound,StoreFound,NotSameType){
	//check if file is found
	fstream check(name);
	if(check.good()==0){
		throw FileNotFound();
	}
	//check we dont have duplicate stores
	for(std::vector<pop*>::iterator it=stores.begin();it!=stores.end();++it){
		if(typeid(Store<T>)==typeid(**it)){
			throw StoreFound();
		}
	}
	//check if the file same tyoe as the store
	fstream *file=new fstream(name,ios::binary|ios::in|ios::out);
	file->seekg(0,ios::end);
	int y=file->tellg();
	file->seekg(0);
	if(y%sizeof(T)!=0){
		throw NotSameType();
	}
	//adding the store
	T p;
	file->seekg(0);
	file->read(reinterpret_cast<char *>(&p),sizeof(T));
	this->stores.push_back(new Store<T>(*file));
}
template<class T>
Store<T>& DataStore::store()throw (StoreNotFound){
	int cnt=0;
	//searching for the store we want if not exist StoreNotFound
	for(std::vector<pop*>::iterator it=stores.begin();it!=stores.end();++it){
		cnt++;
		if(typeid(**it)==typeid(Store<T>)){
			return (Store<T>&)(*stores[cnt-1]);
		}
	}
	throw StoreNotFound();
}
#endif /* DATASTORET_H_ */
