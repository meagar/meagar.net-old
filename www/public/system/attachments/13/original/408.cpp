// 408.cpp http://acm.uva.es/p/v4/408.html
//
// Solution to ACM problem #408 - "Uniform Generator"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of August 21 / 2007

#include <iostream>
#include <iomanip>
#include <vector>

const char* GOOD = "    Good Choice\n\n"; 
const char* BAD  = "    Bad Choice\n\n"; 

int main() {

	for (int step, mod; std::cin >> step >> mod;) {
		std::vector<int> seeds(mod + 1, 0), freqCount(mod + 1, 0);
		
		int i = 0;
		for (i = 0; i < mod; ++i) {
			seeds[i + 1] = (seeds[i] + step) % mod;
			if (++(freqCount[seeds[i + 1]]) != 1)
				break;
		}
		
		if (i != mod) {
			// we finished, but we need to check our freq count
			for (i = 0; i < mod; ++i)
				if (freqCount[i] != 1) break;
		}

		std::cout
			<< std::setw(10) << step
			<< std::setw(10) << mod
			<< (i == mod ? GOOD : BAD);
	}
}

