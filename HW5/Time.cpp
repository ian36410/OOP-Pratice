#include <iostream>
#include <string>
#include "Time.h"

using namespace std;

Time::Time() {
	days = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;
}

Time::Time(int t) {
	if (t < 0) {
		days = 0;
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	else if (t >= 60) {
		seconds = t % 60;
		minutes = t / 60;
		if (minutes >= 60) {
			hours = minutes / 60;
			minutes = minutes % 60;
			if (hours >= 24) {
				days = hours / 24;
				hours = hours % 24;
			}
		}
		else {
			days = 0;
			hours = 0;
		}
	}
	else {
		days = 0;
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
}

Time::Time(int d, int h, int m, int s) {
	if (d < 0 || h < 0 || m < 0 || s < 0) {
		days = 0;
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	else {
		days = d;
		hours = h;
		minutes = m;
		seconds = s;
		if (seconds >= 60) {
			minutes = m + seconds / 60;
			seconds %= 60;
		}
		if (minutes >= 60) {
			hours = h + minutes / 60;
			minutes %= 60;
		}
		if (hours >= 24) {
			days = d + hours / 24;
			hours %= 24;
		}
	}
}

ostream& operator<<(ostream& output, Time const& time) {
	output << time.days << "~" << time.hours << ":" << time.minutes << ":" << time.seconds;
	return output;
}

istream& operator>>(istream& input, Time& time) {
	string s;
	input >> s;
	if (stoi(s.substr(0, s.find("~"))) < 0) {
		time.days = 0;
	}
	else {
		time.days = stoi(s.substr(0, s.find("~")));
	}
	if (stoi(s.substr(s.find("~") + 1, s.find(":") - s.find("~"))) < 0) {
		time.hours = 0;
	}
	else {
		time.hours = stoi(s.substr(s.find("~") + 1, s.find(":") - s.find("~")));
		if (time.hours >= 24) {
			time.days += (int)time.hours / 24;
			time.hours %= 24;
		}
	}
	if (stoi(s.substr(s.find(":") + 1, s.rfind(":") - s.find(":"))) < 0) {
		time.minutes = 0;
	}
	else {
		time.minutes = stoi(s.substr(s.find(":") + 1, s.rfind(":") - s.find(":")));
		if (time.minutes >= 60) {
			time.hours += time.minutes / 60;
			time.minutes %= 60;
		}
	}
	if (stoi(s.substr(s.rfind(":") + 1, s.length() - s.find(":") - 1)) < 0) {
		time.seconds = 0;
	}
	else {
		time.seconds = stoi(s.substr(s.rfind(":") + 1, s.length() - s.find(":") - 1));
		if (time.seconds >= 60) {
			time.minutes += time.seconds / 60;
			time.seconds %= 60;
		}
	}
	return input;
}

Time Time::operator+(Time& right) {
	int d, h, m, s;
	d = days + right.days;
	h = hours + right.hours;
	m = minutes + right.minutes;
	s = seconds + right.seconds;
	return Time(d, h, m, s);
}

Time Time::operator+(int right) {
	int d, h, m, s;
	Time r(right);
	d = days + r.days;
	h = hours + r.hours;
	m = minutes + r.minutes;
	s = seconds + r.seconds;
	return Time(d, h, m, s);
}

Time Time::operator-(Time& right) {
	int d, h, m, s;
	d = days - right.days;
	h = hours - right.hours;
	m = minutes - right.minutes;
	s = seconds - right.seconds;
	return Time(d, h, m, s);
}

Time Time::operator-(int right) {
	int d, h, m, s;
	Time r(right);
	d = days - r.days;
	h = hours - r.hours;
	m = minutes - r.minutes;
	s = seconds - r.seconds;
	return Time(d, h, m, s);
}

bool Time::operator>(Time const& right)const {
	if (days > right.days) {
		return true;
	}
	else if(days == right.days) {
		if (hours > right.hours) {
			return true;
		}
		else if (hours == right.hours) {
			if (minutes > right.minutes) {
				return true;
			}
			else if (minutes == right.minutes) {
				if (seconds > right.seconds) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Time::operator<(Time const& right)const {
	return !((*this) > right);
}

bool Time::operator>=(Time const& right)const {
	if (days < right.days) {
		return false;
	}
	else if (days == right.days) {
		if (hours < right.hours) {
			return false;
		}
		else if (hours == right.hours) {
			if (minutes < right.minutes) {
				return false;
			}
			else if (minutes == right.minutes) {
				if (seconds < right.seconds) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}

bool Time::operator<=(Time const& right)const {
	if (days > right.days) {
		return false;
	}
	else if (days == right.days) {
		if (hours > right.hours) {
			return false;
		}
		else if (hours == right.hours) {
			if (minutes > right.minutes) {
				return false;
			}
			else if (minutes == right.minutes) {
				if (seconds > right.seconds) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}

bool Time::operator==(Time const& right)const {
	if (days == right.days && hours == right.hours && minutes == right.minutes && seconds == right.seconds) {
		return true;
	}
	else {
		return false;
	}
}

bool Time::operator!=(Time const& right)const {
	return !(*this == right);
}

Time& Time::operator++() {
	++seconds;
	*this = Time(days, hours, minutes, seconds);
	return *this;
}

Time Time::operator++(int) {
	Time temp = *this;
	++ *this;
	return temp;
}

Time& Time::operator--(){
	if (seconds == 0) {
		if (minutes == 0) {
			if (hours == 0) {
				if (days == 0) {
					return *this;
				}
				else {
					--days;
					hours += 23;
					minutes += 59;
					seconds += 59;
					return *this;
				}
			}
			else {
				--hours;
				minutes += 59;
				seconds += 59;
				return *this;
			}
		}
		else {
			--minutes;
			seconds += 59;
			return *this;
		}
	}
	else {
		--seconds;
		return *this;
	}
}

Time Time::operator--(int) {
	Time temp = *this;
	-- *this;
	return temp;
}