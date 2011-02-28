// 402.cpp http://acm.uva.es/p/v4/402.html
//
// Solution to ACM problem #402 - "M*A*S*H"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Sept 21 / 2006
// Verified to work as of August 21 / 2007


#include <iostream>
#include <vector>
#include <sstream>

int main() {

	int n = 1;
	for (int nPeople, nLucky; std::cin >> nPeople >> nLucky;) {

		std::vector<int> people(nPeople, 1);

		int nLeft = nPeople, card = 0;

		// Read a line
		std::string line;
		std::getline(std::cin, line);
		std::istringstream strm(line);

		for (int i = 0; i != 20; ++i) {
			if (!(strm >> card))
				break;
			
			if (card > 11)
				card = 11;
			else if (card < 1)
				card = 1;

			// If we're done, continue reading cards until
			// we've hit 20
			if (nLeft <= nLucky)
				continue;

			int c = 1;
			// We have to loop through the line, eliminating people
			for (int j = 0; j != nPeople; ++j) {
				if (people[j]) {
					// we've got a person still in line 
					if (c == card) {
						people[j] = false;
						--nLeft;
						c = 0;
					}
					++c;
				}
				if (nLeft <= nLucky)
					break;
			}
		}
	
		std::cout << "Selection #" << n << "\n";

		bool f = true;		
		for (int i = 0; i != nPeople; ++i)	{
			if (people[i]) {
				if (f)
					f = false;
				else 
					std::cout << ' ';

				std::cout << i + 1;
			}
		}

		++n;
		std::cout << "\n\n";
	}

}
