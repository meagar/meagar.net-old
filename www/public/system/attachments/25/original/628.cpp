// 628.cpp http://acm.uva.es/p/v6/628.html
//
// Solution to ACM problem #628 - "Passwords"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of July 30 / 2009

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

typedef std::vector<std::string> StrVec;
typedef std::vector<StrVec::const_iterator> IterVec;

// Both our dictionary and rules are read in the same format;
// N, follow by N lines
bool read(StrVec& items) {
	std::size_t n;
	if (std::cin >> n) {
		items.resize(n);
		for (StrVec::iterator i = items.begin(); i != items.end(); ++i) 
			std::cin >> *i;
	}

	return std::cin.good();
}

inline void print(const IterVec& v) {
	for (IterVec::const_iterator i = v.begin(); i != v.end(); ++i)
		std::cout << **i;
	std::cout << '\n';
}

// Rather than passing these recuvsively, we use globals
StrVec dict, rules;
const char* digits[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
StrVec nums(digits, digits + 10);
IterVec buf;

// Recursive function to go over all permutations
void permute(const std::string& rule, std::size_t idx = 0) {
	StrVec& v = (rule[idx] == '#' ? dict : nums);
	StrVec::const_iterator& i = buf[idx];

	if (++idx == rule.length()) {
		for (i = v.begin(); i != v.end(); ++i)
			// We've hit the last element, print the items
			print(buf);
	} else {
		for (i = v.begin(); i != v.end(); ++i)
			permute(rule, idx);
	}
}

int main() {
	// Read the number of words
	while (read(dict) && read(rules)) {
		for (StrVec::const_iterator r = rules.begin(); r != rules.end(); ++r) {
			std::cout << "--\n";
			buf.resize(r->length());
			permute(*r);
		}
	}

	return 0;
}

