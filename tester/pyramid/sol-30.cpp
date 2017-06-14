#include <cassert>
#include <iostream>

using namespace std;

const long long MAX = 1000000000000000000LL;
const int MAXN = 15;

int N, M;
long long A[MAXN];

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
	if (N == 1) {
		return x / A[0];
	}

	if (N == 2) {
		return x / A[0] + x / A[1] - x / lcm(A[0], A[1]);
	}

	assert(false);
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
	for (int i = 0; i < M; i++) {
		long long Q;
		cin >> Q;
		assert(Q >= 1 && Q <= MAX);
		cout << solve(Q) << endl;
	}
	return 0;
}
