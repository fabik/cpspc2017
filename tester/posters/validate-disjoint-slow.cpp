#include<bits/stdc++.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main () {
    ll r, c, n, q, m;
    cin >> r >> c >> n >> q >> m;

    vector<vector<ll> > rects(n, vector<ll>(4));

    For(i, n) {
        For(j, 4) cin >> rects [i][j];
        if (rects [i][0] > rects [i][2]) swap(rects [i][0], rects [i][2]);
        if (rects [i][1] > rects [i][3]) swap(rects [i][1], rects [i][3]);
        For(j, i) {
            ll x = min(rects [i][2], rects [j][2]) - max(rects [i][0], rects [j][0]);
            ll y = min(rects [i][3], rects [j][3]) - max(rects [i][1], rects [j][1]);
            if (x > 0 && y > 0) {
                cerr << "Bad input: " << i << ' ' << j << "\n";
                return 1;
            }
        }
    }
}
