class Cube {
private:

	double x, y, z;
	double sum = x + y + z;
	double vol = x * y * z;

public:

	Cube(double a = 1, double b = 1, double c = 1);
	bool operator==(Cube const& right)const;
	bool operator!=(Cube const& right)const;
	friend const double operator /(Cube const& left, Cube const& right);
};