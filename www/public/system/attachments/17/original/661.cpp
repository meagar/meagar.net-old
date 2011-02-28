// 661.cpp http://acm.uva.es/p/v6/661.html
//
// Solution to ACM problem #661 - "Blowing Fuses"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Feb 19 / 2005

#include <iostream>
#include <cstring>

int main() {

	int  devices, cases, capacity, N = 1;
	int d, max, current;

	while (std::cin >> devices >> cases >> capacity) {

		// This one is really picky about no trailing newlines
		// Only print a newline to seperate cases
		if (N != 1) std::cout << '\n';

		if (devices == 0 && cases == 0 && capacity == 0) break;

		d = max = current = 0;

		bool state[20] = {0};
		int  power[20] = {0};

		for (int i = 0; i != devices; ++i)
			std::cin >> power[i];

		for (int i = 0; i != cases; ++i) {
			// read a device, toggle it
			std::cin >> d;
			d -= 1;
			state[d] = !state[d]; 

			if (state[d]) {
				// if it's on, add the current to the total,
				// and see if we have a new peek current.
				if ((current += power[d]) > max)
					max = current;
			} else {
				// it's off, subtract it's current
				current -= power[d];
			}
		}

		std::cout << "Sequence " << N << '\n';

		if (max > capacity) {
			std::cout << "Fuse was blown." << '\n';
		} else {
			std::cout << "Fuse was not blown.\nMaximal power consumption was "
				<< max << " amperes." << '\n';
		}

		++N;
	}

	return 0;
}

