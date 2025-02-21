#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

double calculate_average(const vector<double>& numbers) {
    double sum = 0;
    for (double num : numbers) {
        sum += num;
    }
    return sum / numbers.size();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please input numbers to find average." << endl;
        return 1;
    }

    vector<double> numbers;
    try {
        for (int i = 1; i < argc; ++i) {
            numbers.push_back(stod(argv[i]));
        }
        double avg = calculate_average(numbers);

        cout << "---------------------------------" << endl;
        cout << "Average of " << numbers.size() << " numbers = ";
        
        if (avg == floor(avg)) {
            cout << static_cast<int>(avg);
        } else {
            cout << fixed << setprecision(3) << avg;
        }
        cout << endl;
        cout << "---------------------------------" << endl;

    } catch (const exception& e) {
        cout << "Error: Please enter valid numbers." << endl;
    }

    return 0;
}

