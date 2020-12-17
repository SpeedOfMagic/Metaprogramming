#include <iostream>
#include "functor.h"

int f(int a, int b) { return a + b; }

using namespace std;
int main() {
	Functor<int(int, int)> pf(f);
	cout << pf(2, 3) << endl;
}
