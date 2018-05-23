#include <iostream>

using namespace std;

class Rect {
private:
	int left, right, top, bottom;
public:
	Rect(int left, int right, int  top, int bottom) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}

	int getLeft(){
		return this->left;
	}

    int getTop() {
    	return this->top;
    }

    int getRight() {
    	return this->right;
    }

    int getBottom(){
    	return this->bottom;
    }

    Rect operator+(const Rect& b) {
		return Rect(max(this->left, b.left), min(this->right, b.right), min(this->top, b.top), max(this->bottom, b.bottom));
    }

    Rect operator+=(const Rect& b) {
    	Rect c = *this + b;
    	this->left = c.left;
    	this->right = c.right;
    	this->top = c.top;
    	this->bottom = c.bottom;
    	return *this;
    }

    bool operator==(const Rect& b) {
		return this->left == b.left && this->right == b.right && this->top == b.top && this->bottom == b.bottom;
    }

    Rect operator*(const Rect& b) {
		return Rect(min(this->left, b.left), max(this->right, b.right), max(this->top, b.top), min(this->bottom, b.bottom));
    }

    Rect operator*=(const Rect& b) {
    	Rect c = *this * b;
    	this->left = c.left;
    	this->right = c.right;
    	this->top = c.top;
    	this->bottom = c.bottom;
    	return *this;
    }

    bool operator<(const Rect& b) {
		return this->left > b.left && this->right < b.right && this->top < b.top && this->bottom > b.bottom;
    }

    friend ostream &operator<<(std::ostream &out, Rect &b) {
		cout << '[' << b.left << ',' << b.right << ',' << b.top << ',' << b.bottom << ']';
		return out;
	}			

	friend istream &operator>>(std::istream& is, Rect &b) {
		char t;
		cin >> t >> b.left >> t >> b.right >> t >> b.top >> t >> b.bottom;
		return is;
	}

protected:
};



int main() {

	Rect a = Rect(4, 6, 6, 4);
	Rect b = Rect(5, 7, 7, 5);
	Rect c = Rect(2, 8, 8, 2);

	Rect d = a + b; 
	Rect f = a * b;

	Rect e = a;
	e += b;

	Rect h = a;
	h *= b;

	cout << a << " + " << b << " = " << d;
	cout << '\n';
	cout << a << " * " << b << " = " << f;
	cout << '\n';
	cout << "a+=b is " << e;
	cout << '\n';
	cout << "a*=b is " << h;

	bool t = a == b;
	cout << '\n';
	cout << "a == b is " << (t ? "True" : "False");

}