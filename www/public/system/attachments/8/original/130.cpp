// 130.cpp http://acm.uva.es/p/v1/130.html
//
// Solution to ACM problem #130 - "Roman Roulette"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Feb 19 / 2005

#include <iostream>

struct Person {
	int id;
	Person* next;	
	Person* prev;
};

Person * makeRing(int n) {
	Person* base = new Person;
	Person* current = base;
	for (int i = 1; i <= n; ++i) {
		current->id = i;
		if (i != n) {
			current->next = new Person;
			current->next->prev = current;
			current = current->next;
		}
	}
	// link the last guy back to the first
	current->next = base;
	base->prev = current;
	return base;
}

int main() {
	int n = 0;
	int k = 0;
	while (std::cin >> n >> k) {
		if (n == 0 && k == 0) return 0;

		if (n == 0) {
			std::cout << n << std::endl;
			continue;
		}

		// setup our people
		Person* basePerson = makeRing(n);
		Person* dead = basePerson;
		Person* digger = 0;

		// find the dead person
		for (int i = 0; i < k - 1; ++i) {
			dead = dead->next;	
		}

		for (int numLeft = n; numLeft > 1; --numLeft)  {
			// remove the dead person	
			dead->prev->next = dead->next;
			dead->next->prev = dead->prev;

			// find the digger
			digger = dead;
			for (int i = 0; i < k; ++i)
				digger = digger->next;

			//swap the digger for the dead guy;
			dead->id = digger->id;

			// restore the links
			dead->prev->next = dead;
			dead->next->prev = dead;
			
			digger->prev->next = digger->next;
			digger->next->prev = digger->prev;
			delete digger;

			for (int i = 0; i < k; ++i)
				dead = dead->next;
		}
		// 'dead' now points to the only living guy :/
		int startPos = 1;
		int winner = dead->id;
		while (winner != 1) {
			--startPos;
			if (startPos < 1) startPos = n;
			--winner;
		}
		std::cout << startPos << std::endl;
	}

}

