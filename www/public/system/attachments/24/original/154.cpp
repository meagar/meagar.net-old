// 154.cpp http://acm.uva.es/p/v1/154.html
//
// Solution to ACM problem #154 - "Recycling"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of July 28 / 2009
//

#include <iostream>
#include <vector>
#include <cassert>
#include <climits>

struct City {
	int id;
	std::vector<char> bins;

	City() : id(0), bins(5) { }

	std::istream& read(std::istream& in) {
		// line ending with 'e' means end of case
		if (in.peek() == 'e') {
			// Eat the line
			while (in.get() != '\n' && in);
			in.setstate(std::ios::failbit);
			return in;
		}

		// line beginning with '#' means EOF
		if (in.peek() == '#') {
			// Eat the hash character
			in.ignore();
			in.setstate(std::ios::failbit);
			in.setstate(std::ios::eofbit);
			return in;
	 	}

		// Read the 5 bins from the input stream
		for (int i = 0; i < 5; ++i) {
			char bin, tmp, material;
			
			// format is "b/m,"...
			in >> bin >> tmp >> material >> tmp;

			// ...except the last bin, which won't have a ','
			if (tmp != ',')
				in.putback(tmp);

			switch(bin) {
			case 'r': bins[0] = material; break;
			case 'o': bins[1] = material; break;
			case 'y': bins[2] = material; break;
			case 'g': bins[3] = material; break;
			case 'b': bins[4] = material; break;
			default: assert(false);
			}
		}

		return in;
	}

	// Return the number of differences between the given city and ourselves
	int diff(const City& c) const {
		int diffs = 0;
		for (int i = 0; i < 5; ++i)
			if (bins[i] != c.bins[i])
				++diffs;
		return diffs;
	}
}; // Class city

std::istream& operator>>(std::istream& in, City& c) { return c.read(in); }

class Solver {
public:
	Solver() : cities_() { }

	// Read our list of cities from the given input stream
	std::istream& read(std::istream& in) {
		cities_.clear();
		int i = 0;
		for (City c; in >> c;) {
			c.id = ++i;
			cities_.push_back(c);
		}

		if (!in.eof())
			in.clear();

		return in;
	}

	// Solve for the best city
	int solve() {
		// Find the city that has the fewest differences between all other cities
		int min = INT_MAX, minIdx = 0;

		typedef std::vector<City>::const_iterator citr;
		// For each city...
		for (citr i = cities_.begin(); i != cities_.end(); ++i) {
			int diffs = 0;
			// Compare with each other city...
			for (citr j = cities_.begin(); j != cities_.end(); ++j) {
				// Except ourselves...
				if (i == j)
					continue;

				diffs += i->diff(*j); 
			}

			if (diffs < min) {
				// We have a new best candidate
				min = diffs;
				minIdx = i->id;
			}
		}

		return minIdx;
	}

private:
	std::vector<City> cities_;

}; // class Solver

std::istream& operator>>(std::istream& in, Solver& s) { return s.read(in); }

int main() {
	for (Solver s; std::cin >> s;)
		std::cout << s.solve() << std::endl;
}

