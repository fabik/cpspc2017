# include <bits/stdc++.h>
# include "oi.h"
# define assert_clear assert(m == 0 && n == 0 && first == 1 && last == 1);
oi::Random rrr;
using namespace std;
int group_nr = 1;
int test_nr = 0;
const string problem_id = "naw";
const int MN = 200, MM = 2000;
vector <pair <int, char> > opening_graph[MN + 1];
vector <pair <int, char> > closing_graph[MN + 1];
int n = 0;
int m = 0;
int BRACKET_TYPES = 4;
char opening[] = "{[<(";
char closing[] = "}]>)";
char all[] = "{}[]<>()";
int first = 1, last = 1;

char random_bracket() {
	return all[rrr.randUInt() % (2 * BRACKET_TYPES)];
}
char random_opening_bracket() {
	return opening[rrr.randUInt() % BRACKET_TYPES];
}
char random_closing_bracket() {
	return closing[rrr.randUInt() % BRACKET_TYPES];
}


struct edge {
	int x, y;
	char c;
	edge(int x_, int y_, char c_) : x(x_), y(y_), c(c_) {}
};
vector <edge> edges;


char val[128];
typedef long long res_t;
res_t dp[MN + 1][MN + 1];
const res_t inf = 1e18;
set <pair <res_t, pair <int, int> > > dijkstra_queue;
void enque(int start, int end, res_t value) {
	if (dp[start][end] > value) {
		dijkstra_queue.erase(make_pair(dp[start][end], make_pair(start, end)));
		dp[start][end] = value;
		dijkstra_queue.insert(make_pair(dp[start][end], make_pair(start, end)));
	}
}
void init() {
	val['['] = 1;
	val[']'] = -1;
	val['{'] = 2;
	val['}'] = -2;
	val['('] = 3;
	val[')'] = -3;
	val['<'] = 4;
	val['>'] = -4;
}
void calc() {
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			dp[i][k] = inf;
	for (int i = 1; i <= n; ++i)
		enque(i, i, 0);
	while (dijkstra_queue.size()) {
		auto curr = *dijkstra_queue.begin();
		dijkstra_queue.erase(dijkstra_queue.begin());
		int start = curr.second.first, end = curr.second.second;
		for (int i = 1; i <= n; ++i) {
			enque(start, i, dp[start][end] + dp[end][i]);
			enque(i, end, dp[i][start] + dp[start][end]);
		}
		for (auto x : opening_graph[start])
			for (auto y : closing_graph[end])
				if (x.second == y.second)
					enque(x.first, y.first, dp[start][end] + 2);
	}
}
pair <int, int> furthest() {
	calc();
	pair <int, int> res;
	res_t out = -1;
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			if (dp[i][k] > out && dp[i][k] != inf) {
				out = dp[i][k];
				res = make_pair(i, k);
			}
	return res;
}
pair <int, int> unreachable() {
	calc();
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			if (dp[i][k] == inf)
				return make_pair(i, k);
	assert(false);
}
void reset() {
	first = last = 1;
	for (int i = 1; i <= n; ++i) {
		opening_graph[i].clear();
		closing_graph[i].clear();
	}
	edges.clear();
	n = 0;
	m = 0;
}
int new_vertex() {
	assert(n < MN);
	return ++n;
}
char matching(char b) {
	for (int i = 0; ; ++i)
		if (opening[i] == b)
			return closing[i];
		else if (closing[i] == b)
			return opening[i];
}
string invert(const string & a) {
	string res;
	for (int i = a.size() - 1; i >= 0; --i)
		res.push_back(matching(a[i]));
	return res;
}
void add_edge(int x, int y, char c) {
	assert(1 <= x && x <= n && 1 <= y && y <= n);
	edges.push_back(edge(x, y, c));
	c = val[(int)c];
	if (c > 0)
		opening_graph[y].push_back(make_pair(x, c));
	else
		closing_graph[x].push_back(make_pair(y, -c));
	m++;
	assert(m <= MM);
}
string operator * (int n, const string & a) {
	string res;
	for (int i = 0; i < n; ++i)
		res += a;
	return res;
}
string operator * (const string & a, int n) {
	return n * a;
}
void add_path(int first, int last, const string & labels) {
	int prev = first;
	for (size_t i = 0; i < labels.size(); ++i) {
		int next = (i + 1 == labels.size()) ? last : new_vertex();
		add_edge(prev, next, labels[i]);
		prev = next;
	}
}
enum {
	NONE = 0,
	INVERT = 0x1,
	SHUFFLE_EDGES = 0x2,
	SHUFFLE_VERTICES = 0x4,
};
void output(int flags) {
	bool DAG = group_nr == 5;
	static int rnr[MN + 1];
	for (int i = 1; i <= n; ++i)
		rnr[i] = i;
	if (!DAG)
		rrr.randomShuffle(rnr + 1, rnr + n + 1);
	assert(1 <= first && first <= n && 1 <= last && last <= n);
	assert(test_nr < 26);
	string name = ("test/0"+to_string(group_nr) +"." + string(1, 'a' + test_nr) + ".in");
	test_nr++;
	cerr << name << endl;
	ofstream out;
	out.open(name);
	bool invert = (!DAG && rrr.randUInt() % 2);
	if (invert)
		swap(first, last);
	out << n << ' ' << m << ' ' << rnr[first] << ' ' << rnr[last] << '\n';
	if (!DAG)
		rrr.randomShuffle(edges.begin(), edges.end());
	for (auto edge : edges) {
		if (invert)
			swap(edge.x, edge.y);
		out << rnr[edge.x] << ' ' << rnr[edge.y] << ' ' << (invert ? matching(edge.c) : edge.c) << '\n';
	}
	reset();
}
void make_random_closing_with_opening_on_loops(int seed, int n_, int m_, std::initializer_list <std::string> loops, int last_ = -1, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = 1;
	for (auto loop : loops) {
		add_path(1, 1, loop);
	}
	n = n_;
	while (m < m_) {
		int x = rrr.randUInt() % n + 1;
		int y = rrr.randUInt() % n + 1;
		char c = random_closing_bracket();
		add_edge(x, y, c);
	}
	if (last_ == -1) {
		auto longest = furthest();
		first = longest.first;
		last = longest.second;
	}
	else {
		first = 1;
		last = last_;
	}
	do_after();
	output(flags);
}
void append(const string & labels, int iterations) {
	add_path(last, first, labels);
	int new_end = new_vertex();
	add_path(first, new_end, invert(labels) * iterations);
	last = new_end;
}
void new_group() {
	assert_clear;
	assert(test_nr > 0);
	group_nr ++;
	test_nr = 0;
}
void make_test_with_big_result(int seed, int flags, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	first = last = n = 1;
	append("{{", 5);
	append("[(", 5);
	append("[<", 5);
	append("{[", 5);
	append("((", 6);
	append("([", 6);
	append("<{", 6);
	append("<[", 6);
	append("({", 6);
	append("(<", 6);
	append("{<", 6);
	append("<(", 6);
	append("{(", 6);
	append("[{", 6);
	append("[[", 6);
	append("<", 12);
	do_after();
	output(flags);
}

