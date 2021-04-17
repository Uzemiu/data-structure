template <class T>
class MyStack{
public:
	MyStack() {
		top = 0;
		max_size = 100;
		element = new T[100];
	}
	MyStack(int size) {
		top = 0;
		max_size = size;
		element = new T[size];
	}
	T pop();
	void push(T e);
	size_t size();
	T peek();
	bool empty();
	void clear();
	void resize(size_t size);

private:
	size_t max_size;
	T* element;
	size_t top;
};
