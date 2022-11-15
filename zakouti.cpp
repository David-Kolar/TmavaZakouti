#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<bool>> graf, navstiveno;


struct Souradnice {
    int x;
    int y;
};
inline int solve() {
    queue<Souradnice> fronta;
    fronta.push({1, 1});
    navstiveno[1][1] = true;
    Souradnice aktualni;
    int maximumX = 1;
    int pocitadlo = 0;
    bool pokracovat;
    while (true) {
        if (fronta.empty()) {
            pokracovat = false;
            pocitadlo += 1;
            if (maximumX == N)
                return pocitadlo;
            for (int y = 1; y <= N; y++) {
                if (graf[maximumX+1][y] and !navstiveno[maximumX+1][y]) {
                    pokracovat = true;
                    navstiveno[maximumX+1][y] = true;
                    fronta.push({maximumX+1, y});
                }
            }
            if (not pokracovat) return -1;
        }
        aktualni = fronta.front();
        fronta.pop();
        maximumX = max(maximumX, aktualni.x);
        if (aktualni.x == N and aktualni.y == N)
            return pocitadlo;
        for (auto policko : vector<Souradnice>{{aktualni.x - 1, aktualni.y},
                                                   {aktualni.x + 1, aktualni.y},
                                                   {aktualni.x, aktualni.y + 1},
                                                   {aktualni.x, aktualni.y - 1}}) {
            if ((policko.y <= N) and (policko.x <= N)) {
                if ((not navstiveno[policko.x][policko.y]) and (graf[policko.x][policko.y])){
                    navstiveno[policko.x][policko.y] = true;
                    fronta.push({policko.x, policko.y});
                }

            }
        }
    }
}

int main() {
    cin >> N >> M;
    int x, y;
    graf.resize(N+1, vector<bool>(N+1, false));
    navstiveno.resize(N+1, vector<bool>(N+1, false));
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        graf[x][y] = true;
    }
    cout << solve();
    return 0;
}
