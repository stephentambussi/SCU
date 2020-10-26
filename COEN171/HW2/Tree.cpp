#include <iostream>
#include "Tree.h"

int main(int argc, const char * argv[])
{
	Tree<int> *t; //creates tree object that expects int type
	t = new Tree<int>();
	std::cout << std::boolalpha;//Prints true/false instead of 1/0	

	//Inserts items into the tree
	t->insert(15);
	t->insert(10);
	t->insert(20);
	t->insert(5);
	t->insert(30);
	t->insert(25);
	//Sees if the item is in the tree
	std::cout << "t->member(15) : " << t->member(15) << "\n";
	std::cout << "t->member(5) : " << t->member(5) << "\n";
	std::cout << "t->member(25) : " << t->member(25) << "\n";
	std::cout << "t->member(7) : " << t->member(7) << "\n";
	std::cout << "t->member(11) : " << t->member(11) << "\n";
	std::cout << "t->member(44) : " << t->member(44) << "\n";	
	
	return 0;
}
