// 476.cpp http://acm.uva.es/p/v4/476.html
//
// Solution to ACM problem #476 - "Points in Figures: Rectangles"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of June 1 / 2010

#include <iostream>
#include <vector>
#include <cstdlib>

using std::istream;

class Point {
	public:
	double x, y;
	std::istream& read(std::istream& in) {
		in >> x >> y;
		return in;
	}
};

class Figure {
public:
	virtual bool contains(const Point&) = 0;
	virtual void read(std::istream&) = 0;
};

class Rect : public Figure {
public:
	double x1, y1, x2, y2;

	void read(istream& in) {
		in >> x1 >> y1 >> x2 >> y2;

		if (y2 < y1) std::swap(y1, y2);
		if (x2 < x2) std::swap(x1, x2);
	}

	inline bool contains(const Point& p) {
		return p.x > x1 && p.x < x2 && p.y > y1 && p.y < y2;
	}

};

void read_figures(std::istream& in, std::vector<Figure*>& vec) {
	for(char ch; in && ch != '*'; in >> ch) {
		Figure* f;

		switch(ch) {
		case 'r':
			f = new Rect();
			f->read(in);
			vec.push_back(f);
		}
	}
}

int main() {

	std::vector<Figure*> figures;
	figures.reserve(10);
	read_figures(std::cin, figures);

	Point p;

	for (int i = 1; ; ++i) {
		bool contained = false;
		p.read(std::cin);
		if (p.x == 9999.9 || p.y == 9999.9)
			break;

		for (std::size_t j = 0; j < figures.size(); ++j) {
			Figure* f = figures[j];
			if (f->contains(p)) {
				contained = true;
				std::cout << "Point " << i << " is contained in figure " << j + 1 << '\n';
			}
		}

		if (!contained)
			std::cout << "Point " << i << " is not contained in any figure\n";
	}
}


