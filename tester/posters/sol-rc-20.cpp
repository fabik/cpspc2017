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

    vector<vector<ll> > pref(r + 5, vector<ll>(c + 5, 0)), orig = pref;

    For(i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        for(int ir = x1; ir < x2; ir++) {
            for(int ic = y1; ic < y2; ic++) {
                orig [ir][ic] = 1;
            }
        }
    }


    For(i, r+1) {
        For(j, c+1) {
            pref [i + 1][j + 1] = pref [i][j+1] + pref[i+1][j] - pref [i][j] + orig [i][j];
        }
    }

    ll lastres = 0;
    For(i, q) {
        ll x1_, y1_, x2_, y2_, v;
        cin >> x1_ >> y1_ >> x2_ >> y2_ >> v;
        ll mod = ((lastres % m) * v) % m;

        ll x1 = (x1_ + mod) % m, y1 = (y1_ + mod) % m, x2 = (x2_ + mod) % m, y2 = (y2_ + mod) % m;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        lastres = pref [x2][y2] - pref [x2][y1] - pref[x1][y2] + pref[x1][y1];
        cout << lastres << '\n';
    }
}
