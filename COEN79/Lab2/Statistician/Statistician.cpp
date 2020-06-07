//Stephen Tambussi
#include <cassert>
#include <iostream>
#include "Statistician.h"
using namespace std;
using namespace coen79_lab2;
namespace coen79_lab2
{
	statistician::statistician()//set everything to zero
	{
		count = 0;
		summ = 0;
		smallest = 0;
		largest = 0;
		last = 0;
	}
	void statistician::next(double x)//next function
	{
		count++;
		summ += x;
		last = x;
		if (x < smallest)
			smallest = x;
		if (x > largest)
			largest = x;
	}
	int statistician::length() const { return count; }
	double statistician::sum() const { return summ; }
	double statistician::mean() const { assert(count > 0); return (summ / count); }
	double statistician::min() const { assert(count > 0); return smallest; }
	double statistician::max() const { assert(count > 0); return largest; }
	void statistician::reset()
	{
		count = 0;
		summ = 0;
		smallest = INT_MAX;
		largest = 0;
		last = 0;
	}
	//adds all private variables of two statistician objects and takes the smallest and largest value of the two for return object
	statistician operator +(const statistician& s1, const statistician& s2)
	{
		statistician sum;
		sum.count = s1.count + s2.count;
		sum.summ = s1.summ + s2.summ;
		if (s1.smallest < s2.smallest) sum.smallest = s1.smallest;
		else sum.smallest = s2.smallest;
		if (s1.largest > s2.largest) sum.largest = s1.largest;
		else sum.largest = s2.largest;
		sum.last = s1.last + s2.last;
		return sum;
	}
	//multiplies private variables of statistician object by scale value
	statistician operator *(double scale, const statistician& s)
	{
		statistician ans;
		ans.count = s.count;
		ans.summ = s.summ * scale;
		ans.smallest = s.smallest * scale;
		ans.largest = s.largest * scale;
		ans.last = s.last * scale;
		return ans;
	}
	//compare two statistician objects
	bool operator ==(const statistician& s1, const statistician& s2)
	{
		if (s1.length() == 0 && s2.length() == 0) return true;
		else if (s1.length() == s2.length() && s1.mean() == s2.mean() && s1.min() == s2.min() && s1.max() == s2.max() && s1.sum() == s2.sum())
			return true;
		else
			return false;
	}
}