#include <iostream>
#include "Cube.h"

Cube::Cube(double a, double b, double c ) {
	x = a;
	y = b;
	z = c;
	sum = a + b + c;
	vol = a * b * c;
}

bool Cube::operator ==(Cube const& right) const {
	if ((*this).vol == right.vol) {
		return true;
	}
	else {
		return false;
	}
}

bool Cube::operator !=(Cube const& right)const {
	return !(*this == right);
}

const double operator /(Cube const& left, Cube const& right) {
	return left.sum / right.sum;
}