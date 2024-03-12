#include <iostream>
#include <fstream>
using namespace std;

int getDigit(int number) {
    int q = number / 10;
    if (q != 0) {
        return q + number % 10;
    }
    else {
        return number;
    }
}

int sumofDoubleEvenPlace(const string& cardNumber) {
    int l = cardNumber.length();
    int sum = 0;
    for (int i = l - 2; i >= 0; i -= 2) {
        int d = (cardNumber[i] - '0') * 2;
        sum += getDigit(d);
    }
    return sum;
}

int sumOfOddPlace(const string& cardNumber) {
    int l = cardNumber.length();
    int sum = 0;
    for (int i = l-1; i >= 0; i -= 2) {
        sum += (cardNumber[i] - '0');
    }
    return sum;
}

bool startsWith(const string& cardNumber, const string& substr) {
    return true;
}

bool isvalid(const string& cardNumber) {
    int sum = sumOfOddPlace(cardNumber) + sumofDoubleEvenPlace(cardNumber);
    if (sum % 10 != 0) {
        return false;
    }
    else {
        return true;
    }
}

int main(int args, char** argv) {
    const string a = "4388576018402626";
    cout << isvalid(a) << endl;
    return 0;
}