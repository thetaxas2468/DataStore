
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "Store.h"
#include "DataStore.h"
using namespace std;
struct Child{
	int age;
	int height;
	 const char* serialize()const{
		return reinterpret_cast<const char*>(this);
	}
	Child& deserialize(fstream& file,int where){
		file.seekg(where);
		file.read(reinterpret_cast<char*>(this),sizeof(*this));
		return *this;
	}
};
struct Student{
	int age;
	int height;
//	Student():age(0),height(0){}
//	Student(int a,int b){
//		age=a;
//		height=b;
//	}
//	Student(const Student& e){
//		age=e.age;
//		height=e.height;
//	}
	 const char* serialize()const{
		return reinterpret_cast<const char*>(this);
	}
	Student& deserialize(fstream& file,int where){
		file.seekg(where);
		file.read(reinterpret_cast<char*>(this),sizeof(*this));
		return *this;
	}
};
int main() {
	DataStore ds;
	try{
		//creating a DataStore and checking that every thing is working
		Student a;
		a.age=21;
		a.height=183;
		ds.create<int>("asda.dat");
		ds.create<Student>("asda1.dat");
		ds.store<int>().append(107);
		ds.store<int>().append(108);
		ds.store<Student>().append(a);
		cout<<"int is : "<<ds.store<int>().read(1)<<endl;
		cout<<"int is : "<<ds.store<int>().read(2)<<endl;
		Student b=ds.store<Student>().read(1);
		cout<<"Student "<<b.age<<" "<<b.height<<endl;
		//Try for child to check load bool load = false means creating vchil bool ==true check load function
		bool load=true;
		if(load==false){
			Child f;
			f.age=7;
			f.height=741;
			ds.create<Child>("asda2.dat");
			ds.store<Child>().append(f);
			Child f2=ds.store<Child>().read(1);
			cout<<"Child "<<f2.age<<" "<<f2.height<<endl;
		}
		else{
			ds.load<Child>("asda2.dat");
			Child q=ds.store<Child>().read(1);
			cout<<"Child "<<q.age<<" "<<q.height<<endl;
		}
	}
	catch(FileNotFound& e){
		cerr<<"File Not Found"<<endl;
		exit(1);
	}
	catch(FileFound& e){
		cerr<<"File Found"<<endl;
		exit(1);
	}
	catch(StoreFound& e){
		cerr<<"Store Found"<<endl;
		exit(1);
	}
	catch(StoreNotFound& e){
		cerr<<"Store Not Found"<<endl;
		exit(1);
	}
	catch(IllegalIndex& e){
		cerr<<"Illegal index"<<endl;
		exit(1);
	}
	catch(...){
		cerr<<"Exception"<<endl;
		throw;
	}
	return 0;

}
