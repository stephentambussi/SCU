//Stephen Tambussi
/*
CONSTRUCTOR
	statistician(double initial);
		Postcondition: object is initialized
MEMBER FUNCTIONS
	void next(double x);
		Postcondition: decimal number x is given to statistican as next number in sequence
	int length() const;
		Postcondition: return value is number of values in sequence(returns count)
	double sum() const;
		Postcondition: returns the sum of all the values in sequence
	double mean() const;
		Precondition: length() > 0
		Postcondition: return value is the average of all values in the sequence(summ/count)
	double min() const;
		Precondition: length() > 0
		Postcondition: returns the smallest value in the sequence
	double max() const;
		Precondition: length() > 0
		Postcondition: returns the largest value in the sequence
	void reset();
		Postconition: statistician's private variables are set to 0
NON-MEMBER FUNCTIONS
	statistician operator +(const statistician& s1, const statistician& s2);
		Postcondition: The statistician that is returned contains all the numbers of the sequences of s1 and s2.
	statistician operator *(double scale, const statistician& s);
		Postcondition: The statistician that is returned contains the same
		numbers that s does, but each number has been multiplied by the scale number.
	bool operator ==(const statistician& s1, const statistician& s2);
		Postcondition: The return value is true if s1and s2 have the zero
		length. Also, if the length is greater than zero, then s1 and s2 must
		have the same length, the same mean, the same minimum, the same maximum, and the same sum.
*/
#ifndef STATS_H
#define STATS_H
#include <iostream>
namespace coen79_lab2
{
	class statistician
	{
	public:
		statistician();
		void next(double x);
		int length() const;
		double sum() const;
		double mean() const;
		double min() const;
		double max() const;
		void reset();
		friend statistician operator +(const statistician& s1, const statistician& s2);
		friend statistician operator *(double scale, const statistician& s);
	private:
		int count;//length of sequence
		double summ;//sum of sequence
		double smallest;//smallest number in sequence
		double largest;//largest number in sequence
		double last;
	};
	bool operator ==(const statistician& s1, const statistician& s2);
}
#endif