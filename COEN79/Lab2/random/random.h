//Stephen Tambussi
/*
CONSTRUCTOR: 
    rand_gen();
        Postcondition: object initialized
MEMBER FUNCTIONS: 
    int next();
        Postcondition: returns new random number and new random number is new seed
    void set_seed(int n);
        Postcondition: seed is set to int n
*/
#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H
#include <iostream>
#include <cassert>
using namespace std;
namespace coen79_lab2
{
    class rand_gen
    {
    public:
        rand_gen(int s, int ml, int i, int md);
        int next();
        void set_seed(int n);
        void print_info() const;
    private:
        int seed;
        int multiplier;
        int increment;
        int modulus;
    };
}
#endif