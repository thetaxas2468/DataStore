/*
 * Storechar.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */

#ifndef STORECHAR_H_
#define STORECHAR_H_
#include "Store.h"
#include <iostream>
#include <fstream>
using namespace std;
//same as StoreInt
template<>
class Store<char>:public pop{
private:
	int index;
	fstream &file;
public:
	Store(fstream& file1):index(0),file(file1){}
	void append(const char& object){
		file.seekg(index*sizeof(char));
		file.write(reinterpret_cast<const char*>(&object),sizeof(char));
		index++;

	}
	void write(int index1,const char& object)throw(IllegalIndex){
		if(index1>index){
			throw IllegalIndex();
		}
		file.seekg((index1-1)*sizeof(char));
		file.write(reinterpret_cast<const char*>(&object),sizeof(char));
		if(index1==index){
			index++;
		}
	}
	char read(int index1)throw(IllegalIndex){
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
		file.seekg((index1-1)*sizeof(char));
		char x;
		file.read(reinterpret_cast<char*>(&x),sizeof(char));
		return x;
	}
};



#endif /* STORECHAR_H_ */
