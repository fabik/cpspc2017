#include <cassert>
#include <iostream>

using namespace std;

const long long MAX = 1000000000000000000LL;
const int MAXN = 15;

int N, M;
long long A[MAXN];
long long set_lcm[1 << MAXN];
int set_size[1 << MAXN];

long long gcd(long long a, long long b) {
	while (b != 0) {
		long long c = a % b;
		a = b;
		b = c;
	}
	return a;
}

long long lcm(long long a, long long b) {
	return a / gcd(a, b) * b;
}

long long count_magic_numbers_lower_than_or_equal_to(long long x) {
	long long count = 0;
	for (int s = 1; s < (1 << N); s++) {
		count += (x / set_lcm[s]) * (set_size[s] % 2 == 1 ? 1 : -1);
	}
	return count;
}

long long solve(long long Q) {
	long long low = 1, high = MAX;
	while (low < high) {
		long long mid = (low + high) / 2;
		if (count_magic_numbers_lower_than_or_equal_to(mid) < Q) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}
	return low;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	assert(N >= 1 && N <= 15);
	assert(M >= 1 && M <= 50);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		assert(A[i] >= 2 && A[i] <= MAX);
	}
	for (int s = 1; s < (1 << N); s++) {
		set_lcm[s] = 1;
		set_size[s] = 0;
		for (int i = 0; i < N; i++) {
			if (s & (1 << i)) {
				set_lcm[s] = lcm(set_lcm[s], A[i]);
				set_size[s]++;
			}
		}
	}
	for (int i = 0; i < M; i++) {
		long long Q;
		cin >> Q;
		assert(Q >= 1 && Q <= MAX);
		cout << solve(Q) << endl;
	}
	return 0;
}
