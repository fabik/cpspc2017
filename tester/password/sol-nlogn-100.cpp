#include<bits/stdc++.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define MOD 1000000009
#define P 251

ll power(ll a, ll b) {
    ll sq = a, res = 1;
    while (b > 0) {
        if (b % 2 != 0) res *= sq;
        b /= 2;
        sq *= sq;
        res %= MOD;
        sq %= MOD;
    }
    return res;
}
vector<ll> pows, inv;
vector<ll> roll;

ll getroll(ll from, ll to) { // [)
    return (roll[to] - (roll [from] * pows [to - from]) % MOD + MOD) % MOD;
}

int main () {
    int n;
    cin >> n;
    string s;
    cin >> s;

    pows.resize(n+1, 1);
    inv.resize(n+1, 1);

    pows[1] = P;
    inv[1] = power(P, MOD - 2);

    for(int i = 2; i <= n; i++) {
        pows [i] = (P*pows[i - 1]) % MOD;
        inv [i] = (inv[1] * inv [i - 1]) % MOD;
    }

    roll.resize(n+1, 0);
    For(i, n) roll [i + 1] = (roll [i] * P + s [i]) % MOD;

    for (int i = (n+1) / 2; i < n; i++) {
//        cout << i << ' ' << getroll(0, n - i) << ' ' << getroll(i, n) << endl;
        if (getroll(0, n - i) == getroll(i, n)) continue;
        int l = 0, u = n - i;

        bool satisfying = true;
        while (u - l > 1) {
            int mid = (l + u) / 2;
            if (getroll(l, mid) == getroll(i + l, i + mid)) l = mid;
            else if (getroll(mid, u) == getroll(i + mid, i + u)) u = mid;
            else {
                satisfying = false;
                break;
            }
        }

        if (satisfying) {
            cout << i << endl;
            return 0;
        }
    }
    cout << "-1\n";
}
