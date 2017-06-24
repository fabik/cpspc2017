#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <utility>

using namespace std;

const int MAXN = 1000;
const int MAXQ = 1000000;

int n, m, q;
bool empty[MAXN][MAXN];
int sr[MAXQ], sc[MAXQ], tr[MAXQ], tc[MAXQ];
pair<int, int> empty_fields[MAXN * MAXN];

void generate_random(int empty_percentage) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			empty[i][j] = (rand() % 100) < empty_percentage;
		}
	}
}

void generate_stripes(int empty_percentage) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			empty[i][j] = (i % 2 == 0) || ((rand() % 100) < empty_percentage);
		}
	}
}

void generate_random_queries() {
	int c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (empty[i][j]) {
				empty_fields[c++] = make_pair(i, j);
			}
		}
	}
	assert(c > 0);
	for (int i = 0; i < q; i++) {
		int s = rand() % c;

		bool assigned = false;
		if (i % 2 == 0) {
			sr[i] = empty_fields[s].first;
			sc[i] = empty_fields[s].second;

			for (int it = 0; it < 10; it++) {
				tr[i] = min(sr[i] + rand() % 50, n - 1);
				tc[i] = min(sc[i] + rand() % 50, m - 1);
				if (empty[tr[i]][tc[i]]) {
					assigned = true;
					break;
				}
			}
		}

		if (!assigned) {
			int t = rand() % c;
			if (t < s) swap(t, s);
			sr[i] = empty_fields[s].first;
			sc[i] = empty_fields[s].second;
			tr[i] = empty_fields[t].first;
			tc[i] = empty_fields[t].second;
		}
	}
}

int main(int argc, char **argv) {
	if (argc < 6) {
		fprintf(stderr, "Usage: ./gen <min_nm> <max_nm> <q> <type> <empty_percentage> <seed>\n");
		return 1;
	}

	int min_nm = atoi(argv[1]);
	int max_nm = atoi(argv[2]);
	q = atoi(argv[3]);
	int type = atoi(argv[4]);
	int empty_percentage = atoi(argv[5]);
	int seed = atoi(argv[6]);

	srand(seed);
	n = min_nm + rand() % (max_nm - min_nm + 1);
	m = min_nm + rand() % (max_nm - min_nm + 1);

	switch (type) {
		case 0:
			generate_random(empty_percentage);
			break;
		case 1:
			generate_stripes(empty_percentage);
			break;
	}

	generate_random_queries();

	printf("%d %d %d\n", n, m, q);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%c", empty[i][j] ? '.' : '#');
		}
		printf("\n");
	}
	for (int i = 0; i < q; i++) {
		printf("%d %d %d %d\n", sr[i] + 1, sc[i] + 1, tr[i] + 1, tc[i] + 1);
	}
	return 0;
}
