#include<bits/stdc++.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pii;

int main () {
    ll r, c, n, q, MOD;
    cin >> r >> c >> n >> q >> MOD;
    vector<vector<bool> > plane(r, vector<bool>(c, false));

    For(i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        for (int ir = x1; ir < x2; ir ++) {
            for (int ic = y1; ic < y2; ic ++) {
                if (plane [ir][ic]) {
                    cerr << "BAD INPUT! " << ir << ' ' << ic << "\n";
                    exit(1);
                }
                plane [ir][ic] = true;
            }
        }
    }

/*    For(i, r) {
        For(j, c) {
            cout << plane [i][j];
        }
        cout << '\n';
    }*/

    ll lastres = 0;
    For(magic, q) {
        ll x1, y1, x2, y2, mod;
        cin >> x1 >> y1 >> x2 >> y2 >> mod;
        
        mod = ((lastres % MOD) * mod) % MOD;
        x1 = (x1 + mod) % MOD;
        x2 = (x2 + mod) % MOD;
        y1 = (y1 + mod) % MOD;
        y2 = (y2 + mod) % MOD;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        lastres = 0;
        for (int ir = x1; ir < x2; ir ++){
            for (int ic = y1; ic < y2; ic ++) {
                if (plane [ir][ic]) lastres ++;
            }
        }
        cout << lastres << '\n';
    }
}
