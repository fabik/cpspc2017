#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>

using namespace std;

const long long MAX = 1000000000000000000LL;
const int MAXN = 15;

long long get_random(long long a, long long b) {
	long long r1 = rand() & ((1 << 15) - 1);
	long long r2 = rand() & ((1 << 15) - 1);
	long long r3 = rand() & ((1 << 15) - 1);
	long long r4 = rand() & ((1 << 15) - 1);
	long long r = (r1 << 45) | (r2 << 30) | (r3 << 15) | r4;
	return a + r % (b - a + 1);
}

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

int main(int argc, char **argv) {
	if (argc < 7) {
		fprintf(stderr, "Usage: ./gen <min-n> <max-n> <m> <min-q> <max-q> <seed>\n");
		return 1;
	}

	int min_n = atoi(argv[1]), max_n = atoi(argv[2]), m = atoi(argv[3]);
	long long min_q = atoll(argv[4]), max_q = atoll(argv[5]);
	int seed = atoi(argv[6]);

	srand(seed);
	N = get_random(min_n, max_n);
	M = m;

	__int128 prod = 1;
	for (int i = 0; i < N; i++) {
		long long max_a = (MAX / prod) >> ((N - i) * 2);
		int min_log_a = 1, max_log_a = log2l(max_a);
		assert(min_log_a <= max_log_a);
		int log_a = get_random(min_log_a, max_log_a);
		A[i] = get_random(1LL << log_a, (1LL << (log_a + 1)) - 1);
		prod *= A[i];
		assert(prod <= MAX);
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

	max_q = min(max_q, count_magic_numbers_lower_than_or_equal_to(MAX));
	assert(min_q <= max_q);

	printf("%d %d\n", N, M);
	for (int i = 0; i < N; i++) {
		if (i != 0) printf(" ");
		printf("%lld", A[i]);
	}
	printf("\n");
	for (int i = 0; i < M; i++) {
		printf("%lld\n", get_random(min_q, max_q));
	}

	return 0;
}
