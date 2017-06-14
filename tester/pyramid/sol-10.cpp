#include <cassert>
#include <iostream>

using namespace std;

const long long MAX = 1000000000000000000LL;
const int MAXN = 15;
const int MAXQ = 1000000;

int N, M;
long long A[MAXN];
long long f[MAXN];
long long magic[MAXQ];

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	assert(N >= 1 && N <= 15);
	assert(M >= 1 && M <= 50);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		assert(A[i] >= 2 && A[i] <= MAX);
	}
	for (int i = 0; i < N; i++) {
		f[i] = A[i];
	}
	for (int i = 0; i < MAXQ; i++) {
		magic[i] = f[0];
		for (int j = 1; j < N; j++) {
			if (f[j] < magic[i]) {
				magic[i] = f[j];
			}
		}
		for (int j = 0; j < N; j++) {
			if (f[j] == magic[i]) {
				f[j] += A[j];
			}
		}
	}
	for (int i = 0; i < M; i++) {
		long long Q;
		cin >> Q;
		assert(Q >= 1 && Q <= 1000000);
		cout << magic[Q - 1] << endl;
	}
	return 0;
}
