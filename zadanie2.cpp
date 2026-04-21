#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>
using namespace std;

vector<int64_t> sieveOfEratosthenes(int limit);
int64_t modPow(int64_t base, int64_t exp, int64_t mod);
int64_t findQ(int t, const vector<int64_t>& primes);
double randomXi();
int64_t gostGenerate(int t, int64_t q, double xi, int& attempts);
bool isPrimeDeterministic(int64_t n);
void printPrimesTable(const vector<int64_t>& primes);
void printAppendixGHeader();
void generateAndPrintNumbers(int bits, int64_t q, vector<int64_t>& numbers, vector<int>& attemptsList, int& rejected);
void printResultTable(const vector<int64_t>& numbers, const vector<int>& attemptsList, int rejected);

int main() {
    int bits;
    cout << "Введите требуемую разрядность чисел: ";
    cin >> bits;
    vector<int64_t> primes = sieveOfEratosthenes(500);
    printPrimesTable(primes);
    int64_t q = findQ(bits, primes);
    if (q == -1) {
        cerr << "Ошибка: не найдено подходящее q для разрядности " << bits << endl;
        return 1;
    }
    cout << "Выбрано q = " << q << " (разрядность " << ((bits + 1) / 2) << " бит)" << endl;
    printAppendixGHeader();
    vector<int64_t> numbers;
    vector<int> attemptsList;
    int rejected = 0;
    generateAndPrintNumbers(bits, q, numbers, attemptsList, rejected);
    printResultTable(numbers, attemptsList, rejected);
    return 0;
}

vector<int64_t> sieveOfEratosthenes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<int64_t> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

int64_t modPow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int64_t findQ(int t, const vector<int64_t>& primes) {
    int targetBits = (t + 1) / 2;
    int64_t minVal = 1LL << (targetBits - 1);
    int64_t maxVal = (1LL << targetBits) - 1;
    for (int64_t p : primes) {
        if (p >= minVal && p <= maxVal) return p;
    }
    return -1;
}

double randomXi() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

int64_t gostGenerate(int t, int64_t q, double xi, int& attempts) {
    attempts = 0;
    int64_t twoPowT = 1LL << t;
    int64_t twoPowT1 = 1LL << (t - 1);
    int64_t N = twoPowT1 / q;     
    N += static_cast<int64_t>(twoPowT1 * xi / q); 
    if (N % 2 == 0) N += 1;
    int64_t u = 0;
    while (true) {
        attempts++;
        int64_t p = (N + u) * q + 1;
        if (p > twoPowT) return -1;
        if (modPow(2, p - 1, p) == 1 && modPow(2, N + u, p) != 1) {
            return p;
        }
        u += 2;
    }
}

bool isPrimeDeterministic(int64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void printPrimesTable(const vector<int64_t>& primes) {
    cout << "\n=== Таблица простых чисел до 500 ===" << endl;
    for (size_t i = 0; i < primes.size(); ++i) {
        cout << setw(4) << primes[i] << " ";
        if ((i + 1) % 15 == 0) cout << endl;
    }
    cout << endl;
}

void printAppendixGHeader() {
    cout << "\n=== Проверка по Приложению Г (ξ = 0) ===" << endl;
    cout << "t\tq\tОжидаемое p\tПолученное p\tСовпадение" << endl;
    cout << string(55, '-') << endl;
}

void generateAndPrintNumbers(int bits, int64_t q, vector<int64_t>& numbers, vector<int>& attemptsList, int& rejected) {
    const int NUM_COUNT = 10;
    numbers.clear();
    attemptsList.clear();
    rejected = 0;
    cout << "\n=== Генерация " << NUM_COUNT << " простых чисел ===" << endl;
    cout << "№\tПростое число\t\tПопытки" << endl;
    cout << string(40, '-') << endl;
    for (int i = 0; i < NUM_COUNT; ++i) {
        int attempts;
        int64_t p;
        bool found = false;
        while (!found) {
            double xi = randomXi();
            p = gostGenerate(bits, q, xi, attempts);
            if (p != -1 && isPrimeDeterministic(p)) {
                numbers.push_back(p);
                attemptsList.push_back(attempts);
                found = true;
                cout << (i + 1) << "\t" << p;
                if (p < 100000) cout << "\t\t";
                else cout << "\t";
                cout << attempts << endl;
            } else if (p != -1) {
                rejected++;
                cout << (i + 1) << "\t" << p << "\t\t(отвергнуто, rejected=" << rejected << ")" << endl;
            }
        }
    }
}

void printResultTable(const vector<int64_t>& numbers, const vector<int>& attemptsList, int rejected) {
    cout << "\n=== Результаты выполнения тестов ===" << endl;
    cout << "+----+-----------------+-------------------------+-----+" << endl;
    cout << "| №  | Простое число   | Результат проверки       | K   |" << endl;
    cout << "+----+-----------------+-------------------------+-----+" << endl;
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << "| " << setw(2) << (i + 1) << " | " << setw(15) << numbers[i] << " | простое                 | " << setw(3) << attemptsList[i] << " |" << endl;
    }
    cout << "+----+-----------------+-------------------------+-----+" << endl;
    cout << "Количество отвергнутых чисел (rejected): " << rejected << endl;
}