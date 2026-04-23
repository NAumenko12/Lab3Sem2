#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

void input(int &n, int &m, vector<int> &chisla);
pair<int, int64_t> selectBestMove(int pos, int m, int lastMove, const vector<int> &chisla);
void playGame(const vector<int> &chisla, int m, int64_t &pavel, int64_t &vika);

int main() {
    int n{};
    int m{};
    int64_t pavel{};
    int64_t vika{};
    vector<int> chisla;
    input(n, m, chisla);
    playGame(chisla, m, pavel, vika);
    cout << (pavel > vika ? 1 : 0) << endl;
    return 0;
}

void input(int &n, int &m, vector<int> &chisla) {
    cin >> n >> m;
    chisla.resize(n);
    for (int i = 0; i < n; ++i){
        cin >> chisla[i];
    }
}

pair<int, int64_t> selectBestMove(int pos, int m, int lastMove, const vector<int> &chisla) {
    int bestK = 1;
    int64_t bestSum = INT64_MIN;
    int64_t currentSum = 0;
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

void playGame(const vector<int> &chisla, int m, int64_t &pavel, int64_t &vika) {
    int pos = 0;
    int lastMove = -1;
    bool isPavel = true;
    pavel = vika = 0;
    while (pos < (int)chisla.size()) {
        pair<int, int64_t> moveResult = selectBestMove(pos, m, lastMove, chisla);
        int bestK = moveResult.first;
        int64_t bestSum = moveResult.second;
        if (isPavel){
            pavel += bestSum;
        } 
        else{
            vika += bestSum;
        } 
        pos += bestK;
        lastMove = bestK;
        isPavel = !isPavel;
    }
}