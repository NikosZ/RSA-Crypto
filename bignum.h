#ifdef BIGNUM_H
#define BIGNUM_H
#endif
#include <vector>
#define BASE 2147483648 // 2<<31  
typedef std::vector<unsigned long long>::iterator ITERATOR;
typedef std::vector<unsigned long long>::reverse_iterator REV_IT;
typedef std::vector<unsigned long long>::size_type SIZE;
typedef std::vector<unsigned long long> VLL;
class numbers{
public:
	VLL mynum;
	short pos;// 1 negative, 0 positive;
	numbers();
	numbers(long long);
	/*
	Overload Function to be added
	*/
	void same_size(numbers &);
	void clean_null(); //Delete Zeroes
	 numbers operator+(const numbers &) const;
	//inline numbers &operator=(const numbers &) ;
	bool operator==(const numbers &);
	bool operator!=(const numbers &);
	bool operator<(const numbers &); // Absolute Value <
	 bool operator>(const numbers &);// Absolute Value >
	 numbers operator*(const numbers &) const; //For Start I will you the first algorithm in my mind 
	 numbers operator*(const long long) ;
	 numbers operator-(const numbers &) const;
	 numbers operator/(const numbers &) const; //with Binary search. Need opt. Interpolation search may work.
	 numbers operator/(const long long) const;
	 numbers operator%(const numbers &) const;
	 numbers operator<<(int) const ; //For Small numbers
	 numbers operator>>(int) const;//For Small numbers
	~numbers();
	void assign_pos(long long, long long);
	//TODO:ofstream ifstream operators
};
template <class T>
numbers cast(T);