void make_small_test_with_appending_twice_and_random_noise(int seed, int noise, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	first = last = n = 1;
	append("({}", 2);
	append("<<", 5);
	for (int i = 0; i < noise; ++i) {
		int x = rrr.randUInt() % n + 1;
		int y = rrr.randUInt() % n + 1;
		add_edge(x, y, rrr.randUInt() % 2 ? '>' : '}');
	}
	do_after();
	output(flags);
}

void make_small_test_with_big_result(int seed, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	first = last = n = 1;
	append("(", 4);
	append("[", 5);
	append("<", 5);
	append("{", 5);
	do_after();
	output(flags);
}

void add_random_edge() {
	int x = rrr.randUInt() % n + 1;
	int y = rrr.randUInt() % n + 1;
	char c = random_bracket();
	add_edge(x, y, c);
}

void add_random_directed_edge() {
	int x = rrr.randUInt() % n + 1;
	int y = rrr.randUInt() % (n - 1) + 1;
	if (y >= x)
		y++;
	else
		swap(x, y);
	char c = random_bracket();
	add_edge(x, y, c);
}

void make_completely_random_test(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	first = rrr.randUInt() % n + 1;
	last = rrr.randUInt() % n + 1;
	for (int i = 0; i < m_; ++i)
		add_random_edge();
	do_after();
	output(flags);
}

