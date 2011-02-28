// 713.cpp http://acm.uva.es/p/v7/713.html
//
// Solution to ACM problem #713 - "Adding Reversed Numbers"
// 
// Matthew Eagar - meagar@gmail.com
// Verified to work as of March 15 / 2005
//
// Totally rewritten and verified on August 22 / 2007
// Uses Bignum with simplifed main() instead of inline algorithm

#include <iostream>
#include <string>
#include <vector>

class Bignum {
public:

	Bignum() {
		digits_.reserve(200); // maximum length of input
	}

	// Read a number from an istream
	std::istream& read(std::istream& in) {
		digits_.clear();
		std::string number;
		if (in >> number) {
			digits_.reserve(number.length());
			for (std::string::const_iterator it = number.begin()
			; it != number.end(); ++it) {
				digits_.push_back((int)(*it) - (int)('0'));
			}
		}
			
		return in;
	}

	// Write a number (without leading 0's) to an ostream
	std::ostream& write(std::ostream& os) const {
		bool print = false;
		for (Citr it = digits_.begin(); it != digits_.end(); ++it) {
			if (*it != 0) // avoid printing leading 0's
				print = true;
			if (print)
				os << *it;
		}

		if (!print) {
			// We never found a non-0 digit, so nothing was printed.
			// (Won't actually happen, problem input is a positive integer)
			os << 0;
		}

		return os;
	}

	// Add another Bignum to ourselves
	Bignum& operator+=(const Bignum& rhs) {

		// we must have at least as many digits as rhs
		if (rhs.digits_.size() > digits_.size())
			digits_.resize(rhs.digits_.size(), 0);

		unsigned int carry = 0;
		for (std::size_t i = 0; i != digits_.size(); ++i) {
			int sum = digits_[i]
				+ (rhs.digits_.size() > i ? rhs.digits_[i] : 0)
				+ carry;

			if (sum >= 10) {
				carry = 1;
				sum -= 10;
			} else {
				carry = 0;
			}

			digits_[i] = sum;
		}

		// We have a trailing carry digit
		if (carry != 0)
			digits_.push_back(carry);

		return *this;	
	}

private:
	typedef std::vector<unsigned int> Vec;
	typedef Vec::iterator Itr;
	typedef Vec::const_iterator Citr;

	Vec digits_;
};

std::istream& operator>>(std::istream& in, Bignum& b) {
	return b.read(in);
}

std::ostream& operator<<(std::ostream& out, const Bignum& b) {
	return b.write(out);
}

Bignum operator+(Bignum l, const Bignum& r) {
	return l += r;
}

int main() {

	int n;
	std::cin >> n;

	for (int i = 0; i != n; ++i) {
		Bignum n1, n2;

		std::cin >> n1 >> n2;

		std::cout << (n1 += n2) << std::endl;
	}
}
