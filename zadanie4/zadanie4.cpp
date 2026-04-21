#include <iostream>
#include <vector>
using namespace std;

void input(int &n, int &m, vector<int> &chisla);
pair<int, long long> selectBestMove(int pos, int m, int lastMove, const vector<int> &chisla);
void playGame(const vector<int> &chisla, int m, long long &pavel, long long &vika);

int main() {
    int n{};
    int m{};
    vector<int> chisla;
    input(n, m, chisla);
    long long pavel, vika;
    playGame(chisla, m, pavel, vika);
    cout << (pavel > vika ? 1 : 0) << endl;
    return 0;
}

void input(int &n, int &m, vector<int> &chisla) {
    cin >> n;
    cin >> m;
    vector<int> chisla(n);
    for (int i = 0; i < n; ++i) {
        cin >> chisla[i];
    }
}

pair<int, long long> selectBestMove(int pos, int m, int lastMove, const vector<int> &chisla) {
    int bestK = 1;
    long long bestSum = -1e18;        
    long long currentSum = 0;
    for (int k = 1; k <= m && pos + k <= (int)chisla.size(); ++k) {
        if (k == lastMove){
            continue;
        } 
        currentSum += chisla[pos + k - 1];
        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestK = k;
        }
    }
    return {bestK, bestSum};
}

void playGame(const vector<int> &chisla, int m, long long &pavel, long long &vika) {
    int pos = 0;
    int lastMove = -1;
    bool isPavel = true;
    pavel = vika = 0;
    while (pos < (int)chisla.size()) {
        auto [bestK, bestSum] = selectBestMove(pos, m, lastMove, chisla);
        if (isPavel)
            pavel += bestSum;
        else
            vika += bestSum;
        pos += bestK;
        lastMove = bestK;
        isPavel = !isPavel;
    }
}