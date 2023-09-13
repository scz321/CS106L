#pragma once



#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iomanip>


using namespace std;


//���������ӣ����Ը��õ������ν�ġ�����һ���ԡ����Լ���������������з��ӵ���Ҫ����



template<typename T>
class SmartPointer {
private:
	struct Intermediary {
		T* ref;
		size_t count;
	};
	struct Intermediary* data;

	//һЩ��������
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

//Ĭ�Ϲ��캯��
template<typename T> SmartPointer<T>::SmartPointer() {
	cout << setw(10) << setfill('=') << "Ĭ�Ϲ��캯����ʼִ��" << setw(10)  << endl;
	data = new Intermediary();
	data->count = 1;
	data->ref = new T();
	cout << setw(10)  << "Ĭ�Ϲ��캯������ִ��" << setw(10)  << endl;

}

//���ƹ��캯��1������������ڵ�������:
template<typename T> SmartPointer<T>::SmartPointer(T* memory) {
	cout << setw(10) << setfill('=') <<' '  << "���ƹ��캯��_1��ʼִ��" << setw(10) << ' ' << endl;

	data = new Intermediary();
	data->count = 1;
	data->ref = memory;

	cout << setw(10) << ' '  << "���ƹ��캯��_1����ִ��" << setw(10) << ' ' << endl;

}
//���ƹ��캯��2������������ڵ�������:
template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& other) {
	cout << setw(10) << setfill('=') << ' ' << "���ƹ��캯��_2��ʼִ��" << setw(10) << ' ' << endl;
	attach(other);
	cout << setw(10) << ' ' << "���ƹ��캯��_2����ִ��" << setw(10) << ' ' << endl;

}





//��ֵ���캯����������ֵ��
//��������д���Ǵ���ģ�ǳ����
//template<typename T>
// SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer& other) {
//	 this->data = other.data;
//	 this->data->count++;
//}
//��ȷ��˼·�����ո��ƺ����ı�׼ģ��д������ǳ����



 template<typename T> void SmartPointer<T>::detach() {
	 this->data->count--;
	 if (this->data->count == 0) {
		 delete data->ref;//!ֻ��delete data�ǲ����ģ���
		 delete data;
	 }
}
 template<typename T> void SmartPointer<T>::attach(const SmartPointer& other) {
	 //data = new Intermediary();
	 this->data = other.data;

	 this->data->count++;

 }


 //��������������Ҫע�ⲻ��©�� delete data->ref;
 template<typename T> SmartPointer<T>::~SmartPointer() {
	 this->detach();
 }




 template<typename T> T* SmartPointer<T>::operator ->() const {
	 cout << setw(10) << setfill('=') << ' ' << "->���غ���start" << setw(10) << ' ' << endl;
	 cout << setw(10) << setfill('=') << ' ' << "->���غ���end  " << setw(10) << ' ' << endl;


	 return this->data->ref;

 };
 template<typename T> T& SmartPointer<T>::operator *() const {
	 cout << setw(10) << setfill('=') << ' ' << "*���غ���start" << setw(10) << ' ' << endl;
	 cout << setw(10) << setfill('=') << ' ' << "*���غ���end  " << setw(10) << ' ' << endl;


	 return *(this->data->ref);


 };
 template<typename T>  SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer& other) {
	 cout << setw(10) << setfill('=') << ' ' << "=���غ���start" << setw(10) << ' ' << endl;
	 if (this != &other) {
		 detach();
		 attach(other);
	 }
	 cout << setw(10) << setfill('=') << ' ' << "=���غ���end  " << setw(10) << ' ' << endl;

	 return *this;
 }


 void SmartPointerTest() {

	 SmartPointer<string> myPtr(new string);
	 *myPtr = "This is a string!";
	 cout << *myPtr << endl;
	 SmartPointer<string> other = myPtr;//!!��һ��ʵ���ϵȼ���SmartPointer<string> other(myPtr)�����������ڸ�ֵ�����Ǹ���
	 cout << *other << endl;
	 //cout << other->length() << endl;
 }