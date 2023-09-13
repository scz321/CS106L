#pragma once



#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iomanip>


using namespace std;


//结合这个例子，可以更好地体会所谓的“语义一致性”，以及运算符重载在其中发挥的重要作用



template<typename T>
class SmartPointer {
private:
	struct Intermediary {
		T* ref;
		size_t count;
	};
	struct Intermediary* data;

	//一些辅助函数
	void detach();
	void attach(const SmartPointer& other);

public:
	explicit SmartPointer(T* memory);
	SmartPointer();
	SmartPointer(const SmartPointer<T>& other);
	SmartPointer& operator =(const SmartPointer& other);
	~SmartPointer();
	T* operator ->() const;
	T& operator *() const;
	
	
};


//implemention

//默认构造函数
template<typename T> SmartPointer<T>::SmartPointer() {
	cout << setw(10) << setfill('=') << "默认构造函数开始执行" << setw(10)  << endl;
	data = new Intermediary();
	data->count = 1;
	data->ref = new T();
	cout << setw(10)  << "默认构造函数结束执行" << setw(10)  << endl;

}

//复制构造函数1，这个函数存在的意义是:
template<typename T> SmartPointer<T>::SmartPointer(T* memory) {
	cout << setw(10) << setfill('=') <<' '  << "复制构造函数_1开始执行" << setw(10) << ' ' << endl;

	data = new Intermediary();
	data->count = 1;
	data->ref = memory;

	cout << setw(10) << ' '  << "复制构造函数_1结束执行" << setw(10) << ' ' << endl;

}
//复制构造函数2，这个函数存在的意义是:
template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& other) {
	cout << setw(10) << setfill('=') << ' ' << "复制构造函数_2开始执行" << setw(10) << ' ' << endl;
	attach(other);
	cout << setw(10) << ' ' << "复制构造函数_2结束执行" << setw(10) << ' ' << endl;

}





//赋值构造函数（参数赋值）
//下面这种写法是错误的（浅拷贝
//template<typename T>
// SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer& other) {
//	 this->data = other.data;
//	 this->data->count++;
//}
//正确的思路：按照复制函数的标准模板写，避免浅拷贝



 template<typename T> void SmartPointer<T>::detach() {
	 this->data->count--;
	 if (this->data->count == 0) {
		 delete data->ref;//!只是delete data是不够的！！
		 delete data;
	 }
}
 template<typename T> void SmartPointer<T>::attach(const SmartPointer& other) {
	 //data = new Intermediary();
	 this->data = other.data;

	 this->data->count++;

 }


 //析构函数，尤其要注意不能漏了 delete data->ref;
 template<typename T> SmartPointer<T>::~SmartPointer() {
	 this->detach();
 }




 template<typename T> T* SmartPointer<T>::operator ->() const {
	 cout << setw(10) << setfill('=') << ' ' << "->重载函数start" << setw(10) << ' ' << endl;
	 cout << setw(10) << setfill('=') << ' ' << "->重载函数end  " << setw(10) << ' ' << endl;


	 return this->data->ref;

 };
 template<typename T> T& SmartPointer<T>::operator *() const {
	 cout << setw(10) << setfill('=') << ' ' << "*重载函数start" << setw(10) << ' ' << endl;
	 cout << setw(10) << setfill('=') << ' ' << "*重载函数end  " << setw(10) << ' ' << endl;


	 return *(this->data->ref);


 };
 template<typename T>  SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer& other) {
	 cout << setw(10) << setfill('=') << ' ' << "=重载函数start" << setw(10) << ' ' << endl;
	 if (this != &other) {
		 detach();
		 attach(other);
	 }
	 cout << setw(10) << setfill('=') << ' ' << "=重载函数end  " << setw(10) << ' ' << endl;

	 return *this;
 }


 void SmartPointerTest() {

	 SmartPointer<string> myPtr(new string);
	 *myPtr = "This is a string!";
	 cout << *myPtr << endl;
	 SmartPointer<string> other = myPtr;//!!这一行实际上等价于SmartPointer<string> other(myPtr)，它并不属于赋值，而是复制
	 cout << *other << endl;
	 //cout << other->length() << endl;
 }