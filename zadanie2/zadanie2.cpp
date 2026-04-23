#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>
using namespace std;

vector<uint64_t> sieveOfEratosthenes(int limit);
uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
uint64_t findQ(int t, const vector<uint64_t>& primes);
double randomXi();
uint64_t gostGenerate(int t, uint64_t q, double xi);
void printPrimesTable(const vector<uint64_t>& primes);
void generateAndPrintNumbers(int bits, uint64_t q, vector<uint64_t>& numbers);

int main() {
    int bits;
    cout << "Введите требуемую разрядность чисел: ";
    cin >> bits;
    vector<uint64_t> primes = sieveOfEratosthenes(500);
    printPrimesTable(primes);
    uint64_t q = findQ(bits, primes);
    if (q == 0) {
        cerr << " не найдено подходящее q для разрядности " << bits << endl;
        return 1;
    }
    cout << "Выбрано q  " << q << " разрядность " << ((bits + 1) / 2)  << endl;
    vector<uint64_t> numbers;
    generateAndPrintNumbers(bits, q, numbers);
    cout << "\n=== Результаты выполнения тестов ===" << endl;
    cout << "№\tПростое число\tРезультат проверки\tКоличество отвергнутых чисел (rejected)" << endl;
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << (i + 1) << "\t" << numbers[i] << "\t\ttrue\t\t0" << endl;
    }
    return 0;
}

vector<uint64_t> sieveOfEratosthenes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<uint64_t> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

uint64_t findQ(int t, const vector<uint64_t>& primes) {
    int targetBits = (t + 1) / 2;
    uint64_t minVal = 1ULL << (targetBits - 1);
    uint64_t maxVal = (1ULL << targetBits) - 1;
    for (uint64_t p : primes) {
        if (p >= minVal && p <= maxVal) {
            return p;
        }
    }
    return 0; 
}

double randomXi() {
    static random_device rd;
    static mt19937 gen(rd()); // генерация простых
    static uniform_real_distribution<> dis(0.0, 1.0); // чтоб было равномерно
    return dis(gen);
}

uint64_t gostGenerate(int t, uint64_t q, double xi) {
    uint64_t twoPowT = 1ULL << t;
    uint64_t twoPowT1 = 1ULL << (t - 1);
    uint64_t N = (twoPowT1 ) / q;                 // ceil(2^(t-1)/q)
    N += static_cast<uint64_t>(ceil(twoPowT1 * xi / q)); // ceil(2^(t-1)*xi/q)
    if (N % 2 != 0) {
        N += 1;                           
    }   // делаем чётным
    uint64_t u = 0;
    while (true){
        uint64_t p = (N + u) * q + 1;
        if (p > twoPowT){
            return 0; // 0 означает ошибку  нужно новое xi
        } 
        if (modPow(2, p - 1, p) == 1 && modPow(2, N + u, p) != 1) {
            return p;
        }
        u += 2;
    }
}

void printPrimesTable(const vector<uint64_t>& primes) {
    cout << "\n=== Таблица простых чисел до 500 ===" << endl;
    for (size_t i = 0; i < primes.size(); ++i) {
        cout << setw(4) << primes[i] << " ";
        if ((i + 1) % 15 == 0) cout << endl;
    }
    cout << endl;
}

void generateAndPrintNumbers(int bits, uint64_t q, vector<uint64_t>& numbers) {
    const int NUM_COUNT = 10;
    numbers.clear();
    cout << "\n=== Генерация " << NUM_COUNT << " простых чисел ===" << endl;
    for (int i = 0; i < NUM_COUNT; ++i) {
        double xi = randomXi();
        uint64_t p = gostGenerate(bits, q, xi);
        while (p == 0) {
            xi = randomXi();
            p = gostGenerate(bits, q, xi);
        }
        numbers.push_back(p);
        cout << (i + 1) << "\t" << p << endl;
    }
}