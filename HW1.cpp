#include <iostream>
#include <string>
using namespace std;

int main() {
    int number; // The number of scores read.
    int sum; // The summation of all the scores read.
    int grade; // Holds each individual score as it is read from the keyboard.
    float average; // Holds the computed average.
    string str;
    number = 0; // Initialize number and sum to 0 before starting.
    sum = 0;
    average = 0;
    cout << "Please input your score : ";
    // Infinite Loop.
    while (1) {
        cin >> str; // Get the user input.
        //There will have exception when user input a string or char.
        try {
            //Check the input is an integer or not.
            if (str.find(".") != string::npos || !stoi(str)) {
                cout << "The score is invaild! Please input the right score !" << endl;
                return -1;
            }
            else {
                grade = stoi(str);
                if (grade >= 0 && grade <= 100) {
                    sum = sum + grade; // Add new score into sum
                    number = number + 1; // and count one more grade
                    cout << "Please input the next score or input -1 to show the average :";
                    continue;
                }
                // When done reading scores, compute average and display.
                else if (grade == -1) {
                    average = (float)sum / number;
                    cout << "Your average score is : " << average << endl;
                    // When done, exit the program.
                    return 0;
                }
            }
        }
        //Catch the exception and handle it.
        catch (exception& e) {
            cout << "The score is invaild! Please input the right score !" << endl;
            return -1;
        }
    }
}
