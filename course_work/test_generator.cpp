#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Var {
private:
	int value;
public:
	Var(int v) {
		this->value = v;
	}

	int get_value() {
		return value;
	}

	Var operator+(const Var& b) {
		return this->value + b.value;
    }

    Var operator-(const Var& b) {
		return this->value - b.value;
    }

    Var operator*(const Var& b) {
		return this->value * b.value;
    }

    Var operator/(const Var& b) {
		return this->value / b.value;
    }
protected:
};

class Action {
private:
public:
	virtual void run() {};
protected:
};

class Any : public Action {
private:
	string str;
public:

	Any(string str) {
		this->str = str;
	}

	void run(){
		cout << str[rand() % str.length()];
	}
protected:	
};

class Per : public Action {
private:
	string str;
public:

	Per(string str) {
		this->str = str;
	}

	void run() {
		sort(str.begin(), str.end());
		for(int i = 0; i < rand() % str.length() * 26; i++) {
			next_permutation(str.begin(), str.end());
		}
		cout << str;
	}
protected:	
};

class Format : public Action {
private:
	int value;
	string format;
public:

	Format(int v, string f) {
		this->value = v;
		this->format = f;
	}

	Format(Var v, string f) {
		this->value = v.get_value();
		this->format = f;
	}

	void run() {
		printf(this->format.c_str(), this->value);
	}
protected:	
};

class Rep : public Action {
private:
	int value;
	Action *action;
public:

	Rep(int v, Action *action) {
		this->value = v;
		this->action = action;
	}

	Rep(Var v, Action *action) {
		this->value = v.get_value();
		this->action = action;
	}

	void run() {
		for(int i = 0; i < this->value; i++) {
			action->run();
		}
	}
protected:	
};

class While : public Action {
private:
	Var *val;
	Action *action;
public:

	While(Var *val, Action *action) {
		this->val = val;
		this->action = action;
	}

	void run() {

	}
protected:	
};

class Select : public Action {
private:
public:
	void run() {

	}
protected:	
};

class Assign : public Action {
private:
public:
	void run() {

	}
protected:	
};

class Seq {
private:
	vector<Action *> action_list;
public:
	Seq add(Action *action){
		action_list.push_back(action);
		return *this;
	}

	void generate() {
		for(std::vector<Action *>::iterator it = action_list.begin(); it != action_list.end(); ++it) {
			(*it)->run();
		}
	}
protected:
};