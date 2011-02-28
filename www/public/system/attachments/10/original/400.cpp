// 400.cpp http://acm.uva.es/p/v4/400.html
//
// Solution to ACM problem #400 - "Unix ls"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Sept 15 / 2006
// And again on August 21 / 2007

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

typedef std::vector<std::string> Vec;
typedef Vec::iterator Itr;

int main() {
	for (unsigned numFiles; std::cin >> numFiles;) {
		std::cin.ignore();
		std::cout <<
			"------------------------------------------------------------\n";

		// Read in names, recording the longest
		Vec files(numFiles);

		unsigned longest = 0;
		for (Itr it = files.begin(); it != files.end(); ++it) {
			std::getline(std::cin, *it);

			if (it->length() > longest)
				longest = it->length();
		}

		std::sort(files.begin(), files.end());

		// find the number of rows and columns in the output
		int cols = 0;
		
		while ((++cols + 1) * (longest + 2) - 2 <= 60);

		// Calculate the number of rows
		int rows = (int)(std::ceil((float)numFiles / (float)cols));

		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < cols; ++col) {
				// Translate (row,col) to an offset into the files array
				unsigned int idx = row + (col * rows);

				if (idx < numFiles) {
					std::cout << std::setw(longest)
						<< std::setiosflags(std::ios::left)
						<< files[idx];

					// Space between cols
					if (col + 1 != cols)
						std::cout << "  ";
				}
			}

			// end of row
			std::cout << std::endl;
		}
	}

	return 0;
}
