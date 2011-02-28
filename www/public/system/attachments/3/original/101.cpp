// 101.cpp http://acm.uva.es/p/v1/101.html
// Solution to ACM problem #101 - "The Blocks Problem"
//
// Matthew Eagar - meagar@gmail.com
// Verified to work as of Feb 19 / 2005

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

struct Block {
	Block(int i) : id(i), up(0), down(0), stackNum(0) { }
	int id;
	Block* up;
	Block* down;
	int stackNum;
};

class Stack {
public:
	Stack(int id) : num(id), base(0) { }

	int num;
	Block* base;

	void put(Block* b) {
		if (base) {
			Block* top = base;
			while (top->up)
				top = top->up;
			top->up = b;
			b->down = top;
		} else {
			base = b;
			base->down = 0;
		}

		// set all the block's stack #'s
		for (Block* blk = b; blk; blk = blk->up)
			blk->stackNum = num;
	}

	void take(Block* b) {
		assert (base != 0);

		// find the block in question, remove it
		if (base == b) {
			base->down = 0;
			base = 0;
		} else {
			Block * blk = base;
			while (blk != b && (blk = blk->up));
			if (blk == b) {
				b->down->up = 0;
				b->down = 0;
			}
		}
	}

	void print(std::ostream& os) const {
		os << num << ':';
		if (base) os << ' ';

		for (const Block* blk = base; blk != 0; blk = blk->up) {
			os << blk->id;
			if (blk->up)
				os << ' ';
		}
	}	
};

inline std::ostream& operator<<(std::ostream& os, const Stack& s) {
	s.print(os);
	return os;
}

typedef std::vector<Block*> BlockVec;
typedef std::vector<Stack> StackVec;

BlockVec blocks;
StackVec stacks;

enum Command { CMD_MOVE = 1, CMD_PILE = 2 };
enum Argument { ARG_ONTO = 4, ARG_OVER = 8 };

void restorePos(Block* b) {
	if (!b)
		return;
	restorePos(b->up);

	stacks[b->stackNum].take(b);
	stacks[b->id].put(b);
}

void doCommand(Command cmd, Argument arg, int blockA, int blockB) {
	
	if (blocks[blockA]->stackNum == blocks[blockB]->stackNum) return;

	switch (cmd | arg) {
	case CMD_MOVE | ARG_ONTO:
		// return all blocks
		restorePos(blocks[blockA]->up);
		restorePos(blocks[blockB]->up);
		break;
	case CMD_MOVE | ARG_OVER:
		restorePos(blocks[blockA]->up);
		break;
	case CMD_PILE | ARG_ONTO: restorePos(blocks[blockB]->up);
		break;
	case CMD_PILE | ARG_OVER:
		// nothing
		break;
	default:
		assert(false);
	}

	stacks[blocks[blockA]->stackNum].take(blocks[blockA]);
	stacks[blocks[blockB]->stackNum].put(blocks[blockA]);
}


int main() {

	int numBlocks = 0; // 0 < numBlocks < 25
	std::cin >> numBlocks;

	// create the blocks
	blocks.resize(numBlocks, 0);

	for (int i = 0; i < numBlocks; ++i) {
		blocks[i] = new Block(i);
		stacks.push_back(Stack(i));
		stacks[i].put(blocks[i]);
	}

	int blockA, blockB;
	std::string arg;
	for (std::string cmd; std::cin >> cmd && cmd != "quit";) {
		std::cin >> blockA >> arg >> blockB;
		
		doCommand
			( (cmd == "move" ? CMD_MOVE : CMD_PILE)
			, (arg == "onto" ? ARG_ONTO : ARG_OVER)
			, blockA, blockB);

	}

	for (StackVec::const_iterator i = stacks.begin(); i != stacks.end(); ++i)
		std::cout << *i << '\n';

}