void make_random_test_with_answer_no(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	for (int i = 0; i < m_; ++i)
		add_random_edge();
	furthest();
	first = -1;
	bool done = false;
	for (int i = 1; i <= n && !done; ++i)
		for (int k = 1; k <= n && !done; ++k)
			if (dp[i][k] == inf) {
				first = i;
				last = k;
				done = true;
			}
	assert(first != -1);
	do_after();
	output(flags);
}

void make_random_test_with_query_about_furthest(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	for (int i = 0; i < m_; ++i)
		add_random_edge();
	pair <int, int> longest = furthest();
	
	first = longest.first;
	last = longest.second;
	do_after();
	output(flags);
}
void make_random_test_with_a_cycle(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	for (int i = 1; i <= n; ++i)
		add_edge(i, i % n + 1, random_bracket());
	for (int i = n + 1; i <= m_; ++i)
		add_random_edge();
	pair <int, int> longest = furthest();
	first = longest.first;
	last = longest.second;
	do_after();
	output(flags);
}
void make_random_test_with_a_cycle_and_answer_no(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	for (int i = 1; i <= n; ++i)
		add_edge(i, i % n + 1, random_bracket());
	for (int i = n + 1; i <= m_; ++i)
		add_random_edge();
	pair <int, int> longest = unreachable();
	first = longest.first;
	last = longest.second;
	do_after();
	output(flags);
}
void make_simple_test_with_one_type_of_brackets(int seed, int n_, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = n_;
	add_edge(1, 1, '(');
	for (int i = 1; i < n_; ++i)
		add_edge(i, i + 1, ')');
	first = 1, last = n_;
	do_after();
	output(flags);
}
void make_small_manual_test_2(int seed, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = 10;
	//cycles at vertex 1 with { and ([
	add_edge(1, 1, '{');
	add_edge(1, 2, '(');
	add_edge(2, 1, '[');
	
	add_edge(1, 3, ']');
	add_edge(3, 4, ')');
	add_edge(4, 5, ']');
	add_edge(5, 6, ')');
	add_edge(6, 5, '}');
	add_edge(5, 7, ']');
	add_edge(7, 8, '<');
	add_edge(8, 9, '>');
	add_edge(9, 10, ')');
	first = 1;
	last = 10;
	do_after();
	output(flags);
}
void make_random_test_with_opening_brackets_only(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = n_;
	first = rrr.randUInt() % n + 1;
	last = rrr.randUInt() % n + 1;
	for (int i = 0; i < m_; ++i) {
		int x = rrr.randUInt() % n + 1;
		int y = rrr.randUInt() % n + 1;
		char c = random_opening_bracket();
		add_edge(x, y, c);
	}
	do_after();
	output(flags);
}

void make_test_with_given_sequence(int seed, string seq, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = 2;
	add_path(1, 2, seq);
	first = 1;
	last = 2;
	do_after();
	output(flags);
}

void make_empty_test() {
	assert_clear;
	n = 1;
	output(0);
}

void make_random_path_with_given_string(int seed, int n_, const string & labels, int flags = 0, function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = n_;
	first = rrr.randUInt() % n + 1;
	int current = first;
	for (auto c : labels) {
		int next = rrr.randUInt() % n + 1;
		add_edge(current, next, c);
		current = next;
	}
	last = current;
	do_after();
	output(flags);
}

