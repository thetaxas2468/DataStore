/*
 * Storebool.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */
#ifndef STOREBOOL_H_
#define STOREBOOL_H_
#include "Store.h"
#include <iostream>
#include <fstream>
using namespace std;
//same as StoreInt
template<>
class Store<bool>:public pop{
private:
	int index;
	fstream &file;
public:
	Store(fstream& file1):index(0),file(file1){}
	void append(const bool& object){
		file.seekg(index*sizeof(bool));
		file.write(reinterpret_cast<const char*>(&object),sizeof(bool));
		index++;

	}
	void write(int index1,const bool& object)throw(IllegalIndex){
		if(index1>index){
			throw IllegalIndex();
		}
		file.seekg((index1-1)*sizeof(bool));
		file.write(reinterpret_cast<const char*>(&object),sizeof(bool));
		if(index1==index){
			index++;
		}
	}
	bool read(int index1)throw(IllegalIndex){
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
		file.seekg((index1-1)*sizeof(bool));
		bool x;
		file.read(reinterpret_cast<char*>(&x),sizeof(bool));
		return x;
	}
};


#endif /* STOREBOOL_H_ */
