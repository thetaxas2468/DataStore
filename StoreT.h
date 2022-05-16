/*
 * StoreT.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */

#ifndef STORET_H_
#define STORET_H_
#include "Store.h"
template<class T>
void Store<T>::append(const T& object){
	//append generic type into the binary file
	file.seekg(index*sizeof(T));
	file.write(reinterpret_cast<const char*>(object.serialize()),sizeof(T));
	index++;
}
template<class T>
void Store<T>::write(int index1,const T& object)throw(IllegalIndex){
	//writing the object into index that we want and overrides it and we use generic in here
	if(index1>index){
		throw IllegalIndex();
	}
	file.seekg((index1-1)*sizeof(T));
	file.write(object.serialize(),sizeof(T));
	if(index1==index){
		index++;
	}
}
template<class T>
T& Store<T>::read(int index1)throw(IllegalIndex){
	//also as int this can be a problem but dealing with it also here reading the iTH index from the file which means iTh object
	file.seekg(0,ios::end);
	int y=file.tellg();
	file.seekg(0);
	if(index==0){
		if(((double)(y/sizeof(int))-(int)(y/sizeof(int)))==0){
			index=y/sizeof(int);
		}
		else{
			throw IllegalIndex();
		}
	}
	if(index1>index){
		throw IllegalIndex();
	}
	file.seekg((index1-1)*sizeof(T));
	int where=file.tellg();
	T x;
	return x.deserialize(file,where);
}

#endif /* STORET_H_ */
