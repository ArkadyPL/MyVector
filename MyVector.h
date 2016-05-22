#pragma once

using namespace std;

template <typename T = int>
class MyVector {
	T* arr;
	int size;
public:
	MyVector(int size = 0);//size
	MyVector(int size, const T& value);//size, value for all
	MyVector(const T* values, int size);//array of values, size of array
	MyVector(MyVector&);
	~MyVector();
	void Append(const T& value, const int position = -1);//if pos == -1 append at the end
	void Erase(int position = -1);//erase element at 'position'
	void Clear();
	inline int Size() const { return size; }
	inline bool isEmpty() const { return size == 0 ? true : false; }
	T& operator[](int);
	MyVector<T>& operator+=(const T& value);
	template <typename T>
	friend ostream& operator<<(ostream&, MyVector<T>&);
};

//Constructor with size as parameter
template <typename T>
MyVector<T>::MyVector(int _size) {
	if (_size < 0) {
		size = 0;
		arr = nullptr;
		throw exception("Size cannot be smaller than 0!");
	}
	size = _size;
	arr = new T[size];
}

//Constructor with size and value (for all variables the same)
template <typename T>
MyVector<T>::MyVector(int _size, const T& value) {
	if (_size < 0) {
		size = 0;
		arr = nullptr;
		throw exception("Size cannot be smaller than 0!");
	}
	size = _size;
	arr = new T[size];
	for (int i = 0; i < size; i++) {
		arr[i] = value;
	}
}

//Constructor with given array of values and size of the array
template <typename T>
MyVector<T>::MyVector(const T* _arr, int _size) {
	if (_size > 0 && arr == nullptr) throw exception("Empty array with nonzero 'size' parameter!");
	if (_size < 0) {
		size = 0;
		arr = nullptr;
		throw exception("Size cannot be smaller than 0!");
	}
	size = _size;
	arr = new T[size];
	for (int i = 0; i < size; i++) {
		try {
			arr[i] = _arr[i];
		}
		catch (...) {
			delete[] arr;
			size = 0;
			arr = nullptr;
			throw exception("Given array doesn't match 'size' parameter value!");
		}
	}
}

//Copy Constructor
template <typename T>
MyVector<T>::MyVector(MyVector& vec) { //no if's and try's by assumption that every instance of MyVector contains correct data due to members protection
	this->size = vec.size;
	this->arr = new T[size];
	for (int i = 0; i < size; i++) {
		this->arr[i] = vec[i];
	}
}

//Destructor
template <typename T>
MyVector<T>::~MyVector() {
	delete[] arr;
}

//Add value at position, counting from 0, append at the end when no position specified
template <typename T>
void MyVector<T>::Append(const T& value, int position) {
	if (position < -1) { throw exception("Negative positions are not allowed!"); }
	if (position > size || position == -1) position = size;
	++size;
	T* temp = new T[size];
	int i = 0;
	for (; i < position; i++) { temp[i] = arr[i]; }
	temp[i] = value;
	i++;
	for (; i < size; i++) { temp[i] = arr[i - 1]; }
	delete[] arr;
	arr = temp;
}

//erase element at 'position', erase the last one when 'position' not specified
template <typename T>
void MyVector<T>::Erase(int position) {
	if (position < -1) { throw exception("Negative positions are not allowed!"); }
	if (position >= size || position == -1) position = size-1;
	T* temp = new T[size - 1];
	int i = 0;
	for (; i < position; i++) { temp[i] = arr[i]; }
	i++;
	for (; i < size; i++) { temp[i - 1] = arr[i]; }
	delete[] arr;
	arr = temp;
	size--;
}

//Clear vector
template <typename T>
void MyVector<T>::Clear() {
	size = 0;
	delete[] arr;
	arr = nullptr;
}

template <typename T>
T& MyVector<T>::operator[](int i) {
	if (i >= size || i < 0) throw exception("Out of range exception!");
	return arr[i];
}

template <typename T>
MyVector<T>& MyVector<T>::operator+=(const T& value) {
	this->Append(value);
	return *this;
}


template <typename T>
ostream& operator<<(ostream& out, MyVector<T>& vec) {
	if (vec.size >= 1) { out << vec[0]; }
	for (int i = 1; i < vec.size; i++) out << ", " << vec[i];
	return out;
}