// 156.cpp http://acm.uva.es/p/v1/156.html
//
// Solution to ACM problem #156 - "Ananagrams"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of April 30 / 2005

#include <string>
#include <iostream>
#include <set>
#include <cctype>

typedef std::set<std::string> dictionary; // sorts for us

void addWord(dictionary& d, const std::string& word) {
	d.insert(word);
}

// ANAgram - returns true if 'anagram' is an anagram for 'word'
bool isAnagram(const std::string& word, const std::string& anagram) {
	if (word.length() != anagram.length()) return false;

	int letters[(int)'z' + 1] = {0};

	// For each letter in 'anagram', increment it's frequency in 'letters'
	// For each letter in 'word', decrement it's frequency, and, if all
	// the frequencies balance to 0, it's an anagram (we have the exact same
	// number of each letter in both words)
	unsigned int i = 0;
	for (; i < anagram.length(); ++i) {
		++letters[std::tolower(anagram[i])];
		--letters[std::tolower(word[i])];
	}

	// make sure that all the positions from a..z balanced out to 0 
	i = 'a';
	while (i <= 'z' && letters[i] == 0) ++i;
	return (i > 'z');
}

// ANANAgram - returns true if 'word' has no anagrams in the dictionary 'dict'
bool isAnanagram(dictionary::const_iterator word, const dictionary& dict) {
	for (dictionary::const_iterator i = dict.begin(); i != dict.end(); ++i)
		if (word != i && isAnagram(*word, *i))
			return false;

	return true;
}

int main() {
	// read in the words
	dictionary d;
	std::string word;

	// Read 
	while (std::cin >> word && word != "#")
		addWord (d, word);

	for (dictionary::iterator i = d.begin(); i != d.end(); ++i)
		if (isAnanagram(i, d)) std::cout << *i <<  std::endl;

	return 0;
}

