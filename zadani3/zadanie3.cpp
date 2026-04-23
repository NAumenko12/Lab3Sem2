#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int64_t gcd(int64_t a, int64_t b);
vector<int64_t> euler(int a);
int64_t polyEval(const vector<int64_t>& coeff, int b);
int64_t denPow(int b, int a);
pair<int64_t, int64_t> sum(int a, int b);

int main() {
    int a, b;
    cin >> a >> b;
    if (b == 1) {
        cout << "infinity\n";
    } else{
        pair<int64_t, int64_t> result = sum(a, b);
        cout << result.first << "/" << result.second << endl;
    }
    return 0;
}

int64_t gcd(int64_t a, int64_t b) { 
    while (b != 0) {
        int64_t temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

vector<int64_t> euler(int a) { 
    vector<int64_t> prev = {1};
    for (int n = 2; n <= a; ++n) {
        vector<int64_t> cur(n, 1);
        for (int k = 1; k < n - 1; ++k){
            cur[k] = (k + 1) * prev[k] + (n - k) * prev[k - 1]; 
        }
        prev.swap(cur);
    }
    return prev;
}

int64_t polyEval(const vector<int64_t>& coef, int b) { 
    int64_t res = 0;
    int64_t powB = 1;
    for (size_t k = 0; k < coef.size(); ++k) {
        res += coef[k] * powB;
        powB *= b;
    }
    return res;
}

int64_t denPow(int b, int a) { 
    int64_t res = 1;
    for (int i = 0; i <= a; ++i) {
        res *= (b - 1);
    }
    return res;
}

pair<int64_t, int64_t> sum(int a, int b) { 
    vector<int64_t> coeff = euler(a);
    int64_t poly = polyEval(coeff, b);
    int64_t num = b * poly;
    int64_t den = denPow(b, a);
    int64_t g = gcd(num, den);
    return {num / g, den / g};
}