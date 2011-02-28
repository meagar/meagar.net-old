// 755.cpp http://acm.uva.es/p/v7/755.html
//
// Solution to ACM problem #755 - "487-3279"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as July 04 / 2009

#include <iostream>
#include <cctype>
#include <map>

typedef std::map<int, int> Directory;

// The first bit of the ASCII table
char digits[] =
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	
	, 0,1,2,3,4,5,6,7,8,9              // 0..9
	, -1,-1,-1,-1,-1,-1,-1             // whatever
	, 2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7  // A..P
	, -1                               // Q
	, 7,7,8,8,8,9,9,9                  // R..Y
	};


// Read the next 7 alphanumeric characters from stdin and convert to a number
// We can just grap 7 at a time because the lines are guaranteed to contain
// exactly 7 correct chars, and x number of garbage (dash, new line)
int nextNum() {
	int n = 0, c = 0, ch;
	for(;;) {
		ch = digits[std::cin.get()];
		if (ch == -1)
			continue;
		n += ch;
		if (++c == 7)
			return n;
		n *= 10;
	}
}

int main() {

	int numDataSets, numNumbers;
	std::cin >> numDataSets;

	Directory freq;
	while (numDataSets--) {
		freq.clear();
		std::cin >> numNumbers;

		while (--numNumbers >= 0)
			++freq[nextNum()];

		bool duplicates = false;
		for (Directory::const_iterator i = freq.begin(); i != freq.end(); ++i) {
			if (i->second == 1)
				// This number only appears once
				continue;

			duplicates = true;
			// So much simpler than cout
			printf("%03d-%04d %d\n", i->first / 10000, i->first % 10000, i->second); 
		}

		if (!duplicates)
			std::cout << "No duplicates.\n";

		if (numDataSets != 0)
			std::cout << '\n';

		/// We might have trailing dashes from the last case
		while ('-' == std::cin.peek() && std::cin && std::cin.get());
	}

}

