// 725.cpp http://acm.uva.es/p/v7/725.html
//
// Solution to ACM problem #725 - "Division"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of July 06 / 2009

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <iomanip>

// Check to see if the given numbers contain all 10 digits between them
bool check(int n1, int n2) {
	// Obvious checks for invalid pairs
	if (n1 < 1234 || n2 < 1234) return false;
	if (n1 < 9876 && n2 < 9876) return false;

	// Add a 0 (01234 vs 12340 doesn't matter for these tests)
	if (n1 < 9876) n1 *= 10;
	if (n2 < 9876) n2 *= 10;

	bool used[10] = { 0 };

	int n;
	while (n1 > 0) {
		n = n1 % 10;
		if (used[n]) return false;
		used[n] = true;
		n1 /= 10;
	}
	while (n2 > 0) {
		n = n2 % 10;
		if (used[n]) return false;
		used[n] = true;
		n2 /= 10;
	}

	return true;
}

int main() {

	int n;
	std::cin >> n;
	while (n) {
		bool noSolutions = true;

		// Start with the lowest possible numerator/denominator
		for (int num = 1234 * n, denom = 1234
		// Loop until we hit the maximum of either value
		; denom <= 98765 && num <= 98765
		// Each step denominator goes up 1, numerator goes up by n
		; ++denom, num += n) {
			if (check(num, denom)) {
				// We have a valid pair
				std::cout << num << " / ";
				std::cout.width(5);
				std::cout.fill('0');
				std::cout << denom << " = " << n << std::endl;
				noSolutions = false;
			}
		}

		if (noSolutions)
			std::cout << "There are no solutions for " << n << "." << "\n";

		if (std::cin >> n && n != 0)
			std::cout << '\n';
	}

}

