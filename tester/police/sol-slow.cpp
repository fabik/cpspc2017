#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000000;

int N, M;
vector<int> graph[MAXN];
bool visited[MAXN];
int ans_count;
int ans_vertices[MAXN];

void dfs(int u) {
	visited[u] = true;
	for (int v : graph[u]) {
		if (!visited[v]) {
			dfs(v);
		}
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[j] = false;
		}
		dfs(i);
		bool can_reach_all = true;
		for (int j = 0; j < N; j++) {
			if (!visited[j]) {
				can_reach_all = false;
				break;
			}
		}
		if (can_reach_all) {
			ans_vertices[ans_count++] = i;
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