//creates two cycles each having p_labels on paths between consecutive vertices, c_labels on cycles merged by path having path_labels
void make_test_with_two_cycles(int seed, int len_1, const string & p_labels_1, const string & c_labels_1, int position_1,
int len_2, const string & p_labels_2, const string & c_labels_2, int position_2, const string & path_labels, int flags = 0,
function <void()> do_after = [](){}) {
	rrr.setSeed(seed);
	assert_clear;
	n = 1;
	first = 1;
	int previous = 1;
	int path_start = -1;
	for (int i = 0; i < len_1; ++i) {
		int next = i + 1 == len_1 ? first : new_vertex();
		add_path(previous, next, p_labels_1);
		add_path(previous, previous, c_labels_1);
		if (i == position_1)
			path_start = previous;
		previous = next;
	}
	assert(path_start != -1);
	int path_end = new_vertex();
	previous = path_end;
	add_path(path_start, path_end, path_labels);
	for (int i = 0; i < len_2; ++i) {
		int next = i + 1 == len_2 ? path_end : new_vertex();
		add_path(previous, next, p_labels_2);
		add_path(previous, previous, c_labels_2);
		if (i == position_2)
			last = previous;
		previous = next;
	}
	do_after();
	output(flags);
}

void duplicate_edges_till(int target_count) {
	while (m < target_count) {
		edge r = edges[rrr.randUInt() % m];
		add_edge(r.x, r.y, r.c);
	}
}

void duplicate_one_edge_till(int target_count) {
	edge r = edges[rrr.randUInt() % m];
	while (m < target_count)
		add_edge(r.x, r.y, r.c);
}


void make_very_small_test_with_appending(int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	n = 1;
	first = last = 1;
	append("<", 2);
	append("{", 2);
	append("(", 2);
	append("[", 3);
	do_after();
	output(flags);
}


void make_random_semicycle_with_furthest(int seed, int n_, int m_, int leaps, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	for (int i = 0; i < m_; ++i) {
		int x = rrr.randUInt() % n;
		int y = (x + rrr.randUInt() % leaps) % n;
		x++;
		y++;
		add_edge(x, y, random_bracket());
	}
	auto opt = furthest();
	first = opt.first;
	last = opt.second;
	do_after();
	output(flags);
}

void make_random_dag(int seed, int n_, int m_, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	first = 1, last = n;
	for (int i = 0; i < m_; ++i)
		add_random_directed_edge();
	do_after();
	output(flags);
}

void make_random_dag_with_short_leaps(int seed, int n_, int m_, int leaps, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	n = n_;
	first = 1, last = n;
	for (int i = 0; i < m_; ++i) {
		int x = rrr.randUInt() % (n - 1) + 1;
		int y = 1 + rrr.randUInt() % min(leaps - 1, n - x);
		add_edge(x, x + y, random_bracket());
	}
	do_after();
	output(flags);
}

void make_test_with_multiple_paths(int seed, initializer_list <string> labels, int flags = 0, function <void()> do_after = [](){}) {
	assert_clear;
	rrr.setSeed(seed);
	first = 1;
	last = 2;
	for (auto s : labels)
		add_path(first, last, s);
	do_after();
	output(flags);
}

//TODO: add INVERT, SHUFFLE flags
//TODO: add some random edges trying not to alter the test

