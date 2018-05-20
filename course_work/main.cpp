#include "test_generator.cpp"


using namespace std;

int main() {
	srand(time(NULL));

	Seq s1;
	string s = "fuck";
	s1.add(new Any(s));
	s1.add(new Per(s));
	s1.add(new Format(22, "\n%d\n"));
	s1.add(new Rep(22, new Per(s)));

	s1.add(new Format(22, "\n%d\n"));
	Select select = Select();
	select.add(new Per(s), 1.0);
	select.add(new Any(s), 1.0);
	s1.add(&select);

	s1.add(new Format(22, "\n%d\n"));
	
	s1.generate();
}