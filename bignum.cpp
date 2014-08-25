#include "bignum.h"
numbers::numbers()
{
	pos = 0;
	mynum.push_back(0);
}
numbers::numbers(long long k)
{
	pos = 0;
	if (k<0)
	{
		pos = 1;
		k = -k;
	}
	if (k > BASE)
	{
			mynum.push_back(k % BASE);
			k = k / BASE;
			mynum.push_back(k);
		
	}
	else
		mynum.push_back(k);
	k++;
}
void numbers::same_size(numbers &c){
	if (mynum.size() == c.mynum.size())
		return;
	SIZE big_size = (mynum.size() > c.mynum.size()) ? mynum.size() : c.mynum.size();
	mynum.resize(big_size, 0);
	c.mynum.resize(big_size, 0); //Initialize Extra with Zeroes
}
void numbers::clean_null()
{
	SIZE toDel = 0;
/*	for (REV_IT rit = mynum.rbegin(); rit != mynum.rend(); ++rit)
	{
		if (*rit != 0)
			break;
		toDel++;
	}*/
	for (ITERATOR it = mynum.end(); it != mynum.begin();)
	{
		--it;
		if (*it != 0)
			break;
		toDel++;
	}
	SIZE res = mynum.size() - toDel;
	if (res < 0)
		std::perror("To be add"); //TODO: message to be add
	else
	mynum.resize(res);
}
bool numbers::operator==(const numbers &c)
{
	if (pos != c.pos)
		return false;
	if (mynum.size() != c.mynum.size())
		return false;
	auto it_second = c.mynum.begin();
	for (auto it_first : mynum)
	{
		if (it_first != *it_second)
			return false;
		it_second++;
	}
	return true;
}
bool numbers::operator!=(const numbers &c)
{
	if (*this == c)
		return true;
	else
		return false;
}
 numbers numbers::operator+(const numbers &c) const
{
	if (pos != c.pos)
	{
		switch (pos)
		{
		case 1:
			return c - (*this);
			break;
		default:
			return (*this) - c;
			break;
		}
	}
	numbers temp;
	numbers number1, number2;
	number1 = *this;
	number2 = c;
	number1.same_size(number2);
	temp.same_size(number1);
	unsigned long long add = 0;
	ITERATOR it_second = number2.mynum.begin();
	ITERATOR result = temp.mynum.begin();
	for (auto &it_fist : number1.mynum)
	{
		unsigned long long temp_sum = it_fist + *it_second + add;
		add = 0ULL;
		if (temp_sum >= BASE)
		{
			*result = temp_sum%BASE;
			add = temp_sum / BASE;
		}
		else
			*result = temp_sum;
		result++;
		it_second++;
	}
	if (add)
		temp.mynum.resize(temp.mynum.size()+1,add);
	return temp;
}
bool numbers::operator>(const numbers &c)
{
	if (mynum.size() > c.mynum.size())
		return true;
	else if (mynum.size() < c.mynum.size())
		return false;
	else
	{
		numbers temp1, temp2;
		temp1 = *this;
		temp2 = c;
		REV_IT rit_first = temp1.mynum.rbegin();
		REV_IT rit_second = temp2.mynum.rbegin();
		for (; rit_first != temp1.mynum.rend(); rit_first++,rit_second++)
		{
			if (*rit_first>*rit_second)
				return true;
			else if (*rit_first < *rit_second)
				return false;
		}
	}
	return false;
}
bool numbers::operator<(const numbers &c)
{
	if (mynum.size() < c.mynum.size())
		return true;
	else if (mynum.size() > c.mynum.size())
		return false;
	else
	{
		numbers temp1, temp2;
		temp1 = *this;
		temp2 = c;
		REV_IT rit_first = temp1.mynum.rbegin();
		REV_IT rit_second = temp2.mynum.rbegin();
		for (; rit_first != temp1.mynum.rend(); rit_first++,rit_second++)
		{
			if (*rit_first<*rit_second)
				return true;
			else if (*rit_first > *rit_second)
				return false;
		}
	}
	return false;
}
numbers numbers::operator*(const long long c)  
{
	return (*this) * cast(c);
}
numbers numbers::operator-(const numbers &c) const
{
	if (pos != c.pos)
	{
		numbers temp=c;
		switch (pos)
		{
		case 1:
			temp.pos = 1;
			return temp + (*this);
			break;
		default:
			temp.pos = 0;
			return temp + (*this);
			break;
		}
	}
	numbers temp;
	numbers number1, number2;
	number1 = *this;
	if (number1>c)
	{
		number2 = c;
		temp.pos = number1.pos;
	}
	else
	{
		number2 = *this;
		number1 = c;
		if (pos)
			temp.pos = 0;
		else
			temp.pos = 1;
	}
	number1.same_size(number2);
	temp.same_size(number1);
	long long add = 0;
	ITERATOR it_second = number2.mynum.begin();
	ITERATOR result = temp.mynum.begin();
	for (auto it_first : number1.mynum)
	{
		long long toDel = *it_second + add;
		if (it_first < toDel)
		{
			toDel = toDel - it_first;
			*result = BASE - toDel;
			add = 1;
		}
		else{
			add = 0;
			*result = it_first - toDel;
		}
		result++;
		it_second++;
	}
	if (add)
		temp.mynum.resize(temp.mynum.size() + 1, add);
	temp.clean_null();
	return temp;
}
numbers numbers::operator<<(int k) const
{
		numbers temp = *this;
		temp.pos = this->pos;
		ITERATOR it = temp.mynum.begin();
		temp.mynum.insert(it, 0,k);
		return temp;
}
numbers numbers::operator>>(int k) const
{
	numbers temp = *this;
	temp.pos = this->pos;
	ITERATOR it = temp.mynum.begin();
	temp.mynum.erase(it, it+k);
	return temp;
}
numbers numbers::operator%(const numbers &c) const
{
	numbers temp;
	temp.pos=0;
	temp.mynum.resize(c.mynum.size());
	temp = (*this) - (*this) / c;
	return temp;
}
/*inline numbers &numbers::operator=(const numbers &c)
{
	if (this != NULL)
		*this = c;
	else{
		numbers *temp = new numbers();
		temp->mynum = c.mynum;
		temp->pos = c.pos;
		return *temp;
	}
	return *this;
}*/
numbers numbers::operator*(const numbers &c) const
{
	numbers res;
	res.pos = pos^c.pos; //Using XOR  0X0RX=0 1XOR1=0,1XOR0=1 
	numbers num1, num2;
	num1 = *this;
	num2 = c;
	num1.same_size(num2);
	res.mynum.resize(num1.mynum.size() * 2,0);
	long long k = 0;
	while (k< num1.mynum.size())
	{
		long long temp=0;
		temp = num1.mynum[k] * num2.mynum[k];
		res.assign_pos(k, temp);
		k++;
	}
	res.clean_null();
	return res;
}
numbers numbers::operator/(const numbers &c) const
{
	numbers temp = *this;
	temp.pos = pos^c.pos;
	while (temp*c > *this)
	{
		temp = temp / 2;
	}
	numbers max = *this;
	while (temp<max)
	{
		numbers mid = (temp + max) / 2;
		if (mid*c>*this)
			max = mid-1;
		else if (mid*c < *this)
			temp = mid + 1;
		else
		{
			mid.pos = temp.pos;
			return mid;
		}
		if (!(temp < max))
			break;
	}

	if (temp*c>*this)
		temp = temp - numbers(1);
	return temp;
	/*numbers d = numbers(0);
	numbers k = numbers(0);

	while (res*c < *this)
	{
		res = res + 1;
	}
	res = res - 1;
	if (res == 0)
		return 0;
	*/

}
template <class T>
numbers cast(T a){
	if (a > 0)
	{
		numbers temp= numbers(a);
		return temp;
	}
	else
	{
		numbers temp = numbers(a);
		temp.pos = 1;
		return temp;
	}
}
numbers::~numbers()
{
	mynum.resize(0);
}
void numbers::assign_pos(long long pos, long long value_in)
{
	
	//if (pos > mynum.size()-1)
		this->mynum.resize(mynum.size()+pos+1,0);
	long long value = value_in + mynum[pos];
	if (value > BASE)
	{
		assign_pos(pos + 1, value/BASE + mynum[pos + 1]);
		mynum[pos] = value % BASE;
	}
	else
		mynum[pos] = value;
	clean_null();
}
 numbers numbers::operator/(const long long c) const{
	numbers res = numbers();
	res.pos = (c > 0) ? (this->pos ^ 0) : (this->pos ^ 1);
	res.mynum.resize(this->mynum.size());
		long long k = this->mynum.size();
		long long mod = 0;
		while (k--)
		{
			long long div = this->mynum[k] + mod*BASE;
			res.mynum[k] = div / c;
			mod = div % c;

		}
	res.clean_null();
	return res;
}