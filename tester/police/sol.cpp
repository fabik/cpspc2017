#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000000;

int N, M;
vector<int> graph[MAXN];
bool visited[MAXN];
int stack_size;
int stack[MAXN];
bool in_stack[MAXN];
int current_num;
int num[MAXN];
int low[MAXN];
int scc_count;
int scc[MAXN];
int in_degree[MAXN];
int ans_count;
int ans_vertices[MAXN];

void tarjan(int u) {
	visited[u] = true;
	num[u] = low[u] = ++current_num;
	stack[stack_size++] = u;
	in_stack[u] = true;
	for (int v : graph[u]) {
		if (!visited[v]) {
			tarjan(v);
		}
		if (in_stack[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (low[u] == num[u]) {
		int v;
		do {
			v = stack[--stack_size];
			in_stack[v] = false;
			scc[v] = scc_count;
		} while (v != u);
		scc_count++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	assert(N >= 1 && N <= 1000000);
	assert(M >= 1 && M <= 1000000);
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		assert(a >= 1 && a <= N);
		assert(b >= 1 && b <= N);
		assert(a != b);
		a--; b--;
		graph[a].push_back(b);
	}
	for (int u = 0; u < N; u++) {
		if (!visited[u]) {
			tarjan(u);
		}
	}
	for (int u = 0; u < N; u++) {
		for (int v : graph[u]) {
			if (scc[u] != scc[v]) {
				in_degree[scc[v]]++;
			}
		}
	}
	int zero_in_degree_scc_count = 0;
	int zero_in_degree_scc = -1;
	for (int i = 0; i < scc_count; i++) {
		if (in_degree[i] == 0) {
			zero_in_degree_scc_count++;
			zero_in_degree_scc = i;
		}
	}
	if (zero_in_degree_scc_count == 1) {
		for (int i = 0; i < N; i++) {
			if (scc[i] == zero_in_degree_scc) {
				ans_vertices[ans_count++] = i;
			}
		}
	}
	cout << ans_count << endl;
	for (int i = 0; i < ans_count; i++) {
		if (i != 0) {
			cout << " ";
		}
		cout << ans_vertices[i] + 1;
	}
	cout << endl;
	return 0;
}
