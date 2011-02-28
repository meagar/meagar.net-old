// 105.cpp http://acm.uva.es/p/v1/105.html
//
// Solution to ACM problem #105 - "The Skyline Problem"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Dec 10 / 2005

#include <iostream>

int main() {
	int height[10001] = {0};
	int left, right, buildingHeight;

	// read our buildings
	while (std::cin >> left >> buildingHeight >> right) {
		for (int i = left; i < right; ++i) {
			if (buildingHeight > height[i])
				height[i] = buildingHeight;
			}
	}

	bool notFirst = false; // only show a preceeding space on the non-first entries
	int currentHeight = 0;
	for (int pos = 0; pos != 10000; ++pos) {
		if (height[pos] != currentHeight) {
			if (notFirst)
				std::cout << ' ';
			else
				notFirst = true;

			std::cout << pos << ' ' << height[pos];
			currentHeight = height[pos];
		}
	}
	std::cout << std::endl;
	
}