int main() {
	init();
	
	//subtask 1, n <= 10, m <= 50
	make_random_closing_with_opening_on_loops(0x123456, 10, 50, {"(", "{[", "<<"});
	make_small_manual_test_2(0x3337);
	make_very_small_test_with_appending();
	make_random_test_with_query_about_furthest(0xba3a3a, 10, 50);
	make_random_dag(0x1eecac, 10, 49, 0, [](){add_edge(7, 1, '<');});
	make_test_with_multiple_paths(0x337, {"[(])", "{<}>", "(()"});
	make_test_with_two_cycles(0xc1, 5, "[", "(", 4, 4, "]", "", 3, ")", SHUFFLE_VERTICES, [](){add_edge(last, first, ')');});
	make_random_test_with_query_about_furthest(0xb, 10, 50);
	make_test_with_given_sequence(0x13, "[{}(<>)]", 0, [](){for (int i = 0; i < 5; ++i) add_random_edge();});
	make_random_test_with_a_cycle(0x1410, 10, 36);//Don't change, it has answer = 40
	make_random_semicycle_with_furthest(0xf011a, 10, 50, 3);
	make_test_with_multiple_paths(0x373, {"[({])}", "[>", "{)", "<}"});
	new_group();
	//subtask 2, n <= 20, m <= 100
	make_random_closing_with_opening_on_loops(0x997, 20, 100, {"<", "[]{", "<<", "({[<"}, 18);
	make_small_test_with_appending_twice_and_random_noise(0x1333, 4);
	make_random_test_with_query_about_furthest(0x7321, 17, 100);
	make_random_closing_with_opening_on_loops(0xface, 20, 99, {"<", "(()", ")[[["});
	make_random_test_with_query_about_furthest(0xabcde, 20, 95);
	make_empty_test();
	make_small_test_with_big_result(0x1266);
	make_random_closing_with_opening_on_loops(0xfeed, 20, 100, {"<<<<", "[[[[[", "({{", "{<<"});
	make_random_test_with_query_about_furthest(0xa132e, 20, 93);
	make_random_test_with_query_about_furthest(0xa320ea, 20, 97);
	make_test_with_two_cycles(0xcce, 4, "{({{", "", 2, 3, ")", "}", 1, "{{");
	make_random_semicycle_with_furthest(0x1791, 20, 100, 3);
	new_group();
	
	//subtask 3, n <= 50
	make_test_with_two_cycles(0xc1373, 19, "(", "[", 8, 24, ")", "]", 18, "[[", NONE, [](){for (int i = 0; i < 6; ++i) add_random_edge(); });
	make_completely_random_test(0xbab13a, 50, 280);
	make_test_with_two_cycles(0x143, 7, "[[[(", "", 5, 15, ")", "]", 13, "[", NONE, [](){
		append("<", 4);
		append("{", 3);
		for (int i = 6; i > 0; --i)
			duplicate_one_edge_till(m + (MM - m) / i);
	});
	make_random_path_with_given_string(0xcada, 50, "((([()]<>(<()[][<><({}[]{<>})><>[{}]]<>>)(){}{})))[]()<><>");
	make_random_test_with_a_cycle_and_answer_no(0xb069a, 50, 610);
	make_random_semicycle_with_furthest(0x1214b, 50, MM, 7);
	make_test_with_two_cycles(0xd, 9, "([", "{", 6, 16, ")}", "]", 13, "[", NONE);
	make_random_closing_with_opening_on_loops(0xb767, 50, 100, {"<<", "((", "[{", "{("});//output = 40
	make_random_path_with_given_string(0x14f, 50, "[{[[{[][(<<(<>)<><<{{}}>>()>>)]<[][{(){}}]>[(<<<<{{}[]}>()>()>>)][]}]][(<<(<>)<><<{{}}>>()>>)]<[][{(){}}]>[(<<(((()[][]{{()}})<<<<>>>>))<<{{}[]}>()>()>>)][]}]",
 		SHUFFLE_EDGES, [](){for (int i = 0; i < 46; ++i)add_random_edge();});
	make_simple_test_with_one_type_of_brackets(0x1e6, 50);
	make_completely_random_test(0x1683, 50, MM);
	make_random_semicycle_with_furthest(0x1438, 50, MM / 3, 3);
	new_group();
	
	//subtask 4, n <= 100
	make_test_with_two_cycles(0x2017, 7, "[(((((", "", 6, 40, "]", ")", 39, "[", NONE, [](){
		append("{", 9);
		append("<", 9);
	});
	make_completely_random_test(0x440, 100, MM);
	make_random_closing_with_opening_on_loops(0xc2a5, 100, 500, {"[[[", "((", "<{", "[<<"});
	make_random_test_with_query_about_furthest(0x147, 100, 200);
	make_completely_random_test(0x404, 100, MM);
	make_random_semicycle_with_furthest(0x7432, 100, 300, 2);
	make_random_test_with_query_about_furthest(0x1920, 20, 40, NONE, [](){
		append("{({{{", 7);
		append("<<<[<", 7);
	});
	make_test_with_two_cycles(0x1996, 15, "[[[{", "(", 13, 11, "]", ")}", 9, "[", NONE, [](){
		append("<<", 8);
	});
	make_completely_random_test(0x1357, 100, MM);
	make_random_test_with_query_about_furthest(0x147, 100, MM);
	make_random_closing_with_opening_on_loops(0xbaca7, 100, 553, {"[[", "{{", "((", "<<", "<(", "{[", "<{([", "({<[", "<[({"});
	make_random_semicycle_with_furthest(0x9855, 100, MM, 4);
	make_test_with_two_cycles(0x1410baca, 60, "[", "", 17, 18, "]", "", 16, "<>");
	new_group();
	//subtask 5, DAG
	for (int i = 0; i < 13; ++i) {
		make_random_dag_with_short_leaps(0x1410a + i, MN - i % 7, MM, 5 + i / 4);
	}
	make_random_dag(0x44, MN, MM);
	make_random_dag(0x47, MN, MM);
	make_random_dag_with_short_leaps(0x1337, MN, MN, 4);
	new_group();
	
	//subtask 6
	make_random_test_with_opening_brackets_only(0x4441, MN, MM);
	make_random_semicycle_with_furthest(0x12, MN, MM, 5);
	make_random_semicycle_with_furthest(0x2, MN, MM, 5);
	make_random_semicycle_with_furthest(0x7, MN, MM, 5);
	make_random_closing_with_opening_on_loops(0x6246, MN, MM, {"(((", "[<<", "{<{"});
	make_test_with_two_cycles(0x3382, 40, "({{", "[", 37, 19, ")]]]", "}", 16, "<><>");
	make_completely_random_test(0xbaba1332, MN, MM);
	make_random_test_with_answer_no(0x9071, MN, MM);
	make_test_with_two_cycles(0x5332, 10, "[[[{[[", "", 7, 129, "}", "]", 99, "{", NONE, [](){append("<", 10);});
	make_random_semicycle_with_furthest(0x4571, MN, MM, 10);
	make_random_closing_with_opening_on_loops(0x8451, MN, MM, {"<<(", "(([", "[[{", "{{<"});
	make_test_with_two_cycles(0x4441, 40, "[", "", 9, 37, "]", "", 34, "<<[[]]([][]{}){}>>", NONE, [](){
		for (string s : {"({}{<", "<<<<<<<<<<<<<<<<<<<<", "<<<><><><><<<<<<<<><<<()(<<<<<<<<<<{"}) {
			int x = rrr.randUInt() % n + 1;
			add_path(x, new_vertex(), s);
		}
	});
	make_test_with_big_result(0xbabc1a, SHUFFLE_EDGES, [](){});
	make_random_semicycle_with_furthest(0x7031, 193, MM, 7);
	make_random_semicycle_with_furthest(0x5226, MN, MM, 4);
	make_test_with_two_cycles(0x4432, 11, "[{[[[[[", "", 8, 112, "}", "]", 99, "{<()><()>()");
	make_random_test_with_a_cycle_and_answer_no(0x8893, 70, 500);
	make_completely_random_test(0x7634, MN, MM);
	
	assert_clear;
}
