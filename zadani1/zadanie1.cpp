#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x);
double leftLine(double x);
double leftSemicircle(double x);
double logFunction(double x);
double rightSemicircle(double x);
double rightLine(double x);

int main() {
    double xStart{};
    double xEnd{};
    double dx{};
    cout << "Введите Xнач, Xкон и шаг dx: ";
    cin >> xStart ;
    cin >> xEnd ;
    cin >> dx ;
    cout << fixed << setprecision(2);
    cout << "|   x   |   f(x)   |" << endl;
    cout << "-------------------" << endl;
    for (double x = xStart; x <= xEnd + dx / 2; x += dx) {
        double y = f(x);
        cout << "| " << setw(6) << x << " | " << setw(8) << y << " |" << endl;
    }
    return 0;
}

double f(double x) {
    if (x < -6) {
        return leftLine(x);
    }
    else if (x <= -2) {
        return leftSemicircle(x);
    }
    else if (x <= 2) {
        return logFunction(x);
    }
    else if (x <= 4) {
        return rightSemicircle(x);
    }
    else {
        return rightLine(x);
    }
}

double leftLine(double x) {
    return -2 * x - 14;
}

double leftSemicircle(double x) {
    return -2 + sqrt(4 - pow(x + 4, 2));
}

double logFunction(double x) {
    return log2(x + 2);
}

double rightSemicircle(double x) {
    return sqrt(1 - pow(x - 3, 2));
}

double rightLine(double x) {
    return 0;
}