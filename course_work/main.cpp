#include "test_generator.cpp"


using namespace std;

int main() {
	Seq s1;
	string s = "fuck";
	s1.add(new Any(s));
	s1.add(new Per(s));
	s1.add(new Format(22, "\n%d\n"));
	s1.add(new Rep(22, new Per(s)));
	s1.generate();
}