// 401.cpp http://acm.uva.es/p/v4/401.html
//
// Solution to ACM problem #401 - "Palindromes"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Sept 21 / 2006
//
// Simplified and verified as of August 21 / 2007

#include <iostream>
#include <map>
#include <string>

char mirrorMap[] 
= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,'1','S','E',0,'Z',0,0,'8',0,0,0,0,0,0,0,0,'A',0,0,0
	,'3',0,0,'H','I','L',0,'J','M',0,'O',0,0,0,'2','T','U','V','W','X','Y','5' };

int main() {

	for (std::string word; std::cin >> word;) {
		bool isPal = true, isMir = true;

		std::string::iterator itf;
		std::string::reverse_iterator itr;

		for (itf = word.begin(), itr = word.rbegin()
		; (isPal || isMir) && itf != word.end(); ++itf, ++itr) {
			if (isPal && *itf != *itr)
				isPal = false; // It's not a palendrome

			if (isMir && mirrorMap[(int)(*itf)] != *itr)
				isMir = false; // It's not a mirror
		}
		
		std::cout << word << " -- is ";

		if (isPal && isMir) std::cout << "a mirrored palindrome.";
		else if (isMir) std::cout << "a mirrored string.";
		else if (isPal) std::cout << "a regular palindrome.";	
		else std::cout << "not a palindrome.";

		std::cout << '\n' << std::endl;
	}
}

