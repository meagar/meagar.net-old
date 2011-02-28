// 102.cpp http://acm.uva.es/p/v1/102.html
//
// Solution to ACM problem #102 - "Ecological Bin Packing"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Dec 09 / 2005

#include <iostream>
#include <string>

// The possible orders, in reverse alphabetical order
static const char* combos[] = { "GCB" , "GBC" , "CGB" , "CBG" , "BGC" , "BCG" };

class Bin {
public:
	unsigned int brown;
	unsigned int clear;
	unsigned int green;

	Bin() : brown(0), clear(0), green(0) { }

	// return the number of bottles minus the given colour
	unsigned int getnot(char ch) {
		switch (ch) {
		case 'B': return clear + green;
		case 'C': return brown + green;
		case 'G': return clear + brown;
		default : return 0;
		}
	}

	// Read ourselves, and return the state of the input stream
	inline std::istream& read(std::istream& in) {
		return in >> brown >> green >> clear;
	}

};

inline std::istream& operator>>(std::istream& in, Bin& b) {
	return b.read(in);
}


int main() {
	Bin b1, b2, b3;
	while (std::cin >> b1 >> b2 >> b3) {
		int best = 1;
		unsigned int bestNumMoves = (unsigned int)-1;

		// check each of the possible orders to see if it's the best
		for (unsigned int i = 0; i < sizeof(combos) / sizeof(char*); ++i) {
			unsigned int nMoves
				= b1.getnot(combos[i][0])
				+ b2.getnot(combos[i][1])
				+ b3.getnot(combos[i][2]);

			if (nMoves <= bestNumMoves) {
				best = i;
				bestNumMoves = nMoves;
			}
		}

		std::cout << combos[best] << " " << bestNumMoves << std::endl;
	}
}

