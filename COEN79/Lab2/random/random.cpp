#include "random.h"
#include <stdio.h>
using namespace std;
namespace coen79_lab2
{	//Constructor needs 4 arguments
	rand_gen::rand_gen(int s, int ml, int i, int md)
	{
		seed = s;
		multiplier = ml;
		increment = i;
		modulus = md;
	}
	//returns random number
	int rand_gen::next()
	{
		int temp;
		temp = (multiplier * seed + increment) % modulus;
		seed = temp;
		return temp;
	}
	//sets new seed from argument
	void rand_gen::set_seed(int n)
	{
		seed = n;
	}
	void rand_gen::print_info() const 
	{
		cout << "Seed: " << this->seed;
		cout << " Multiplier: " << this->multiplier;
		cout << " Increment: " << this->increment;
		cout << " Modulus: " << this->modulus << endl << endl;
	}
}