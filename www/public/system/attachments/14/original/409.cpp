// 409.cpp http://acm.uva.es/p/v4/409.html
//
// Solution to ACM problem #409 - "Excuses, Excuses!"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Sept 21 / 2006


#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <vector>

int main() {

	int numKeys, numEx, n = 0;
	typedef std::vector<std::string> Vec;

	while (std::cin >> numKeys >> numEx) {
		++n;

		std::cin.get();

		Vec keywords(numKeys);
		for (Vec::iterator it = keywords.begin(); it != keywords.end(); ++it)
			std::getline(std::cin, *it);

		Vec excuses(numEx);
		for (Vec::iterator it = excuses.begin(); it != excuses.end(); ++it)
			std::getline(std::cin, *it);

		int max = 0;
		std::vector<int> keyCount(numEx);
		for (int i = 0; i < numEx; ++i) {
			std::string tmp = excuses[i];
			for (unsigned int j = 0; j < tmp.length(); ++j)
				tmp[j] = std::tolower(tmp[j]);
	
			for (int j = 0; j < numKeys; ++j) {
				int p = -1;
				while ((p = (int)tmp.find(keywords[j], p + 1)) != (int)tmp.npos) {
					// check for leading delimeter
					if (p >= 1 && isalpha(tmp[p - 1]))
						continue;
					
					// check for tailing delimeter
					int n = p + keywords[j].length();
					if (n <= (int)tmp.length() && isalpha(tmp[n]))
						continue;

					++(keyCount[i]);
				}
			}

			if (keyCount[i] > max)
				max = keyCount[i];
		}

		std::cout << "Excuse Set #" << n << std::endl;

		for (int i = 0; i < numEx; ++i)
			if (keyCount[i] == max)
				std::cout << excuses[i] << std::endl;

		std::cout << std::endl;
	}
}

