#ifdef BIGNUM_H
#define BIGNUM_H
class numbers{

	/*
	Overload Function to be added
	*/
	numbers operator+(const numbers &c);
	numbers operator*(const numbers &c);
	numbers operator-(const numbers &c);
	numbers operator/(const numbers &c);
	numbers operator%(const numbers &c);
	numbers operator<<(const numbers &c);
	numbers operator>>(const numbers &c);
};
#endif