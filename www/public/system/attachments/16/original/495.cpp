// 495.cpp http://acm.uva.es/p/v4/495.html
//
// Solution to ACM problem #495 - "Fibonacci Freeze"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Dec 09 / 2005

#include <list>
#include <iostream>
#include <map>
#include <string>

int main() {
	typedef std::list<int> List;

	// nums holds the numbers we need to find the fib. for, in the order they appear in the input
	List nums;

	// fibs holds the fib. number for each of the input numbers
	std::map<int, std::string> fibs;

	int n;
	while (std::cin >> n) {
		nums.push_back(n);
		fibs[n] = "";
	}

	fibs[0] = "0"; // constant
	fibs[1] = "1"; // constant

	// n0 and n1 are our two big numbers
	List n0, n1;
	// start with the first two terms
	n0.push_back(0); 
	n1.push_back(1);

	// find the highest input number, and loop until we hit it
	int highest = fibs.rbegin()->first;
	for (int n = 2; n <= highest; ++n) {
		// Add n1 to n0, placing the result in n0
		List::iterator i = n0.begin();
		List::iterator j = n1.begin();

		int carry = 0;
		// write directly to n0 until it's iterator hits it's end
		while (i != n0.end()) {
			*i += *j + carry;
			carry = (int)((float)*i / 10.0f);
			*i %= 10;
			++i; ++j;
		}

		// append to n0 until n1's iterator reaches it's end
		// (n0 will always be the shorter number)
		while (j != n1.end()) {
			int tmp = *j + carry;
			carry = (int)((float)tmp / 10.0f);
			n0.push_back(tmp % 10);
			++j;
		}

		// append the remainder, if any
		if (carry != 0)
			n0.push_back(carry);

		// Swap, so that n1 is now n0 + (n1's old value)
		std::swap(n0, n1);

		// see if we need the n'th fib
		if (fibs.find(n) != fibs.end()) {
			char* str = new char[n1.size() + 1];
			int p = 0;
			for (List::reverse_iterator it = n1.rbegin(); it != n1.rend(); ++it)
				str[p++] = *it + '1' - 1;
			str[n1.size()] = 0;
			fibs[n] = str;
		}
	}

	for (List::iterator it = nums.begin(); it != nums.end(); ++it)
		std::cout << "The Fibonacci number for " << *it << " is " << fibs[*it] << std::endl;
}

