// 465.cpp http://acm.uva.es/p/v4/465.html
//
// Solution to ACM problem #465 - "Overflow"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of October 12 / 2005

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

bool readNum(int& out) {
	std::string buffer;
	char ch;

	// Eat leading whitespace
	while (std::isspace(std::cin.peek())  && std::cin.get(ch));

	// Read number
	while (std::isdigit(std::cin.peek()) && std::cin.get(ch))
		buffer += ch;

	if (!std::cin)
		exit(0);

	// write the number as we read it
	std::cout << buffer;

	// Create an input buffer, and read the integer from it
	std::istringstream strin(buffer);
	strin >> out;

	std::ostringstream strout;
	strout.width(buffer.length());
	strout.fill('0');
	strout << out;
	std::string b = strout.str();

	return (buffer != b);
}

// Adds n2 to n1 N times, returning TRUE if the result will overflow
bool addNTimes(int n1, int n2, int N) {
	if (N == 0)
		return false;

	while ((n1 + n2 >= n1) && (--N > 0))
		n1 += n2;

	return N != 0;
}

int main() {

	while (std::cin) {
		bool n1TooBig = false, n2TooBig = false;
		char op = 0;
		int n1 = 0, n2 = 0;

		// Read the first number
		n1TooBig = readNum(n1);

		// Read the operator
		std::cin >> op;
		std::cout << ' ' << op << ' ';

		// Read the second number
		n2TooBig = readNum(n2);
		std::cout << '\n';

		// assume the result will overflow if either number overflows
		bool overflow = (n1TooBig || n2TooBig);

		if (!overflow) {
			if (op == '+')
				overflow = addNTimes(n1, n2, 1);
			else
				overflow = (n1 > n2 ? addNTimes(0, n1, n2) : addNTimes(0, n2, n1));
		}

		if (n1TooBig)
			std::cout << "first number too big\n";
		if (n2TooBig)
			std::cout << "second number too big\n";

		if (overflow) {
			// special case where an operand == 0 and op = *
			if (!(((!n1TooBig && n1 == 0) || (!n2TooBig && n2 == 0)) && op == '*'))
				std::cout << "result too big\n";
		}
	}
}

