/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 60;
int label[N], n;
vector<PII> v[N];
int vis[N], c[N];
int l[N], r[N], m, h[N];
int cc[N];
bool dfs(int u, int x) {
    vis[u] = 1; c[u] = x;
    for (int i = 0; i < v[u].size(); ++i) {
        int j = v[u][i].FR;
        if (!vis[j] && !dfs(j, x ^ v[u][i].SC)) return false;
        else if ((x ^ v[u][i].SC) != c[j]) return false;
    }
    return true;
}
bool check() {
    CL(vis, 0); CL(c, 0xff);
    REP(i, 0, n) if (!vis[i] && !dfs(i, 0)) return false;
    return true;
}
void ae(int a, int b, int c) {
    v[a].PB(MP(b, c)); v[b].PB(MP(a, c));
}
void pop(int a, int b) {
    v[a].pop_back();
    v[b].pop_back();
}
bool inter(int l1, int r1, int l2, int r2) {
    if (l1 > l2) swap(l1, l2), swap(r1, r2);
    return r1 < l2 || r1 > r2;
}
bool can(int n) {
    REP(i, 1, n - 1) if (cc[i] == cc[n] && !inter(l[i], r[i], l[n], r[n])) return false;
    return true;
}
bool solve(int d) {
    if (d > m) return check();
    int x = l[d], y = r[d];
    ae(x - 1, x, 0); ae(y - 1, y, 0);
    ae(x - 1, y, (y - x + 1) & 1);
    cc[d] = 0;
    if (can(d) && solve(d + 1)) return true;
    pop(x - 1, y); pop(y - 1, y); pop(x - 1, x);
    ae(x - 1, x, 1); ae(y - 1, y, 1);
    ae(x - 1, y, 0);
    cc[d] = 1;
    if (can(d) && solve(d + 1)) return true;
    pop(x - 1, y); pop(y - 1, y); pop(x - 1, x);
    return false;
}
class DisjointSemicircles{
	public:
		string getPossibility(vector<int> labels) {
            n = labels.size();
            v[0].clear();
            REP(i, 1, n) label[i] = labels[i - 1], v[i].clear();
            v[0].PB(MP(n, 0)); v[n].PB(MP(0, 0));
            m = 0;
            CL(l, 0), CL(r, 0);
            set<int> S;
            REP(i, 1, n) if (label[i] != -1) {
                if (S.find(label[i]) == S.end()) h[label[i]] = ++m, S.insert(label[i]), l[m] = i;
                else r[h[label[i]]] = i;
            }
            if (solve(1)) return "POSSIBLE";
            else return "IMPOSSIBLE";
		}
};

// CUT begin
ifstream data("DisjointSemicircles.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> labels, string __expected) {
    time_t startClock = clock();
    DisjointSemicircles *instance = new DisjointSemicircles();
    string __result = instance->getPossibility(labels);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> labels;
        from_stream(labels);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(labels, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484815151;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "DisjointSemicircles (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
