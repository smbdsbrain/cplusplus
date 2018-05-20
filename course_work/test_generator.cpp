#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;


#define PLUS     0
#define MINUS 1
#define MULTIPLY 2
#define DEVIDE 3
#define REMAINDER 4

typedef pair<int, int> pipeline_action;

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

	int set_value(int new_value) {
		this->value = new_value;
		return this->value;
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

typedef pair<double, Action*> action_with_probability;

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
		while(val->get_value() != 0) {
			action->run();
		}
	}
protected:	
};

class Select : public Action {
private:
	vector<action_with_probability> actioins_list;
public:

	Select() {
	}

	Select add(Action *val, double probability) {
		actioins_list.push_back(action_with_probability(probability, val));
		return *this;
	}

	void run() {
		int sz = actioins_list.size();
		double *accumulated_probability = new double[sz];
		accumulated_probability[0] = actioins_list[0].first;
		for(int i = 1; i < sz; i++)
			accumulated_probability[i] = accumulated_probability[i-1] + actioins_list[i].first;

		double t = (rand() % ((int)(accumulated_probability[sz - 1] * 100))) / 100.0;
		int position = lower_bound(accumulated_probability, accumulated_probability + sz, t) - accumulated_probability;
		actioins_list[position].second->run();
	}
protected:	
};


class Assignable  {
private:
public:

	virtual int value(int start_value){return 0;};
protected:
};


class Random : public Assignable {
private:
	int start;
	int end;
public:

	Random(int start, int end) {
		this->start = start;
		this->end = end;
	}

	int value(int start_value) {
		return rand() % (end - start) + start;
	}

protected:
};


class Integer : public Assignable {
private:
	vector<pipeline_action> generate_pipeline;
public:

	Integer operator+(int b) {
		generate_pipeline.push_back(pipeline_action(PLUS, b));
		return *this;
    }

    Integer operator-(int b) {
    	generate_pipeline.push_back(pipeline_action(MINUS, b));
		return *this;
    }

    Integer operator*(int b) {
    	generate_pipeline.push_back(pipeline_action(MULTIPLY, b));
		return *this;
    }

    Integer operator/(int b) {
    	generate_pipeline.push_back(pipeline_action(DEVIDE, b));
		return *this;
    }

    Integer operator%(int b) {
    	generate_pipeline.push_back(pipeline_action(REMAINDER, b));
		return *this;
    }

    int value(int start_value) {
    	for(int i = 0; i < generate_pipeline.size(); i++) {
    		switch(generate_pipeline[i].first) {

    			case PLUS:
    				start_value += generate_pipeline[i].second;
    			break;

    			case MINUS:
    				start_value -= generate_pipeline[i].second;
    			break;

    			case MULTIPLY:
    				start_value *= generate_pipeline[i].second;
    			break;
    			
    			case DEVIDE:
    				start_value /= generate_pipeline[i].second;
    			break;

    			case REMAINDER:
    				start_value %= generate_pipeline[i].second;
    			break;
    		}
    	}
    	return start_value;
    }

protected:
};


class Assign : public Action {
private:
	Var *var;
	Assignable *assignable;
public:

	Assign(Var *var, Assignable *assignable) {
		this->var = var;
		this->assignable = assignable;
	}

	void run() {
		var->set_value(assignable->value(var->get_value()));
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