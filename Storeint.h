/*
 * Storeint.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */

#include "Store.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
template<>
class Store<int>:public pop{
	//same as as StoreT but not really much here we use Specialization because int is primitive type
private:
	int index;
	fstream &file;
public:
	Store(fstream& file1):index(0),file(file1){}
	void append(const int& object){
		//getting the exact location by from 1 ----- N and adding it
		//0 is not true because there is place 1 , place 2 place 3
		file.seekg(index*sizeof(int));
		file.write(reinterpret_cast<const char*>(&object),sizeof(int));
		index++;
	}
	void write(int index1,const int& object)throw(IllegalIndex){
		//overriding an index in the file and write in it object that is int and we check for illegal commands
		if(index1>index){
			throw IllegalIndex();
		}
		file.seekg((index1-1)*sizeof(int));
		file.write(reinterpret_cast<const char*>(&object),sizeof(int));
		if(index1==index){
			index++;
		}
	}
	int read(int index1)throw(IllegalIndex){
		//read can be  a problem when we load a file index=0 so we need to deal with it and also make the true loacation and read it
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
		file.seekg((index1-1)*sizeof(int));
		int x;
		file.read(reinterpret_cast<char*>(&x),sizeof(int));
		return x;
	}
};
