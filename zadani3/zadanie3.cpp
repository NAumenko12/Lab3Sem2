#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b);
vector<long long> euler(int a);
long long polyEval(const vector<long long>& coeff, int b);
long long denPow(int b, int a);
pair<long long, long long> sum(int a, int b);

int main() {
    int a, b;
    cin >> a >> b;

    if (b == 1) {
        cout << "infinity\n";
    } else {
        auto [num, den] = sum(a, b);
        cout << num << "/" << den << endl;
    }
    return 0;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

vector<long long> euler(int a) {
    vector<long long> prev = {1};
    for (int n = 2; n <= a; ++n) {
        vector<long long> cur(n, 1);
        for (int k = 1; k < n - 1; ++k) {
            cur[k] = (k + 1) * prev[k] + (n - k) * prev[k - 1];
        }
        prev = move(cur);
    }
    return prev;
}

long long polyEval(const vector<long long>& coef, int b) {
    long long res = 0;
    long long powB = 1;
    for (size_t k = 0; k < coef.size(); ++k) {
        res += coef[k] * powB;
        powB *= b;
    }
    return res;
}

long long denPow(int b, int a) {
    long long d = 1;
    for (int i = 0; i <= a; ++i) d *= (b - 1);
    return d;
}

pair<long long, long long> sum(int a, int b) {
    vector<long long> coeff = euler(a);
    long long poly = polyEval(coeff, b);
    long long num = b * poly;
    long long den = denPow(b, a);
    long long g = gcd(num, den);
    return {num / g, den / g};
}