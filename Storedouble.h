/*
 * Storedouble.h
 *
 *  Created on: Jan 18, 2021
 *      Author: win 10
 */

#ifndef STOREDOUBLE_H_
#define STOREDOUBLE_H_
#include "Store.h"
#include <iostream>
#include <fstream>
using namespace std;
//same as storeInt
template<>
class Store<double>:public pop{
private:
	int index;
	fstream &file;
public:
	Store(fstream& file1):index(0),file(file1){}
	void append(const double& object){
		file.seekg(index*sizeof(double));
		file.write(reinterpret_cast<const char*>(&object),sizeof(double));
		index++;

	}
	void write(int index1,const double& object)throw(IllegalIndex){
		if(index1>index){
			throw IllegalIndex();
		}
		file.seekg((index1-1)*sizeof(double));
		file.write(reinterpret_cast<const char*>(&object),sizeof(double));
		if(index1==index){
			index++;
		}
	}
	double read(int index1)throw(IllegalIndex){
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
		file.seekg((index1-1)*sizeof(double));
		double x;
		file.read(reinterpret_cast<char*>(&x),sizeof(double));
		return x;
	}
};


#endif /* STOREDOUBLE_H_ */
