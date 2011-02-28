// 10310.cpp http://acm.uva.es/p/v103/10310.html
//
// Solution to ACM problem #10310 - "Dog and Gopher"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of April 30 / 2005
// 
// Updated for Standards compliance August 20 / 2005
// Updated to use Point struct July 24 / 2009
//

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
	float x, y;
	inline float sqr(float x) const { return x * x; }

	// Returns the distance squared (avoid sqrt() for speed)
	float dist2(const Point& p) const { return sqr(x - p.x) + sqr(y - p.y); }
};

std::istream& operator>>(std::istream& in, Point& p) {
	return in >> p.x >> p.y;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
	return out << '(' <<  p.x << ',' << p.y << ')';
}

int main() {
	int n;

	std::cout << std::setiosflags(std::ios::fixed);
	std::cout << std::setprecision(3);

	Point goph, dog, hole;

	while (std::cin >> n >> goph >> dog) {
		bool done = false;

		while (--n >= 0 && std::cin >> hole) {
			if (done) continue; // gopher has already escaped

			// If the dog is at least twice as far from the hole...
			// (dist * 4) because of missing sqrt() calls
			if (hole.dist2(goph) * 4 <= hole.dist2(dog)) {
				// ...the gopher can safely reach it
				std::cout << "The gopher can escape through the hole at "
					<< hole << ".\n";
				done = true;
			}
		}

		// None of the holes were close enough
		if (!done)
			std::cout << "The gopher cannot escape." << std::endl;
	}

}
