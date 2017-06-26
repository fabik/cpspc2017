#include<bits/stdc++.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main () {
    int n;
    string s;
    cin >> n >> s;
    for (int i = (n+1)/2; i < n; i++) {
        int ch = 0;
        For(j, n - i) {
            if (s [j] != s [i+j]) {
                ch++;
                if (ch > 1) break;
            }
        }
        if (ch == 1) {
            cout << i << endl;
            return 0;
        }
    }
    cout << "-1\n";
}
