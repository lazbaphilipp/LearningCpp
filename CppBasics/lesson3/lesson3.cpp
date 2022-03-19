#include <iostream>
#include <stdint.h>
using namespace std;

// € рад, что это работает. Ќе знаю,правда, можно ли так.
#define cpfl(param) static_cast<float>(param)

int main() {
	const int a = 2, b = 5, c = 13, d = 3;
	float e = a * (b + cpfl(c) / d);
	printf("float result = %f \n", e);
	return 0;
}
