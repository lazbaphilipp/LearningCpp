#include <iostream>
#include <cstdint>
#include <cmath>
using namespace std;

int main() {
	uint8_t word = 0x0b, key = 0x0d, code = 0;

	uint8_t divider = 0;
	uint16_t pipeline = ((uint16_t)word) << 4; // 4 is the highest bit of the number D
	cout << "word = " << word << endl;
	// encode
	// divide polynominal
	for (int i = 0; i < 7; i++) {
		pipeline = pipeline >> 1;
		code += (pipeline & 0x01) << 7 - i;
		divider = (pipeline & 1) ? (key & 0xFF) : (key & 0x00);
		pipeline = (pipeline ^ divider);
	}
	uint8_t rem = pipeline;

	cout << "code = " << code << endl;

	uint8_t unkey = 0;
	for (int i = 0; i < 8; i++) {
		if (key << i & 0x80) {
			uint8_t tm = 7 - i;
			for (i; i < 8; i++) {
				unkey += ((key >> (7 - i)) & 1) << tm - (7 - i);
			}
		}
	}
	pipeline = 0;
	// decode
	//  x/y=z+r/y => x= z*y + r
	// multipl10}
}