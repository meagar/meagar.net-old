// 10408.cpp http://acm.uva.es/p/v104/10408.html
//
// Solution to ACM problem #10408 - "Farey Sequences"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of September 25 / 2007

#include <iostream>

int main() {

	unsigned int n, term;
	while (std::cin >> n >> term) {
		int a = 0, b = 1, c = 1, d = n, e, f, k;

		unsigned int i = 0;
		// Algorithm taken from Wikipedia and modified
		while (++i != term) {
			k = (int)((n + b) / (float)d);
			e = k * c - a;
			f = k * d - b;
			a = c; b = d; c = e; d = f;
		}

		std::cout << c << '/' << d << '\n';
	}

	return 0;
}
