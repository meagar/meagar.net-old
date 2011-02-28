// 706.cpp http://acm.uva.es/p/v7/706.html
//
// Solution to ACM problem #706 - "LC-Display"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as July 03 / 2009

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

/*
   -  -   -       -   -   -   -
|   |  | | | | | |   |     | | |
   -  -   -   -   -   -       -
| |    | | |   |   | | |   |   |
   -  -   -       -   -       -
*/

const char* getLayout(char n) {
	// We basically return each digit rotated left 90 degrees, which we'll
	// use to build each character vertically
	switch(n) {
	case '1': return " ^ ^ ";
	case '2': return "|^|_|";
	case '3': return "|^|^|";
	case '4': return " =|^ ";
	case '5': return "|_|^|";
	case '6': return "|_|=|";
	case '7': return "|^ ^ ";
	case '8': return "|=|=|";
	case '9': return "|=|^|";
	case '0': return "|= =|";
	default:
		assert(false);
	}
}


// coupel of space-saving cheats
typedef std::vector<std::string> LineList;
#define each_line(x) LineList::iterator x = lines.begin(); x != lines.end(); ++x

int main() {
	int s;
	while (std::cin >> s && s) {
		std::string n;
		std::cin >> n;

		// Build the bits we'll append at the given size
		const std::string dash  = ' ' + std::string(s,     '-') + ' '; // ' - '
		const std::string blank =       std::string(s + 2, ' ')      ; // '   '
		const std::string left  = '|' + std::string(s + 1, ' ')      ; // '|  '
		const std::string right =       std::string(s + 1, ' ') + '|'; // '  |'
		const std::string both  = '|' + std::string(s,     ' ') + '|'; // '| |'

		// Our line buffers
		std::vector<std::string> lines(2 * s + 3);

		for (each_line(it))
			it->reserve(n.length() * (s + 3));

		// Loop over each of the characters in the string
		for (std::string::iterator num = n.begin(); num != n.end(); ++num) {

			// Add a space between digits
			if (num != n.begin())
				for (each_line(it))
					*it += ' ';

			// Get it's 5 character, side-ways representation
			const char* layout = getLayout(*num);

			LineList::iterator it = lines.begin();

			// Loop over each of the 5 characters, appending them down our lines
			for (int i = 0; i < 5; ++i) {
				switch(layout[i]) {

				// dash or blank take up one line regardless of s
				case '|': (*it++) += dash;  break;
				case ' ': (*it++) += blank; break;

				// right, left, both all repeat for s lines
				case '^': for (int i = 0; i < s; ++i) (*it++) += right; break;
				case '_': for (int i = 0; i < s; ++i) (*it++) += left;  break;
				case '=': for (int i = 0; i < s; ++i) (*it++) += both;  break;
				default:
					assert(false);
				}
			}
		}

		// Print the lines
		for (each_line(it))
			std::cout << *it << std::endl;

		// Every case has a new line
		std::cout << '\n';

	}

}

