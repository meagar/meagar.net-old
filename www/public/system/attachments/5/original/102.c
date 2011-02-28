/*
102.c

Solution to ACM problem #102 - "Ecological Bin Packing"

Matthew Eagar - meagar@gmail.com
Verified to work as of July 06 / 2009

This version is highly optimized for speed, with all the loops unrolled.
It is currently ranked 15th.
*/

#include <stdio.h>
#include <limits.h>

static const char* combos[] = { "GCB" , "GBC" , "CGB" , "CBG" , "BGC" , "BCG" };

#define check(x,y,z,i) if ((nMoves = n##x##1 + n##y##2 + n##z##3) <= bestNumMoves)\
{ best = i; bestNumMoves = nMoves; }

int main() {
	int b1, g1, c1, b2, g2, c2, b3, g3, c3
		, nb1, ng1, nc1, nb2, ng2, nc2, nb3, ng3, nc3
		, best, bestNumMoves, nMoves;

	while (EOF != scanf("%d %d %d %d %d %d %d %d %d"
	, &b1, &g1, &c1, &b2, &g2, &c2, &b3, &g3, &c3)) {
		nb1 = g1 + c1;
		ng1 = b1 + c1;
		nc1 = b1 + g1;

		nb2 = g2 + c2;
		ng2 = b2 + c2;
		nc2 = b2 + g2;
		
		nb3 = g3 + c3;
		ng3 = b3 + c3;
		nc3 = b3 + g3;


		best = 1;
		bestNumMoves = INT_MAX;

		check(g, c, b, 0);
		check(g, b, c, 1);
		check(c, g, b, 2);
		check(c, b, g, 3);
		check(b, g, c, 4);
		check(b, c, g, 5);

		printf("%s %d\n", combos[best], bestNumMoves);
	}
	return 0;
}

