// 100.cpp http://acm.uva.es/p/v1/100.html
//
// Solution to ACM problem #100 - "3n + 1"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Feb 19 / 2005

#include <iostream>

typedef unsigned long ulong;

int main() {

	ulong min, max; // our bounds as read from stdin

	while (std::cin >> min && std::cin >> max) {

		ulong maxCycles = 0;

		ulong lbound = min, ubound = max;
		if (lbound > ubound) {
			lbound = max;
			ubound = min;
		}

		// check each number in our given range (n1..n2)
		for (ulong i = lbound; i <= ubound; ++i) {

			ulong n = i;
			ulong cycles = 1;

			// loop until we hit 1
			while (n != 1 && ++cycles) {
				if (n % 2)
					// odd number
					n = 3 * n + 1;
				else
					// even number
					n /= 2;
			}

			if (cycles >= maxCycles)
				maxCycles = cycles;
		}

		// write results, using origional version of lbound and ubound
		std::cout << min << " " << max << " " << maxCycles << std::endl;
	}
}

