// 483.cpp http://acm.uva.es/p/v4/483.html
//
// Solution to ACM problem #483 - "Word Scramble"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of June 1 / 2010

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

int main() {

	char ch;
	std::string word;
	std::ostream_iterator<char> out(std::cout, "");

	while (std::cin.get(ch)) {
		if (std::isspace(ch)) {
			std::copy(word.rbegin(), word.rend(), out);
			std::cout << ch;
			word.clear();
		} else {
			word += ch;
		}
	}
}

