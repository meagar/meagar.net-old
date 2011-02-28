// 119.cpp http://acm.uva.es/p/v1/119.html
//
// Solution to ACM problem #119 - "Greedy Gift Givers"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Feb 19 / 2005
//
// Updates for standards-compliance and best-practices on August 20 / 2007
// Verified to work as of August 20 / 2007

#include <string>
#include <iostream>
#include <map>
#include <vector>

class Person {
public:
	Person() : name(), numGiven(0), numRecieved(0) { }
	std::string name;
	int numGiven;
	int numRecieved;

	inline void give(int amount) { numGiven = amount; }
	inline void receive(int amount) { numRecieved += amount; }
	inline int assets() { return numRecieved - numGiven; }
};


int main(int argc, char** argv) {

	typedef std::vector<Person> Index;
	typedef std::map<std::string, Person*> Map;

	bool firstOutput = true;
	std::size_t n = 0;

	while (std::cin >> n) {
		// avoid printing leading whitespace
		if (!firstOutput) std::cout << std::endl;
		else firstOutput = false;

		Map peopleMap;
		Index people(n);

		// read names
		for (Index::iterator it = people.begin(); it != people.end(); ++it) {
			std::cin >> it->name;
			peopleMap[it->name] = &(*it);
		}
	
		std::string giverName, recieverName;
		std::size_t numRecievers = 0, numGiven = 0;

		// read in people each person gives to
		for (std::size_t i = 0; i < n; ++i) {

			std::cin >> giverName >> numGiven >> numRecievers;
			Person* giver = peopleMap[giverName];

			for (std::size_t j = 0; j != numRecievers; ++j) {
				std::cin >> recieverName;
				peopleMap[recieverName]->receive(numGiven / numRecievers);
				giver->give(numGiven - (numGiven % numRecievers));
			}
		}

		for (Index::iterator it = people.begin(); it != people.end(); ++it) {
			std::cout << it->name << " " << it->assets() << std::endl;
		}

	}
}

