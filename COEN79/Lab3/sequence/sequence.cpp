//Invariant:
//CAPACITY needs to be between 0 and 50 --> 0 <= CAPACITY <= 50
#include <iostream>
#include <cassert>
#include <cmath>
#include "sequence.h"
namespace coen79_lab3
{
	sequence::sequence()
	{
		count = 0;
		curt = 0;
	}
	void sequence::start()
	{
		curt = 0;
	}
	void sequence::end()
	{
		curt = count-1;
	}
	void sequence::last()
	{
		curt = CAPACITY - 1;
	}
	void sequence::advance()
	{
		assert(is_item());
		if (curt < count)
			curt++;
	}
	void sequence::retreat()
	{
		if (curt > 0)
			curt--;
	}
	void sequence::insert(const value_type& entry)
	{
		assert(size() < CAPACITY);
		if (count == 0)
		{
			data[count] = entry;
			curt = 0;
		}
		else
		{
			for (int i = count; i >= curt + 1; i--)
				data[i] = data[i - 1];
			data[curt] = entry;
		}
		count++;
	}
	void sequence::attach(const value_type& entry)
	{
		assert(size() < CAPACITY);
		if (!is_item())
			data[count] = entry;
		else
		{
			for (int i = count; i > curt + 1; i--)
				data[i] = data[i - 1];
			data[curt + 1] = entry;
			curt++;
		}
		count++;
	}
	void sequence::remove_current()
	{
		assert(is_item());
		for (int i = curt + 1; i < count; i++)
		{
			data[i - 1] = data[i];
		}
		count--;
	}
	void sequence::insert_front(const value_type& entry)
	{
		assert(size() < CAPACITY);
		insert(entry);
		curt = 0;
		count++;
	}
	void sequence::attach_back(const value_type& entry)
	{
		assert(size() < CAPACITY);
		data[count] = entry;
		count++;
	}
	void sequence::remove_front()
	{
		assert(is_item());
		for (int i = 0; i < count - 1; i++)
			data[i] = data[i + 1];
		count--;
	}
	void sequence::operator +=(const sequence& rhs)
	{
		assert((count + rhs.count) < CAPACITY);
		size_type tmp = rhs.count;
		for (int i = 0; i < tmp; i++)
			data[count++] = rhs.data[i];
	}
	sequence::size_type sequence::size() const
	{
		return count;
	}
	bool sequence::is_item() const
	{
		if (curt < count) return true;
		else return false;
	}
	sequence::value_type sequence::current() const
	{
		assert(is_item());
		return(data[curt]);
	}
	sequence::value_type sequence::operator[](int index) const
	{
		assert(index < count);
		return data[index];
	}
	double sequence::mean() const
	{
		double sum = 0;
		for (int i = 0; i < count; i++)
			sum += data[i];
		return(sum / count);
	}
	double sequence::standardDeviation() const
	{
		double sdev = 0;
		for (int i = 0; i < count; i++)
			sdev += pow(data[i] - mean(), 2);
		return sqrt(sdev / count);
	}
	sequence operator +(const sequence& lhs, const sequence& rhs)
	{
		assert((lhs.size() + rhs.size()) <= sequence::CAPACITY);
		sequence(tmp);
		tmp += lhs;
		tmp += rhs;
		return tmp;
	}
	sequence::value_type summation(const sequence& s)
	{
		double sum = 0;
		for (int i = 0; i < s.size(); i++)
			sum += s.data[i];
		return sum;
	}
}