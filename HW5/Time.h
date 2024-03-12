#include <iostream>

using namespace std;

class Time {
private:

	unsigned int days, hours, minutes, seconds;

public:

	Time();
	Time(int t);
	Time(int d, int h, int m, int s);
	Time operator+(Time& right);
	Time operator+(int right);
	Time operator-(Time& right);
	Time operator-(int right);
	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	bool operator>(Time const& right)const;
	bool operator<(Time const& right)const;
	bool operator>=(Time const& right)const;
	bool operator<=(Time const& right)const;
	bool operator==(Time const& right)const;
	bool operator!=(Time const& right)const;
	friend ostream& operator<<(ostream& stream, Time const& time);
	friend istream& operator>>(istream& stream, Time& time);
};